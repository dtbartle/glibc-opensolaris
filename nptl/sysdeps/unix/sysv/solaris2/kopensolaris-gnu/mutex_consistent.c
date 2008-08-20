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

#include <pthreadP.h>
#include <synch.h>
#include <errno.h>


int mutex_consistent (mutex)
      mutex_t *mutex;
{
  if ((mutex->mutex_type & LOCK_ROBUST) == 0 ||
      (mutex->mutex_flag & LOCK_INITED) == 0 ||
      (mutex->mutex_flag & (LOCK_OWNERDEAD | LOCK_UNMAPPED)) == 0)
    return EINVAL;

  mutex->mutex_flag &= ~(LOCK_OWNERDEAD | LOCK_UNMAPPED);

  /* The lock cannot be recursively held since it was just reclaimed.  */
  mutex->mutex_rcount = 0;

  return 0;
}
