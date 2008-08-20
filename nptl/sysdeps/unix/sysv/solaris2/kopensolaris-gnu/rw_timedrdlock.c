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

#include <errno.h>
#include <pthreadP.h>
#include <synch.h>
#include <abstime-to-reltime.h>


int __rw_timedrdlock (rwlock, abstime)
      rwlock_t *rwlock;
      struct timespec *abstime;
{
  /* Reject invalid timeouts.  */
  if (INVALID_TIMESPEC (abstime))
    return EINVAL;

  struct timespec _reltime;
  struct timespec *reltime = abstime_to_reltime (abstime, &_reltime);
  if (reltime && reltime->tv_sec < 0)
    return ETIME;

  int errval = mutex_lock (&rwlock->mutex);
  if (errval != 0)
    return errval;

  /* Check for deadlock.  */
  if (__builtin_expect (rwlock->owner == (uintptr_t)THREAD_SELF, 0) ||
        ((rwlock->type & LOCK_SHARED) && __builtin_expect (
        rwlock->ownerpid == THREAD_GETMEM (THREAD_SELF, pid), 0)))
    {
      (void)mutex_unlock (&rwlock->mutex);
      return EDEADLK;
    }

  /* Wait until we can acquire the read lock.  */
  while ((rwlock->readers & _RWLOCK_WR_LOCK) ||
        (__cond_has_waiters (&rwlock->writercv) &&
        !PTHREAD_RWLOCK_PREFER_READER_P (rwlock)))
    {
      /* Wait for writer to wake us up.  */
      errval = __cond_reltimedwait_internal ((cond_t *)&rwlock->readercv,
          (mutex_t *)&rwlock->mutex, reltime, 0);
      if (errval != 0)
        {
          (void)mutex_unlock (&rwlock->mutex);
          return errval;
        }
    }

  /* Increment readers (note that no other bits are set).  */
  if (rwlock->readers == _RWLOCK_RD_MAX)
    {
      /* XXX: Solaris mutexes have no overflow check and don't know about
         EAGAIN; in practice overflow will not occur so we don't care.  */
      (void)mutex_unlock (&rwlock->mutex);
      return EAGAIN;
    }
  ++rwlock->readers;

  (void)mutex_unlock (&rwlock->mutex);
  return 0;
}
