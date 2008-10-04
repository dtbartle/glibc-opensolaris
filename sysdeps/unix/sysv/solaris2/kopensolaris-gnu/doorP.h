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

#ifndef _DOORP_H
#define _DOORP_H

#define DOOR_UNREF		0x01
#define DOOR_PRIVATE		0x02
#define DOOR_LOCAL		0x04
#define DOOR_REVOKED		0x08
#define DOOR_UNREF_MULTI	0x10
#define DOOR_IS_UNREF		0x20
#define DOOR_REFUSE_DESC	0x40
#define DOOR_NO_CANCEL		0x80

/* The default stack size is 1-2M so reserving 16K is reasonable.  */
#define DOOR_MIN_STACKSIZE	16384

#ifndef __ASSEMBLER__

#include <sys/types.h>

typedef struct door_desc door_desc_t;
typedef struct door_info door_info_t;
typedef struct door_arg door_arg_t;
typedef void door_server_func_t (door_info_t *);

typedef struct door_cred
  {
	uid_t dc_euid;
	gid_t dc_egid;
	uid_t dc_ruid;
	gid_t dc_rgid;
	pid_t dc_pid;
	int dc_resv[4];
  } door_cred_t;

typedef struct door_return_desc
  {
	door_desc_t *desc_ptr;
	unsigned int desc_num;
  } door_return_desc_t;

struct door_results
  {
	void *cookie;
	char *data_ptr;
	size_t data_size;
	door_desc_t *desc_ptr;
	size_t desc_num;
	void (*pc)(void);
	int nservers;
	door_info_t *door_info;
  };

int __door_return (long, long, long, long, long, long);

#endif /* __ASSEMBLER__ */

#endif /* _DOORP_H */
