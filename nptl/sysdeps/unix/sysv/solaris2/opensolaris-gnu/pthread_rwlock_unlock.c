/* Copyright (C) 2003, 2007, 2008 Free Software Foundation, Inc.
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
#include <stdio.h>
#include <sys/synch.h>


/* Unlock RWLOCK.  */
int
__pthread_rwlock_unlock (pthread_rwlock_t *rwlock)
{
  int errval = pthread_mutex_lock (&rwlock->mutex);
  if (errval != 0)
    return errval;

  if (rwlock->readers & _RWLOCK_WR_LOCK)
    {
      /* Writer unlock.  */
      if (__builtin_expect (rwlock->owner != (uintptr_t)THREAD_SELF, 0) ||
            ((rwlock->type & LOCK_SHARED) && __builtin_expect (
            rwlock->ownerpid != THREAD_GETMEM (THREAD_SELF, pid), 0)))
        return pthread_mutex_unlock (&rwlock->mutex) ?: EPERM;
      rwlock->owner = rwlock->ownerpid = 0;
      rwlock->readers &= ~_RWLOCK_WR_LOCK;
    }
  else
    {
      /* Reader unlock.  */
      if ((rwlock->readers & _RWLOCK_RD_MASK) == 0)
        return pthread_mutex_unlock (&rwlock->mutex) ?: EPERM;
      rwlock->readers = (rwlock->readers & _RWLOCK_WR_LOCK) |
          ((rwlock->readers & _RWLOCK_RD_MASK) - 1);
    }

  /* Wake up a writer (if possible) or all readers.  */
  if ((rwlock->readers & _RWLOCK_RD_MASK) == 0 &&
        __cond_has_waiters (&rwlock->writercv))
    errval = pthread_cond_signal (&rwlock->writercv);
  else if (__cond_has_waiters (&rwlock->readercv))
    errval = pthread_cond_broadcast (&rwlock->readercv);

  return pthread_mutex_unlock (&rwlock->mutex) ?: errval;
}

weak_alias (__pthread_rwlock_unlock, pthread_rwlock_unlock)
strong_alias (__pthread_rwlock_unlock, __pthread_rwlock_unlock_internal)
weak_alias (__pthread_rwlock_unlock, rw_unlock)
