/* Copyright (C) 1995, 1996 Free Software Foundation, Inc.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* On Linux we must not ask __getdtablesize for te value for _SC_OPEN_MAX
   because this would mean an endless loop.  */

#include <limits.h>
#include <unistd.h>

extern long int __default_sysconf (int name);

long int
__sysconf (int name)
{
  if (name == _SC_OPEN_MAX)
    return OPEN_MAX;

  return __default_sysconf (name);
}

#define __sysconf __default_sysconf

#include <sysdeps/posix/sysconf.c>
