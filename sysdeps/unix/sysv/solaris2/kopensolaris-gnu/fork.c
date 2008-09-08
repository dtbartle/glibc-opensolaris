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
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sysdep.h>

DECLARE_INLINE_SYSCALL (int64_t, forkx, int flags);

pid_t
__libc_fork (void)
{
  rval_t res;
  res.rval64 = INLINE_SYSCALL (forkx, 1, 0);
  if (res.rval64 == -1)
    return (pid_t)-1;
  else if (res.rval2 != 0)
    return 0;
  else
    return (pid_t)res.rval1;
}
weak_alias (__libc_fork, __fork)
libc_hidden_def (__fork)
weak_alias (__libc_fork, fork)
weak_alias (__libc_fork, fork1)
