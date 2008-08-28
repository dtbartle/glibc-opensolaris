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

#ifndef _SYS_EXACCT_H
#define _SYS_EXACCT_H

#include <sys/types.h>
#include <sys/procset.h>
#include <features.h>

#define EXACCT_VERSION	1

#define EUP_ALLOC	0x00
#define EUP_NOALLOC	0x01
#define EUP_ALLOC_MASK	0x02

#define EW_PARTIAL	0x01
#define EW_INTERVAL	0x02
#define EW_FINAL	0x04

enum
  {
	EP_RAW = 0,
#define EP_RAW	EP_RAW
	EP_EXACCT_OBJECT = 1
#define EP_EXACCT_OBJECT	EP_EXACCT_OBJECT
  };

enum
  {
	EXR_OK = 0,
#define EXR_OK	EXR_OK
	EXR_SYSCALL_FAIL = 1,
#define EXR_SYSCALL_FAIL	EXR_SYSCALL_FAIL
	EXR_CORRUPT_FILE = 2,
#define EXR_CORRUPT_FILE	EXR_CORRUPT_FILE
	EXR_EOF = 3,
#define EXR_EOF	EXR_EOF
	EXR_NO_CREATOR = 4,
#define EXR_NO_CREATOR	EXR_NO_CREATOR
	EXR_INVALID_BUF = 5,
#define EXR_INVALID_BUF	EXR_INVALID_BUF
	EXR_NOTSUPP = 6,
#define EXR_NOTSUPP	EXR_NOTSUPP
	EXR_UNKN_VERSION = 7,
#define EXR_UNKN_VERSION	EXR_UNKN_VERSION
	EXR_INVALID_OBJ = 8
#define EXR_INVALID_OBJ	EXR_INVALID_OBJ
  };

typedef enum
  {
	EO_ERROR = -1,
	EO_NONE = 0,
	EO_GROUP = 1,
	EO_ITEM = 2
  } ea_object_type_t;

#define EXACCT_MAX_BUFSIZE	(64 * 1024) /* 64 kb */

typedef uint64_t ea_size_t;
typedef uint32_t ea_catalog_t;

typedef struct ea_item
  {
	union
	  {
		uint8_t ei_u_uint8;
		uint16_t ei_u_uint16;
		uint32_t ei_u_uint32;
		uint64_t ei_u_uint64;
		double ei_u_double;
		char *ei_u_string;
		void *ei_u_object;
		void *ei_u_raw;
	  } ei_u;
	ea_size_t ei_size;
} ea_item_t;
#define ei_uint8	ei_u.ei_u_uint8
#define ei_uint16	ei_u.ei_u_uint16
#define ei_uint32	ei_u.ei_u_uint32
#define ei_uint64	ei_u.ei_u_uint64
#define ei_double	ei_u.ei_u_double
#define ei_string	ei_u.ei_u_string
#define ei_object	ei_u.ei_u_object
#define ei_raw		ei_u.ei_u_raw

typedef struct ea_group
  {
	uint32_t eg_nobjs;
	struct ea_object *eg_objs;
  } ea_group_t;

typedef struct ea_object
  {
	ea_object_type_t    eo_type;
	union
	  {
		ea_group_t eo_u_group;
		ea_item_t eo_u_item;
	  } eo_u;
	struct ea_object *eo_next;
	ea_catalog_t eo_catalog;
} ea_object_t;
#define eo_group	eo_u.eo_u_group
#define eo_item		eo_u.eo_u_item

__BEGIN_DECLS

size_t getacct (idtype_t, id_t, void *, size_t);

int putacct (idtype_t, id_t, void *, size_t, int);

int wracct (idtype_t, id_t, int);

__END_DECLS

#endif /* _SYS_EXACCT_H */
