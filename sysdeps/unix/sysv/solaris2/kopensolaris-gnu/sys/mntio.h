/* Copyright (C) 2009 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>, 2009.

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

#ifndef _SYS_MNTIO_H
#define _SYS_MNTIO_H

#include <sys/stat.h>
#include <sys/types.h>

#define MNTIOC			('m' << 8)
#define MNTIOC_NMNTS		(MNTIOC|1)
#define MNTIOC_GETDEVLIST	(MNTIOC|2)
#define MNTIOC_SETTAG		(MNTIOC|3)
#define MNTIOC_CLRTAG		(MNTIOC|4)
#define MNTIOC_SHOWHIDDEN	(MNTIOC|6)
#define MNTIOC_GETMNTENT	(MNTIOC|7)

struct mnttagdesc
  {
	unsigned int mtd_major;
	unsigned int mtd_minor;
	char *mtd_mntpt;
	char *mtd_tag;
  };

struct mntlookup
  {
	size_t mtl_mntpt_off;
	char *mtl_mntpt;
	major_t mtl_major;
	minor_t mtl_minor;
	__ino64_t mtl_ino;
	char mtl_fstype[_ST_FSTYPSZ];
  };

#endif /* _SYS_MNTIO_H */
