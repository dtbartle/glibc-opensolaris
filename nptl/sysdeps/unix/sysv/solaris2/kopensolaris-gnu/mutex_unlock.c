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
#include <synchP.h>

DECLARE_INLINE_SYSCALL (int, lwp_mutex_unlock, mutex_t *lp);

int __mutex_unlock_fast (mutex_t *mutex);


int mutex_unlock (mutex)
      mutex_t *mutex;
{
  /* Handle inconsistent robust mutexes.  */
  if ((mutex->mutex_type & LOCK_ROBUST) &&
       (mutex->mutex_flag & LOCK_NOTRECOVERABLE))
    return ENOTRECOVERABLE;

  /* Always hit the kernel for priority inherit locks.  */
  if ((mutex->mutex_type & LOCK_PRIO_INHERIT) == 0)
    {
      int result = __mutex_unlock_fast (mutex);
      if(result >= 0)
        return result;
    }
  else
    {
      /* Except when we already hold a recursive lock.  */
      if ((mutex->mutex_type & LOCK_RECURSIVE) && MUTEX_IS_OWNER (mutex) &&
           mutex->mutex_rcount > 0)
        {
          --mutex->mutex_rcount;
          return 0;
        }
    }

  /* The kernel does not clear mutex_owner so we clear it here.  */
  mutex->mutex_owner = 0;

  int errval = INLINE_SYSCALL (lwp_mutex_unlock, 1, mutex);
  if (errval != 0)
    return errval;

  /* The kernel does not clear the lockbyte for priority inherit mutexes.  */
  if (mutex->mutex_type & LOCK_PRIO_INHERIT)
    mutex->mutex_lockbyte = 0;

  return errval;
}

weak_alias (mutex_unlock, _lwp_mutex_unlock)
