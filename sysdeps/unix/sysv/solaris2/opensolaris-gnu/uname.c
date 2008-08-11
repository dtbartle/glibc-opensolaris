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
#include <sys/utsname.h>
#include <string.h>

/* TODO: temporary hack */
#define UNAME_SYSNAME "GNU/OpenSolaris"
#define UNAME_MACHINE "i686"

DECLARE_INLINE_SYSCALL (int, uname, struct utsname *buf);

int
__uname (struct utsname *uname)
{
  int result = INLINE_SYSCALL (uname, 1, uname);

  /* TODO: temporary hack */
  if (result >= 0)
    {
      memcpy (uname->sysname, UNAME_SYSNAME, sizeof(UNAME_SYSNAME));
      memcpy (uname->machine, UNAME_MACHINE, sizeof(UNAME_MACHINE));
    }

  /* the uname syscall returns 1 on success */
  return (result >= 0) ? 0 : -1;
}

weak_alias (__uname, uname)
libc_hidden_def (__uname)
libc_hidden_def (uname)
