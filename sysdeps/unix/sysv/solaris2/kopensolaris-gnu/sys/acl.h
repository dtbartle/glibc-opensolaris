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

#ifndef _ACL_H
#define _ACL_H

#include <features.h>
#include <sys/types.h>

/* cmd values.  */
#define GETACL		1
#define SETACL		2
#define GETACLCNT	3
#define ACE_GETACL	4
#define ACE_SETACL	5
#define ACE_GETACLCNT	6

/* Used by UFS.  */
typedef struct acl
{
	int a_type;
	unsigned int a_id;
	o_mode_t a_perm;
} aclent_t;

/* Used by ZFS and NFSv4.  */
typedef struct ace {
    unsigned int a_who;
    uint32_t a_access_mask;
    uint16_t a_flags;
    uint16_t a_type;
} ace_t;

// TODO: missing lots of constants

__BEGIN_DECLS

extern int acl(char *__pathp, int __cmd, int __nentries, void *__aclbufp);

extern int facl(int __fildes, int __cmd, int __nentries, void *__aclbufp);

__END_DECLS

#endif /* _ACL_H */
