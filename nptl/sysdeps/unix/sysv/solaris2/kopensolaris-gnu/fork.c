/* Copyright (C) 2002, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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
#include <sysdep.h>
#include <tls.h>

DECLARE_INLINE_SYSCALL (int64_t, forkx, int flags);

static inline pid_t ARCH_FORK(void)
{
  rval_t res;
  res.rval64 = INLINE_SYSCALL (forkx, 1, 0);

  /* Only the lower 32-bits are set to -1 on error (see NOTES.opensolaris).  */
  if (res.rval1 == -1)
    return (pid_t)-1;
  else if (res.rval2 != 0)
    return 0;
  else
    return (pid_t)res.rval1;
}
#define ARCH_FORK	ARCH_FORK

#include <nptl/sysdeps/unix/sysv/linux/fork.c>
weak_alias (__libc_fork, fork1)
