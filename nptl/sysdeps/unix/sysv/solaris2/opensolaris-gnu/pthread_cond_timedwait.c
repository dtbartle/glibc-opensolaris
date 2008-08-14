/* Copyright (C) 2003, 2004, 2007, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Martin Schwidefsky <schwidefsky@de.ibm.com>, 2003.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <endian.h>
#include <errno.h>
#include <sysdep.h>
#include <pthread.h>
#include <pthreadP.h>

#include <shlib-compat.h>
#include <inline-syscall.h>
#include <abstime-to-reltime.h>
#include <sys/synch.h>
#include <synch_priv.h>

DECLARE_INLINE_SYSCALL (int, lwp_cond_wait, pthread_cond_t *cv,
    pthread_mutex_t *mp, struct timespec *tsp, int check_park);

struct _condvar_cleanup_buffer
{
  int oldtype;
  pthread_cond_t *cond;
  pthread_mutex_t *mutex;
  int old_cond_waiters;
  int old_mutex_rcount;
};

void
__attribute__ ((visibility ("hidden")))
__condvar_cleanup (void *arg)
{
  struct _condvar_cleanup_buffer *cbuffer =
    (struct _condvar_cleanup_buffer *) arg;
  pthread_mutex_t *mutex = cbuffer->mutex;

  /* Note: we don't whether the mutex was unlocked by the kernel or not.  */

  /* The condition variable is no longer using the mutex.  */
  mutex->mutex_cond_waiters = cbuffer->old_cond_waiters;
  atomic_write_barrier ();

  while (1)
    {
      if (mutex->mutex_lockbyte == LOCKBYTE_SET &&
        ((mutex->mutex_type & LOCK_SHARED) == 0 ||
          mutex->mutex_ownerpid == THREAD_GETMEM (THREAD_SELF, pid)) &&
         (mutex->mutex_owner == (uintptr_t)THREAD_SELF))
        {
          /* The lock is held by us (we didn't get signaled).  */
          break;
        }
      else if (mutex->mutex_lockbyte == 0)
        {
          /* The mutex is unlocked.  */
          pthread_mutex_lock (mutex);
          break;
        }
    }

  /* Restore the mutex_rcount.  */
  if (mutex->mutex_lockbyte == LOCKBYTE_SET &&
     (mutex->mutex_type & LOCK_RECURSIVE) &&
      mutex->mutex_rcount == 0 && cbuffer->old_mutex_rcount > 0)
    {
      mutex->mutex_rcount = cbuffer->old_mutex_rcount;
      atomic_write_barrier ();
    }
}


int
__pthread_cond_timedwait_internal (cond, mutex, abstime, cancel)
     pthread_cond_t *cond;
     pthread_mutex_t *mutex;
     const struct timespec *abstime;
     int cancel;
{
  struct _pthread_cleanup_buffer buffer;
  struct _condvar_cleanup_buffer cbuffer;

  /* Reject invalid timeouts.  */
  if (abstime && (abstime->tv_nsec < 0 || abstime->tv_nsec >= 1000000000))
    return EINVAL;

  if ((mutex->mutex_type & LOCK_ERRORCHECK) &&
     ((mutex->mutex_lockbyte != LOCKBYTE_SET ||
       mutex->mutex_owner != (uintptr_t)THREAD_SELF ||
     ((mutex->mutex_type & LOCK_SHARED) &&
       mutex->mutex_ownerpid != THREAD_GETMEM (THREAD_SELF, pid)))))
    {
      /* Error checking: lock not held by this thread.  */
      return EPERM;
    }
  else if ((mutex->mutex_type & LOCK_RECURSIVE) &&
            mutex->mutex_lockbyte == LOCKBYTE_SET &&
          ((mutex->mutex_type & LOCK_SHARED) == 0 ||
            mutex->mutex_ownerpid == THREAD_GETMEM (THREAD_SELF, pid)) &&
            mutex->mutex_owner == (uintptr_t)THREAD_SELF &&
            mutex->mutex_rcount > 0)
    {
      /* Recursively held lock. XXX: Using recursive mutexes with condition
         variables is undefined; we do what sun's libc does, namely fully
          release the lock.  */
      cbuffer.old_mutex_rcount = mutex->mutex_rcount;
      mutex->mutex_rcount = 0;
      atomic_write_barrier ();
    }

  /* Mark the mutex as still in use.  */
  cbuffer.old_cond_waiters = mutex->mutex_cond_waiters;
  if (cbuffer.old_cond_waiters == 0)
    {
      mutex->mutex_cond_waiters = 1;
      atomic_write_barrier ();
    }

  /* Prepare structure passed to cancellation handler.  */
  cbuffer.cond = cond;
  cbuffer.mutex = mutex;

  if (cancel)
    {
      /* Before we block we enable cancellation.  Therefore we have to
         install a cancellation handler.  */
      __pthread_cleanup_push (&buffer, __condvar_cleanup, &cbuffer);

      /* Enable asynchronous cancellation.  Required by the standard.  */
      cbuffer.oldtype = __pthread_enable_asynccancel ();
    }

  struct timespec _reltime;
  struct timespec *reltime = abstime_to_reltime (abstime, &_reltime);
  if (reltime && reltime->tv_sec < 0)
    return ETIMEDOUT;
  int errval = INLINE_SYSCALL (lwp_cond_wait, 4, cond, mutex, reltime, 1);
  if (errval == ETIME)
    errval = ETIMEDOUT;
  /* The docs say to return 0 when interrupted.  */
  else if (errval == EINTR)
    errval = 0;

  if (cancel)
    {
      /* Disable asynchronous cancellation.  */
      __pthread_disable_asynccancel (cbuffer.oldtype);

      /* The cancellation handling is back to normal, remove the handler.  */
      __pthread_cleanup_pop (&buffer, 0);
    }

  /* Re-acquire the lock. The docs say we must always re-acquire so we don't
     use pthread_mutex_timedlock. Note that even if the above wait fails the
     kernel always unlocks the mutex.  */
  int errval2 = pthread_mutex_lock (mutex);
  if (errval2 == EINTR)
    return 0;
  else if (errval2 != 0)
    return EINVAL;

  /* Restore the mutex_rcount.  */
  if (mutex->mutex_type & LOCK_RECURSIVE)
    {
      mutex->mutex_rcount = cbuffer.old_mutex_rcount;
      atomic_write_barrier ();
    }

  /* The condition variable is no longer using the mutex.  */
  if (cbuffer.old_cond_waiters == 0)
    {
      mutex->mutex_cond_waiters = 0;
      atomic_write_barrier ();
    }

  return errval;
}


int
__pthread_cond_timedwait (cond, mutex, abstime)
     pthread_cond_t *cond;
     pthread_mutex_t *mutex;
     const struct timespec *abstime;
{
  return __pthread_cond_timedwait_internal (cond, mutex, abstime, 1);
}

versioned_symbol (libpthread, __pthread_cond_timedwait, pthread_cond_timedwait,
		  GLIBC_2_3_2);
