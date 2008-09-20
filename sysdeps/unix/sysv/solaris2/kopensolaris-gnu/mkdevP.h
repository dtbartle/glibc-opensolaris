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

#ifndef _MKDEVP_H
#define _MKDEVP_H

#include <sys/feature_tests.h>

#define ONBITSMAJOR	7
#define ONBITSMINOR	8
#define OMAXMAJ		0x7f
#define OMAXMIN		0xff

#ifdef _LP64
# define NBITSMAJOR	32
# define NBITSMINOR	32
# define MAXMAJ		0xfffffffful
# define MAXMIN		0xfffffffful
#else
# define NBITSMAJOR	14
# define NBITSMINOR	18
# define MAXMAJ		0x3ffful
# define MAXMIN		0x3fffful
#endif

#define OLDDEV	0
#define NEWDEV	1

#endif /* _MKDEVP_H */
