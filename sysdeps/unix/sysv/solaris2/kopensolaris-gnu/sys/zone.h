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
#include <sys/uadmin.h>
#include <sys/param.h>
#include <sys/tsol/label.h>

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

/* Miscellaneous.  */
#define GLOBAL_ZONEID	0
#define GLOBAL_ZONENAME	"global"
#define MIN_ZONEID	0
#define MIN_USERZONEID	1
#define MAX_ZONEID	9999
#define ZONEID_WIDTH	4
#define ALL_ZONES	(-1)
#define ZONENAME_MAX	64
#define ZONENAME_REGEXP	"[a-zA-Z0-9][-_.a-zA-Z0-9]{0,62}"
#define ZONES_TMPDIR	"/var/run/zones"
#define ZONE_DOOR_PATH	ZONES_TMPDIR "/%s.zoneadmd_door"

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
#define ZONE_ATTR_BRAND_ATTRS	32768

/* Zone event strings. */
#define ZONE_EVENT_CHANNEL		"com.sun:zones:status"
#define ZONE_EVENT_STATUS_CLASS		"status"
#define ZONE_EVENT_STATUS_SUBCLASS	"change"
#define ZONE_EVENT_UNINITIALIZED	"uninitialized"
#define ZONE_EVENT_INITIALIZED		"initialized"
#define ZONE_EVENT_READY		"ready"
#define ZONE_EVENT_RUNNING		"running"
#define ZONE_EVENT_SHUTTING_DOWN	"shutting_down"

#define ZONE_CB_NAME		"zonename"
#define ZONE_CB_NEWSTATE	"newstate"
#define ZONE_CB_OLDSTATE	"oldstate"
#define ZONE_CB_TIMESTAMP	"when"
#define ZONE_CB_ZONEID		"zoneid"

/* Zone flags.  */
#define ZF_HASHED_LABEL	0x2
#define ZF_IS_SCRATCH	0x4
#define ZF_NET_EXCL	0x8

/* Zone create flags.  */
#define ZCF_NET_EXCL	0x1

/* Exit values.  */
#define ZONE_SUBPROC_OK			0
#define ZONE_SUBPROC_USAGE		253
#define ZONE_SUBPROC_NOTCOMPLETE	254
#define ZONE_SUBPROC_FATAL		255

typedef enum
  {
	ZONE_IS_UNINITIALIZED = 0,
	ZONE_IS_INITIALIZED,
	ZONE_IS_READY,
	ZONE_IS_BOOTING,
	ZONE_IS_RUNNING,
	ZONE_IS_SHUTTING_DOWN,
	ZONE_IS_EMPTY,
	ZONE_IS_DOWN,
	ZONE_IS_DYING,
	ZONE_IS_DEAD
  } zone_status_t;
#define ZONE_MIN_STATE	ZONE_IS_UNINITIALIZED
#define ZONE_MAX_STATE	ZONE_IS_DEAD

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

typedef enum zone_cmd
  {
	Z_READY,
	Z_BOOT,
	Z_FORCEBOOT,
	Z_REBOOT,
	Z_HALT,
	Z_NOTE_UNINSTALLING,
	Z_MOUNT,
	Z_FORCEMOUNT,
	Z_UNMOUNT
  } zone_cmd_t;

typedef struct zone_cmd_arg
  {
	uint64_t uniqid;
	zone_cmd_t cmd;
	uint32_t _pad;
	char locale[MAXPATHLEN];
	char bootbuf[BOOTARGS_MAX];
  } zone_cmd_arg_t;

typedef struct zone_cmd_rval
  {
	int rval;
	char errbuf[1];
  } zone_cmd_rval_t;

#endif /* _SYS_ZONE_H */
