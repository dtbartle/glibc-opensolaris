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

#include <errno.h>
#include <sysdep.h>
#include <pthread.h>
#include <pthreadP.h>
#include <inline-syscall.h>
#include <stddef.h>
#include <sys/synch.h>

/* Try to acquire write lock for RWLOCK or return after specfied time.	*/
int
pthread_rwlock_timedwrlock (rwlock, abstime)
     pthread_rwlock_t *rwlock;
     const struct timespec *abstime;
{
  /* Reject invalid timeouts.  */
  if (abstime && (abstime->tv_nsec < 0 || abstime->tv_nsec >= 1000000000))
    return EINVAL;

  int errval = pthread_mutex_lock (&rwlock->mutex);
  if (errval != 0)
    return errval;

#if 0
char buf[200];
sprintf (buf, "%d:%d (%p): pthread_rwlock_timedwrlock (pre): readers = %d\n",
    THREAD_SELF->pid, pthread_self (), THREAD_SELF, rwlock->readers);
write (1, buf, strlen(buf));
#endif

  /* Check for deadlock.  */
  if (__builtin_expect (rwlock->owner == (uintptr_t)THREAD_SELF, 0) ||
        ((rwlock->type & LOCK_SHARED) && __builtin_expect (
        rwlock->ownerpid == THREAD_GETMEM (THREAD_SELF, pid), 0)))
    return pthread_mutex_unlock (&rwlock->mutex) ?: EDEADLK;

  /* Wait until we can acquire the write lock.  */
  while (rwlock->readers & (_RWLOCK_RD_MASK | _RWLOCK_WR_LOCK))
    {
// TODO: _not_cancel
      errval = pthread_cond_wait (&rwlock->writercv, &rwlock->mutex);
      if (errval != 0)
        return pthread_mutex_unlock (&rwlock->mutex) ?: errval;
    }

  /* Set the write lock.  */
  rwlock->readers = _RWLOCK_WR_LOCK;
  rwlock->owner = (uintptr_t)THREAD_SELF;
  if (rwlock->type & LOCK_SHARED)
    rwlock->ownerpid = THREAD_GETMEM (THREAD_SELF, pid);
  atomic_write_barrier ();

#if 0
sprintf (buf, "%d:%d (%p): pthread_rwlock_timedwrlock (post): readers = %d\n",
    THREAD_SELF->pid, pthread_self (), THREAD_SELF, rwlock->readers);
write (1, buf, strlen(buf));
#endif

  return pthread_mutex_unlock (&rwlock->mutex);
}
