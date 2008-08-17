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


int rw_tryrdlock (rwlock)
      rwlock_t *rwlock;
{
  int errval = mutex_trylock (&rwlock->mutex);
  if (errval != 0)
    return errval;

  if ((rwlock->readers & _RWLOCK_WR_LOCK) ||
        (__cond_has_waiters (&rwlock->writercv) &&
        !PTHREAD_RWLOCK_PREFER_READER_P (rwlock)))
    {
      (void)mutex_unlock (&rwlock->mutex);
      return EBUSY;
    }

  /* Increment readers (note that no other bits are set).  */
  if (rwlock->readers == _RWLOCK_RD_MAX)
    {
      (void)mutex_unlock (&rwlock->mutex);
      return EAGAIN;
    }
  rwlock->readers++;

  (void)mutex_unlock (&rwlock->mutex);
  return 0;
}
