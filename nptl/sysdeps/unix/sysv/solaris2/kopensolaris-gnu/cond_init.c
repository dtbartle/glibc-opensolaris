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


int cond_init (cond, type, arg)
      cond_t *cond;
      int type;
      void *arg;
{
  if (type != LOCK_NORMAL && type != LOCK_SHARED)
    return EINVAL;

  memset (cond, 0, sizeof(cond_t));
  cond->cond_type = type;
  cond->cond_magic = COND_MAGIC;

  return 0;
}
