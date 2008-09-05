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

#ifndef _SYS_FILIO_H
#define _SYS_FILIO_H

#include <sys/ioctl.h>

#define	FIOCLEX		_IO('f', 1)
#define	FIONCLEX	_IO('f', 2)

#define	_FIOLFS		_IO('f', 64)
#define	_FIOLFSS	_IO('f', 65)
#define	_FIOFFS		_IO('f', 66)
#define	_FIOOBSOLETE67	_IO('f', 67)
#define	_FIOAI		_FIOOBSOLETE67
#define	_FIOSATIME	_IO('f', 68)
#define	_FIOSDIO	_IO('f', 69)
#define	_FIOGDIO	_IO('f', 70)
#define	_FIOIO		_IO('f', 71)
#define	_FIOISLOG	_IO('f', 72)
#define	_FIOISLOGOK	_IO('f', 73)
#define	_FIOLOGRESET	_IO('f', 74)
#define	_FIOISBUSY	_IO('f', 75)
#define	_FIODIRECTIO	_IO('f', 76)
#define	_FIOTUNE	_IO('f', 77)

#define	_FIOLOGENABLE		_IO('f', 87)
#define	_FIOLOGDISABLE		_IO('f', 88)
#define	_FIOSNAPSHOTCREATE	_IO('f', 89)
#define	_FIOSNAPSHOTDELETE	_IO('f', 90)
#define	_FIOGETSUPERBLOCK	_IO('f', 91)
#define	_FIOGETMAXPHYS		_IO('f', 92)
#define	_FIO_SET_LUFS_DEBUG	_IO('f', 93)
#define	_FIO_SET_LUFS_ERROR	_IO('f', 94)
#define	_FIO_GET_TOP_STATS	_IO('f', 95)
#define	_FIOSNAPSHOTCREATE_MULTI	_IO('f', 96)
#define	_FIO_SEEK_DATA		_IO('f', 97)
#define	_FIO_SEEK_HOLE		_IO('f', 98)
#define	_FIO_COMPRESSED		_IO('f', 99)

#define	FIONREAD	_IOR('f', 127, int)
#define	FIONBIO		_IOW('f', 126, int)
#define	FIOASYNC	_IOW('f', 125, int)
#define	FIOSETOWN	_IOW('f', 124, int)
#define	FIOGETOWN	_IOR('f', 123, int)

#endif /* _SYS_FILIO_H */
