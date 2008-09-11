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

#ifndef _SYS_PORT_IMPL_H
#define _SYS_PORT_IMPL_H

#include <sys/port.h>

#define PORT_CREATE	0
#define PORT_ASSOCIATE	1
#define PORT_DISSOCIATE	2
#define PORT_SEND	3
#define PORT_SENDN	4
#define PORT_GET	5
#define PORT_GETN	6
#define PORT_ALERT	7
#define PORT_DISPATCH	8

#define PORT_SYS_NOPORT		0x100
#define PORT_SYS_NOSHARE	0x200

#define PORT_CODE_MASK		0xFF

#define PORT_SHARE_EVENT	0x01

#define PORT_MAX_LIST		8192

#endif /* _SYS_PORT_IMPL_H */
