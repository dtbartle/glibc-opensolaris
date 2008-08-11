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

#ifndef _SYSTEMINFO_H
#define _SYSTEMINFO_H

#include <features.h>

#define SI_SYSNAME			1
#define SI_HOSTNAME			2
#define SI_RELEASE			3
#define SI_VERSION			4
#define SI_MACHINE			5
#define SI_ARCHITECTURE		6
#define SI_HW_SERIAL		7
#define SI_HW_PROVIDER		8
#define SI_SRPC_DOMAIN		9

#define SI_SET_HOSTNAME		258

#define SI_SET_SRPC_DOMAIN	265

#define SI_PLATFORM			513
#define SI_ISALIST			514
#define SI_DHCP_CACHE		515
#define SI_ARCHITECTURE_32	516
#define SI_ARCHITECTURE_64	517
#define SI_ARCHITECTURE_K	518
#define SI_ARCHITECTURE_NATIVE	519

__BEGIN_DECLS

extern long sysinfo (int command, char *buf, long count);

__END_DECLS

#endif /* _SYSTEMINFO_H */
