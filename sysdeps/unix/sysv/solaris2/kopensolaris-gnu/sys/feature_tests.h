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

/* Let glibc do the rest of most of the work.  */
#include <features.h>
#include <sys/isa_defs.h>

#if defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
# define _POSIX_C_SOURCE 1
#endif

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
#elif   (_XOPEN_SOURCE - 0 == 600)
# define _XPG6
# define _XPG5
# define _XPG4_2
# define _XPG4
# define _XPG3
#endif

/* By default the large-file interfaces are available.  */
#if !defined(_XOPEN_SOURCE) && !defined(__USE_LARGEFILE64)
# define __USE_LARGEFILE64	1
#endif

/* Sun doesn't leave _FILE_OFFSET_BITS undefined.  */
#ifdef _LP64
# ifndef _FILE_OFFSET_BITS
#  define _FILE_OFFSET_BITS	64
# endif
#else
# ifndef _FILE_OFFSET_BITS
#  define _FILE_OFFSET_BITS	32
# endif
#endif

/* UNIX98 stuff is always available.  */
#ifndef __USE_UNIX98
# define __USE_UNIX98	1
#endif

/* __EXTENSIONS__ corresponds to __USE_MISC.  */
#if defined(__USE_MISC) && !defined(__EXTENSIONS__)
# define __EXTENSIONS__
#endif

#endif /* _SYS_FEATURE_TESTS */
