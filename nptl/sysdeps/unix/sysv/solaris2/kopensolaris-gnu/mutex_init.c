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

DECLARE_INLINE_SYSCALL (int, lwp_mutex_register, mutex_t *lp);


int mutex_init (mutex, type, arg)
      mutex_t *mutex;
      int type;
      void * arg;
{
  // TODO: check type

  if (type & LOCK_ROBUST)
    {
      if ((mutex->mutex_type & LOCK_INITED))
        return EBUSY;
    }
  else
    {
      memset (mutex, 0, sizeof(mutex_t));
    }
  mutex->mutex_type = type;
  mutex->mutex_flag = LOCK_INITED;
  mutex->mutex_magic = MUTEX_MAGIC;
  mutex->mutex_ceiling = (int)arg;
  mutex->mutex_cond_waiters = 0;

  /* Register robust shared lock.  */
  if ((type & (LOCK_ROBUST | LOCK_SHARED)) == (LOCK_ROBUST | LOCK_SHARED))
    {
      int errval = INLINE_SYSCALL (lwp_mutex_register, 1, mutex);
      if (errval != 0)
        return errval;
    }

  return 0;
}
