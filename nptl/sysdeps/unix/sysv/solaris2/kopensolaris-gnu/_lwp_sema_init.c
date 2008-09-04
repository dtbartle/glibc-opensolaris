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


int _lwp_sema_init (sem, count)
      sema_t *sem;
      int count;
{
  /* Parameter sanity check.  */
  if (__builtin_expect (count > SEM_VALUE_MAX, 0))
    return EINVAL;

  memset (sem, 0, sizeof(sema_t));
  sem->count = (uint32_t)count;
  sem->type = LOCK_SHARED;
  sem->magic = SEMA_MAGIC;

  return 0;
}
