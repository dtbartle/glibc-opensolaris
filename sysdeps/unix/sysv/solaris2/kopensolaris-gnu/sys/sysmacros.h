/* Definitions of macros to access `dev_t' values.
   Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H

#include <sys/isa_defs.h>
#include <sys/param.h>

/* Number of major/minor device bits.  */
#define O_BITSMAJOR	7
#define O_BITSMINOR	8
#ifdef _LP64
# define L_BITSMAJOR	32
# define L_BITSMINOR	32
#else
# define L_BITSMAJOR	14
# define L_BITSMINOR	18
#endif

/* Maximum major/minor values.  */
#define O_MAXMAJ	0x7F
#define O_MAXMIN	0xFF
#ifdef _LP64
# define L_MAXMAJ	0xFFFFFFFF
# define L_MAXMIN	0xFFFFFFFF
#else
# define L_MAXMAJ	0x3FFF
# define L_MAXMIN	0x3FFFF
#endif

/* Macros to get minor/major numbers.  */
#define major(x)	((((unsigned)(x)) >> O_BITSMINOR) & O_MAXMAJ)
#define minor(x)	((x) & O_MAXMIN)

/* Make dev.  */
#define makedev(x, y)	(unsigned short)(((x) << O_BITSMINOR) | \
	((y) & O_MAXMIN))

/* Convert new dev to old dev.  */
#define cmpdev(x)	((((x) >> L_BITSMAJOR) > O_MAXMAJ) || \
	(((x) & L_MAXMAJ) > O_MAXMAJ) ? NODEV : ((((x) >> L_BITSMAJOR) << \
	O_BITSMINOR) | (x) & O_MAXMIN))

/* Convert old dev to new dev.  */
#define expdev(x)	((((x) >> O_BITSMINOR) << L_BITSMINOR) | \
	((x) & O_MAXMIN))

/* Round up assuming y is power-of-2 aligned.  */
#define P2ROUNDUP(x, y)		(-(-(x) & -(y)))

#endif /* _SYS_SYSMACROS_H */
