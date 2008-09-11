/* Declarations of privilege functions and types.
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

#ifndef _SYS_DOOR_H
#define _SYS_DOOR_H

#include <sys/types.h>
#include <sys/isa_defs.h>

#define DOOR_CREATE	0
#define DOOR_REVOKE	1
#define DOOR_INFO	2
#define DOOR_CALL	3
#define DOOR_BIND	6
#define DOOR_UNBIND	7
#define DOOR_UNREFSYS	8
#define DOOR_UCRED	9
#define DOOR_RETURN	10
#define DOOR_GETPARAM	11
#define DOOR_SETPARAM	12

#define DOOR_INVAL	-1
#define DOOR_UNREF_DATA	((void *)1)

#define DOOR_QUERY	-2

#define DOOR_UNREF		0x01
#define DOOR_PRIVATE		0x02
#define DOOR_UNREF_MULTI	0x10
#define DOOR_REFUSE_DESC	0x40
#define DOOR_NO_CANCEL		0x80

#define DOOR_LOCAL	0x04
#define DOOR_REVOKED	0x08
#define DOOR_IS_UNREF	0x20

#define DOOR_CREATE_MASK	(DOOR_UNREF | DOOR_PRIVATE | \
	DOOR_UNREF_MULTI | DOOR_REFUSE_DESC | DOOR_NO_CANCEL)
#define DOOR_KI_CREATE_MASK	(DOOR_UNREF | DOOR_UNREF_MULTI)

#define DOOR_ATTR_MASK	(DOOR_CREATE_MASK | DOOR_LOCAL | DOOR_REVOKED | \
	DOOR_IS_UNREF)

#define DOOR_DESCRIPTOR	0x10000
#define DOOR_RELEASE	0x40000
#define DOOR_DELAY	0x80000
#define DOOR_UNREF_ACTIVE	0x100000

#define DOOR_PARAM_DESC_MAX	1
#define DOOR_PARAM_DATA_MAX	2
#define DOOR_PARAM_DATA_MIN	3

typedef unsigned long long door_ptr_t;
typedef unsigned int door_attr_t;
typedef unsigned long long door_id_t;

#if _LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4
# pragma pack(4)
#endif

typedef struct door_info
  {
	pid_t di_target;
	door_ptr_t di_proc;
	door_ptr_t di_data;
	door_attr_t di_attributes;
	door_id_t di_uniquifier;
	int di_resv[4];
  } door_info_t;

typedef struct door_desc
  {
	door_attr_t d_attributes;
	union
	  {
		struct
		  {
			int d_descriptor;
			door_id_t d_id;
		  } d_desc;
		int d_resv[5];
	  } d_data;
} door_desc_t;

#if _LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4
# pragma pack()
#endif

typedef struct door_cred
  {
	uid_t dc_euid;
	gid_t dc_egid;
	uid_t dc_ruid;
	gid_t dc_rgid;
	pid_t dc_pid;
	int dc_resv[4];
  } door_cred_t;

typedef struct door_arg
  {
	char *data_ptr;
	size_t data_size;
	door_desc_t *desc_ptr;
	unsigned int desc_num;
	char *rbuf;
	size_t rsize;
  } door_arg_t;

struct door_results
  {
	void *cookie;
	char *data_ptr;
	size_t data_size;
	door_desc_t *desc_ptr;
	size_t desc_num;
	void (*pc)();
	int nservers;
	door_info_t *door_info;
  };

typedef struct door_return_desc
  {
    door_desc_t *desc_ptr;
    unsigned int desc_num;
  } door_return_desc_t;

#endif /* _SYS_DOOR_H */
