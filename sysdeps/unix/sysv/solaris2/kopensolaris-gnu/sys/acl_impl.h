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

#ifndef _ACL_IMPL_H
#define _ACL_IMPL_H

#include <sys/acl.h>

#define ACL_IS_TRIVIAL	0x10000
#define ACL_IS_DIR	0x20000

typedef enum acl_type
  {
	ACLENT_T = 0,
	ACE_T = 1
  } acl_type_t;

struct acl_info
  {
	acl_type_t acl_type;
	int acl_cnt;
	int acl_entry_size;
	int acl_flags;
	void *acl_aclp;
  };

#endif /* _SYS_ACL_IMPL_H */
