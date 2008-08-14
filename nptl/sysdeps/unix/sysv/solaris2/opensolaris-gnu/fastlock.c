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
#include "pthreadP.h"
#include <synch_priv.h>
#include <sys/synch.h>
#include <stdbool.h>
#include <assert.h>

int __mutex_lock_fast (pthread_mutex_t *mutex, bool try)
{
  if (mutex->mutex_lockword32 == LOCKWORD32_UNSET_NO_WAITERS)
    {
      /* The mutex is not held by anyone so try to grab it.  */
      if (mutex->mutex_type & LOCK_SHARED)
        {
          uint64_t new_lockword64 = LOCKWORD64_SET_NO_WAITERS |
                (THREAD_GETMEM (THREAD_SELF, pid) << MUTEX_OWNERPID_SHIFT);
          uint64_t old_lockword64 = atomic_compare_and_exchange_val_acq (
              &mutex->mutex_lockword64, new_lockword64,
              LOCKWORD64_UNSET_NO_WAITERS);
          if (__builtin_expect (old_lockword64 ==
                LOCKWORD64_UNSET_NO_WAITERS, 1))
            {
              mutex->mutex_owner = (uintptr_t)THREAD_SELF;
              return 0;
            }
        }
      else
        {
          uint32_t old_lockword32 = atomic_compare_and_exchange_val_acq (
              &mutex->mutex_lockword32, LOCKWORD32_SET_NO_WAITERS,
              LOCKWORD32_UNSET_NO_WAITERS);
          if (__builtin_expect (old_lockword32 ==
                LOCKWORD32_UNSET_NO_WAITERS, 1))
            {
              mutex->mutex_owner = (uintptr_t)THREAD_SELF;
              return 0;
            }
        }
    }
  else if ((mutex->mutex_type & LOCK_RECURSIVE) &&
       mutex->mutex_lockbyte == LOCKBYTE_SET &&
     ((mutex->mutex_type & LOCK_SHARED) == 0 ||
       mutex->mutex_ownerpid == THREAD_GETMEM (THREAD_SELF, pid)) &&
       mutex->mutex_owner == (uintptr_t)THREAD_SELF)
    {
      /* Recursively held lock.  */
      if (mutex->mutex_rcount == RECURSION_MAX)
        {
          return EAGAIN;
        }
      mutex->mutex_rcount++;
      atomic_write_barrier ();
      return 0;
    }
  else if ((mutex->mutex_type & LOCK_ERRORCHECK) &&
            mutex->mutex_lockbyte == LOCKBYTE_SET &&
          ((mutex->mutex_type & LOCK_SHARED) == 0 ||
            mutex->mutex_ownerpid == THREAD_GETMEM (THREAD_SELF, pid)) &&
           (mutex->mutex_owner == (uintptr_t)THREAD_SELF))
    {
      /* Error checking: lock already held.  */
      return EDEADLK;
    }
  else if (try && mutex->mutex_lockbyte == LOCKBYTE_SET)
    {
      /* Tried to lock but lock was held.  */
      return EBUSY;
    }

  /* Need to use the slow code.  */
  return -1;
}


int __mutex_unlock_fast (pthread_mutex_t *mutex)
{
  if ((mutex->mutex_type & LOCK_RECURSIVE) &&
       mutex->mutex_lockbyte == LOCKBYTE_SET &&
     ((mutex->mutex_type & LOCK_SHARED) == 0 ||
       mutex->mutex_ownerpid == THREAD_GETMEM (THREAD_SELF, pid)) &&
       mutex->mutex_owner == (uintptr_t)THREAD_SELF &&
       mutex->mutex_rcount > 0)
    {
      /* Recursively held lock.  */
      mutex->mutex_rcount--;
      atomic_write_barrier ();
      return 0;
    }
  else if ((mutex->mutex_type & LOCK_ERRORCHECK) &&
          ((mutex->mutex_lockbyte != LOCKBYTE_SET ||
          ((mutex->mutex_type & LOCK_SHARED) &&
            mutex->mutex_ownerpid != THREAD_GETMEM (THREAD_SELF, pid)) ||
            mutex->mutex_owner != (uintptr_t)THREAD_SELF)))
    {
      /* error checking: lock not held by this thread */
      return EPERM;
    }
  else if (mutex->mutex_lockword32 == LOCKWORD32_SET_NO_WAITERS)
    {
      /* We need to clear the owner before we fully unlock. Otherwise
         we have a race condition where we might clear the owner after
         another thread sets the lock word. If we fail to unlock here
         we don't need to reset the owner as we're just going to unlock
         in the kernel (which doesn't check this field anyhow).  */
      mutex->mutex_owner = (uintptr_t)NULL;

      /* Nobody is waiting on the mutex so we can try to release it.  */
      if (mutex->mutex_type & LOCK_SHARED)
        {
            uint64_t test_lockword64 = LOCKWORD64_SET_NO_WAITERS |
                (mutex->mutex_ownerpid << MUTEX_OWNERPID_SHIFT);
                (THREAD_GETMEM (THREAD_SELF, pid) << MUTEX_OWNERPID_SHIFT);
            uint64_t old_lockword64 = atomic_compare_and_exchange_val_acq (
                &mutex->mutex_lockword64, LOCKWORD64_UNSET_NO_WAITERS,
                test_lockword64);
            if (__builtin_expect (old_lockword64 == test_lockword64, 1))
              {
                return 0;
              }
        }
      else
        {
          uint32_t old_lockword32 = atomic_compare_and_exchange_val_acq (
              &mutex->mutex_lockword32, LOCKWORD32_UNSET_NO_WAITERS,
              LOCKWORD32_SET_NO_WAITERS);
          if (__builtin_expect (old_lockword32 ==
                LOCKWORD32_SET_NO_WAITERS, 1))
            {
              return 0;
            }
        }
    }

  /* Need to use the slow code.  */
  return -1;
}
