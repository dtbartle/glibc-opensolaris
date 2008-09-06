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

#ifndef _SYS_PORT_H
#define _SYS_PORT_H

#include <sys/types.h>

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

#define PORT_SOURCE_AIO		1
#define PORT_SOURCE_TIMER	2
#define PORT_SOURCE_USER	3
#define PORT_SOURCE_FD		4
#define PORT_SOURCE_ALERT	5
#define PORT_SOURCE_MQ		6
#define PORT_SOURCE_FILE	7

typedef struct port_event
  {
	int portev_events;
	unsigned short portev_source;
	unsigned short portev_pad;
	uintptr_t portev_object;
	void *portev_user;
  } port_event_t;

typedef struct  port_notify
  {
	int portnfy_port;
	void *portnfy_user;
  } port_notify_t;

typedef struct file_obj
  {
	struct timespec fo_atime;
    struct timespec fo_mtime;
    struct timespec fo_ctime;
    uintptr_t fo_pad[3];
    char *fo_name;
  } file_obj_t;

#define PORT_ALERT_SET		0x01
#define PORT_ALERT_UPDATE	0x02
#define PORT_ALERT_INVALID	(PORT_ALERT_SET | PORT_ALERT_UPDATE)

#define FILE_ACCESS		0x00000001
#define FILE_MODIFIED		0x00000002
#define FILE_ATTRIB		0x00000004
#define FILE_NOFOLLOW		0x10000000

#define FILE_DELETE		0x00000010
#define FILE_RENAME_TO		0x00000020
#define FILE_RENAME_FROM	0x00000040

#define UNMOUNTED	0x20000000

#define MOUNTEDOVER	0x40000000

#define FILE_EXCEPTION	(UNMOUNTED | FILE_DELETE | FILE_RENAME_TO | \
	FILE_RENAME_FROM | MOUNTEDOVER)

#endif /* _SYS_PORT_H */
