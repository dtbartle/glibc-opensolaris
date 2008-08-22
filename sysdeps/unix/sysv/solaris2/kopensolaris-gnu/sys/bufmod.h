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

#ifndef _SYS_BUFMOD_H
#define _SYS_BUFMOD_H

#include <sys/types.h>

#define SBIOC		('B' << 8)
#define SBIOCSTIME	(SBIOC|1)
#define SBIOCGTIME	(SBIOC|2)
#define SBIOCCTIME	(SBIOC|3)
#define SBIOCSCHUNK	(SBIOC|4)
#define SBIOCGCHUNK	(SBIOC|5)
#define SBIOCSSNAP	(SBIOC|6)
#define SBIOCGSNAP	(SBIOC|7)
#define SBIOCSFLAGS	(SBIOC|8)
#define SBIOCGFLAGS	(SBIOC|9)

struct sb_hdr
{
	unsigned int sbh_origlen;
	unsigned int sbh_msglen;
	unsigned int sbh_totlen;
	unsigned int sbh_drops;
	struct timeval sbh_timestamp;
};

#define SB_SEND_ON_WRITE	0x01
#define SB_NO_HEADER		0x02
#define SB_NO_PROTO_CVT		0x04
#define SB_DEFER_CHUNK		0x08
#define SB_NO_DROPS			0x10

#define SB_DFLT_CHUNK		8192

#define SB_FRCVD			1

#endif /* _SYS_BUFMOD_H */
