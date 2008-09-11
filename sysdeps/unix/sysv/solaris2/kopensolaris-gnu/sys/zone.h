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

#include <sys/types.h>
#include <sys/priv.h>

typedef struct _mac_label_impl m_label_t;
typedef m_label_t bslabel_t;

/* Subcall numbers.  */
#define ZONE_CREATE	0
#define ZONE_DESTROY	1
#define ZONE_GETATTR	2
#define ZONE_ENTER	3
#define ZONE_LIST	4
#define ZONE_SHUTDOWN	5
#define ZONE_LOOKUP	6
#define ZONE_BOOT	7
#define ZONE_VERSION	8
#define ZONE_SETATTR	9
#define ZONE_ADD_DATALINK	10
#define ZONE_DEL_DATALINK	11
#define ZONE_CHECK_DATALINK	12
#define ZONE_LIST_DATALINK	13

#define GLOBAL_ZONEID	0
#define MIN_ZONEID	0
#define MIN_USERZONEID	1
#define MAX_ZONEID	9999
#define ZONEID_WIDTH	4
#define ALL_ZONES	(-1)

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

#define ZONENAME_MAX		64

typedef struct
  {
	const char *zone_name;
	const char *zone_root;
	const struct priv_set *zone_privs;
	size_t zone_privssz;
	const char *rctlbuf;
	size_t rctlbufsz;
	int *extended_error;
	const char *zfsbuf;
	size_t zfsbufsz;
	int match;
	uint32_t doi;
	const bslabel_t *label;
	int flags;
  } zone_def;

#endif /* _SYS_ZONE_H */
