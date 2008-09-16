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

#include <sys/auxv.h>
#include_next <dl-sysdep.h>

#ifdef SHARED
# define SECURE_DECIDED
#else
# define SECURE_DECIDED	__libc_enable_secure_decided = 1;
#endif

#define DL_PLATFORM_AUXV                                    \
      case AT_SUN_EXECNAME:                                 \
	GLRO(dl_sun_execname) = (void *) av->a_un.a_val;        \
	break;                                                  \
      case AT_SUN_AUXFLAGS:                                 \
	if (av->a_un.a_val & AF_SUN_SETUGID)                    \
	  {                                                     \
		__libc_enable_secure = 1;                           \
		SECURE_DECIDED                                      \
	  }                                                     \
	break;
