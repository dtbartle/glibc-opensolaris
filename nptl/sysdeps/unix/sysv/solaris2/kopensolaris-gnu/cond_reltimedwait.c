/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>, 2008.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <inline-syscall.h>
#include <pthreadP.h>
#include <synch.h>
#include <errno.h>

DECLARE_INLINE_SYSCALL (int, lwp_cond_wait, cond_t *cv, mutex_t *mp,
    struct timespec *tsp, int check_park);

struct _condvar_cleanup_buffer
{
  int oldtype;
  cond_t *cond;
  mutex_t *mutex;
  uint8_t old_mutex_rcount;
};

void
__attribute__ ((visibility ("hidden")))
__condvar_cleanup (void *arg)
{
  struct _condvar_cleanup_buffer *cbuffer =
    (struct _condvar_cleanup_buffer *) arg;
  mutex_t *mutex = cbuffer->mutex;

  /* Note: we don't whether the mutex was unlocked by the kernel or not.  */

  /* TODO: mutex_cond_waiters needs to be a counter.  */

  int errval = 0;
  while (1)
    {
      if (mutex->mutex_lockbyte == LOCKBYTE_SET &&
        ((mutex->mutex_type & LOCK_SHARED) == 0 ||
          mutex->mutex_ownerpid == THREAD_GETMEM (THREAD_SELF, pid)) &&
         (mutex->mutex_owner == THREAD_GETMEM (THREAD_SELF, tid)))
        {
          /* The lock is held by us (we didn't get signaled).  */
          break;
        }
      else
        {
          /* The mutex was unlocked so we claim it,  */
          errval = mutex_lock (mutex);
          break;
        }
    }

  /* Restore the mutex_rcount.  */
  if (errval == 0)
    mutex->mutex_rcount = cbuffer->old_mutex_rcount;

  /* The condition variable is no longer using the mutex.  */
  atomic_decrement (&mutex->mutex_cond_waiters);
}


int
__cond_reltimedwait_internal (cond, mutex, reltime, cancel)
     cond_t *cond;
     mutex_t *mutex;
     struct timespec *reltime;
     int cancel;
{
  struct _pthread_cleanup_buffer buffer;
  struct _condvar_cleanup_buffer cbuffer;

  /* Reject invalid timeouts.  */
  if (INVALID_TIMESPEC (reltime))
    return EINVAL;

  if ((mutex->mutex_type & LOCK_ERRORCHECK) &&
     ((mutex->mutex_lockbyte != LOCKBYTE_SET ||
       mutex->mutex_owner != THREAD_GETMEM (THREAD_SELF, tid) ||
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
            mutex->mutex_owner == THREAD_GETMEM (THREAD_SELF, tid) &&
            mutex->mutex_rcount > 0)
    {
      /* Recursively held lock. XXX: Using recursive mutexes with condition
         variables is undefined; we do what sun's libc does, namely fully
         release the lock.  */
      cbuffer.old_mutex_rcount = mutex->mutex_rcount;
      mutex->mutex_rcount = 0;
    }

  /* Mark the mutex as still in use.  */
  atomic_increment (&mutex->mutex_cond_waiters);

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

  int errval = INLINE_SYSCALL (lwp_cond_wait, 4, cond, mutex, reltime, 1);

  if (cancel)
    {
      /* Disable asynchronous cancellation.  */
      __pthread_disable_asynccancel (cbuffer.oldtype);

      /* The cancellation handling is back to normal, remove the handler.  */
      __pthread_cleanup_pop (&buffer, 0);
    }

  /* Re-acquire the lock. The docs say we must always re-acquire so we don't
     use __mutex_timedlock. Note that even if the above wait fails the kernel
     always unlocks the mutex.  */
  int errval2 = mutex_lock (mutex);
  if (errval2 == EOWNERDEAD)
    errval = errval2;
  else if (errval == 0)
    errval = errval2;

  /* Restore the mutex_rcount.  */
  if ((errval2 == 0 || errval2 == EOWNERDEAD) &&
        (mutex->mutex_type & LOCK_RECURSIVE))
    mutex->mutex_rcount = cbuffer.old_mutex_rcount;

  /* The condition variable is no longer using the mutex.  */
  atomic_decrement (&mutex->mutex_cond_waiters);

  return errval;
}


int cond_reltimedwait (cond, mutex, reltime)
      cond_t *cond;
      mutex_t *mutex;
      struct timespec *reltime;
{
  return __cond_reltimedwait_internal (cond, mutex, reltime, 1);
}
