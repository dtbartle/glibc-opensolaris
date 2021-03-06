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

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <errno.h>

DECLARE_INLINE_SYSCALL (int, rusagesys, int cmd, ...);

int
__getrusage (who, usage)
     enum __rusage_who who;
     struct rusage *usage;
{
  int cmd;
  switch (who)
    {
    case RUSAGE_SELF:
      cmd = SYS_SUB_getrusage;
      break;
    case RUSAGE_LWP:
      cmd = SYS_SUB_getrusage_lwp;
      break;
    case RUSAGE_CHILDREN:
      cmd = SYS_SUB_getrusage_chld;
      break;
    default:
      __set_errno (EINVAL);
      return -1;
    }

  return INLINE_SYSCALL (rusagesys, 2, cmd, usage);
}

weak_alias (__getrusage, getrusage)
