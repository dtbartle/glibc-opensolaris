/* Copyright (C) 2009 Free Software Foundation, Inc.
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

#ifndef _SYS_MKDEV_H
#define _SYS_MKDEV_H

#include <sys/sysmacros.h>

#define ONBITSMAJOR	O_BITSMAJOR
#define ONBITSMINOR	O_BITSMINOR
#define OMAXMAJ		O_MAXMAJ
#define OMAXMIN		O_MAXMIN

#define NBITSMAJOR32	L_BITSMAJOR32
#define NBITSMINOR32	L_BITSMINOR32
#define MAXMAJ32	L_MAXMAJ32
#define MAXMIN32	L_MAXMIN32

#ifdef _LP64
# define NBITSMAJOR64	L_BITSMAJOR
# define NBITSMINOR64	L_BITSMINOR
# define MAXMAJ64	L_MAXMAJ
# define MAXMIN64	L_MAXMIN
#endif

#define NBITSMAJOR	L_BITSMAJOR
#define NBITSMINOR	L_BITSMINOR
#define MAXMAJ		L_MAXMAJ
#define MAXMIN		L_MAXMIN

#endif /* _SYS_MKDEV_H */
