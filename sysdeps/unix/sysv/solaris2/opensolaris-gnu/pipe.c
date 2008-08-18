/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>.

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
#include <unistd.h>
#include <stddef.h>
#include <errno.h>

DECLARE_INLINE_SYSCALL (int64_t, pipe, void);

int
__pipe (__pipedes)
     int __pipedes[2];
{
  if (__pipedes == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }

  rval_t result;
  result.rval64 = INLINE_SYSCALL (pipe, 0);
  if (result.rval64 == -1)
    return -1;
  __pipedes[0] = result.rval1;
  __pipedes[1] = result.rval2;

  return 0;
}

libc_hidden_def (__pipe)
weak_alias (__pipe, pipe)
