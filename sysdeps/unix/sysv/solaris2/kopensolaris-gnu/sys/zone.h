/* Declarations of zone functions and types.
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

#ifndef _SYS_ZONE_H
#define _SYS_ZONE_H

#define GLOBAL_ZONEID	0

/* Zone attributes.  */
#define ZONE_ATTR_ROOT		1
#define ZONE_ATTR_NAME		2
#define ZONE_ATTR_STATUS	3
#define ZONE_ATTR_PRIVSET	4
#define ZONE_ATTR_UNIQID	5
#define ZONE_ATTR_POOLID	6
#define ZONE_ATTR_INITPID	7
#define ZONE_ATTR_SLBL		8
#define ZONE_ATTR_INITNAME	9
#define ZONE_ATTR_BOOTARGS	10
#define ZONE_ATTR_BRAND		11
#define ZONE_ATTR_PHYS_MCAP	12
#define ZONE_ATTR_SCHED_CLASS	13
#define ZONE_ATTR_FLAGS		14

#endif /* _SYS_ZONE_H */
