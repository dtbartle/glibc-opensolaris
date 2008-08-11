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

#ifndef _SYS_REBOOT_H
#define _SYS_REBOOT_H

#include <features.h>

#define	RB_AUTOBOOT			0
#define	RB_ASKNAME			0x00000001
#define	RB_SINGLE			0x00000002
#define	RB_NOSYNC			0x00000004
#define	RB_HALT				0x00000008
#define	RB_INITNAME			0x00000010
#define	RB_NOBOOTRC			0x00000020
#define	RB_DEBUG			0x00000040
#define	RB_DUMP				0x00000080
#define	RB_WRITABLE			0x00000100
#define	RB_STRING			0x00000200
#define	RB_CONFIG			0x00000800
#define	RB_RECONFIG			0x00001000
#define	RB_VERBOSE			0x00002000
#define	RB_FORTHDEBUG		0x00004000
#define	RB_FORTHDEBUGDBP	0x00008000
#define	RB_KMDB				0x00020000
#define	RB_NOBOOTCLUSTER	0x00040000
#define	RB_DEBUGENTER		0x00080000

__BEGIN_DECLS

/* Reboot or halt the system.  */
extern int reboot (int __howto, char *bootargs) __THROW;

__END_DECLS

#endif /* _SYS_REBOOT_H */
