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

#include <sysdeps/posix/signal.c>

/* XXX: These are racey.  */

#include <inline-syscall.h>

DECLARE_INLINE_SYSCALL (int64_t, lwp_sigmask, int how, unsigned int bits0,
    unsigned int bits1);

static int64_t __thread __sigmask;

void _sigoff (void)
{
  __sigmask = INLINE_SYSCALL (lwp_sigmask, 3, SIG_SETMASK,
      (unsigned int)-1, (unsigned int)-1);
}

void _sigon (void)
{
  rval_t mask;
  mask.rval64 = __sigmask;
  INLINE_SYSCALL (lwp_sigmask, 3, SIG_SETMASK, (unsigned int)mask.rval1,
    (unsigned int)mask.rval2);
}
