/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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

#ifndef _SYS_FEATURE_TESTS
#define _SYS_FEATURE_TESTS

/* Let glibc do most of the work.  */
#include <features.h>

#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE - 0 < 500) && \
	(_XOPEN_VERSION - 0 < 4) && !defined(_XOPEN_SOURCE_EXTENDED)
# define _XPG3
# elif (defined(_XOPEN_SOURCE) && _XOPEN_VERSION - 0 == 4)
# define _XPG4
# define _XPG3
#elif (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE_EXTENDED - 0 == 1)
# define _XPG4_2
# define _XPG4
# define _XPG3
#elif   (_XOPEN_SOURCE - 0 == 500)
# define _XPG5
# define _XPG4_2
# define _XPG4
# define _XPG3
# undef  _POSIX_C_SOURCE
# define _POSIX_C_SOURCE	199506L
#elif   (_XOPEN_SOURCE - 0 == 600) || (_POSIX_C_SOURCE - 0 == 200112L)
# define _XPG6
# define _XPG5
# define _XPG4_2
# define _XPG4
# define _XPG3
# undef  _POSIX_C_SOURCE
# define _POSIX_C_SOURCE	200112L
# undef  _XOPEN_SOURCE
# define _XOPEN_SOURCE	600
#endif

#endif /* _SYS_FEATURE_TESTS */
