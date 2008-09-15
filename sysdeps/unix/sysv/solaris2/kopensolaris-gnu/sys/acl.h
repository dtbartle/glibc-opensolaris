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
#include <sys/acl_impl.h>

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

typedef struct acl_info acl_t;

#define MIN_ACL_ENTRIES	4
#define MAX_ACL_ENTRIES	1024

/* aclent_t a_type values.  */
#define USER_OBJ	0x01
#define USER		0x02
#define GROUP_OBJ	0x04
#define GROUP		0x08
#define CLASS_OBJ	0x10
#define OTHER_OBJ	0x20
#define ACL_DEFAULT	0x1000
#define DEF_USER_OBJ	(ACL_DEFAULT | USER_OBJ)
#define DEF_USER	(ACL_DEFAULT | USER)
#define DEF_GROUP_OBJ	(ACL_DEFAULT | GROUP_OBJ)
#define DEF_GROUP	(ACL_DEFAULT | GROUP)
#define DEF_CLASS_OBJ	(ACL_DEFAULT | CLASS_OBJ)
#define DEF_OTHER_OBJ	(ACL_DEFAULT | OTHER_OBJ)

/* ace_t a_access_mask values.  */
#define ACE_READ_DATA		0x00000001
#define ACE_LIST_DIRECTORY	0x00000001
#define ACE_WRITE_DATA		0x00000002
#define ACE_ADD_FILE		0x00000002
#define ACE_APPEND_DATA		0x00000004
#define ACE_ADD_SUBDIRECTORY	0x00000004
#define ACE_READ_NAMED_ATTRS	0x00000008
#define ACE_WRITE_NAMED_ATTRS	0x00000010
#define ACE_EXECUTE		0x00000020
#define ACE_DELETE_CHILD	0x00000040
#define ACE_READ_ATTRIBUTES	0x00000080
#define ACE_WRITE_ATTRIBUTES	0x00000100
#define ACE_DELETE		0x00010000
#define ACE_READ_ACL		0x00020000
#define ACE_WRITE_ACL		0x00040000
#define ACE_WRITE_OWNER		0x00080000
#define ACE_SYNCHRONIZE		0x00100000

/* ace_t a_flags values.  */
#define ACE_FILE_INHERIT_ACE		0x0001
#define ACE_DIRECTORY_INHERIT_ACE	0x0002
#define ACE_NO_PROPAGATE_INHERIT_ACE	0x0004
#define ACE_INHERIT_ONLY_ACE		0x0008
#define ACE_SUCCESSFUL_ACCESS_ACE_FLAG	0x0010
#define ACE_FAILED_ACCESS_ACE_FLAG	0x0020
#define ACE_IDENTIFIER_GROUP		0x0040
#define ACE_INHERITED_ACE		0x0080
#define ACE_OWNER			0x1000
#define ACE_GROUP			0x2000
#define ACE_EVERYONE			0x4000

/* ace_t a_type values.  */
#define ACE_ACCESS_ALLOWED_ACE_TYPE	0
#define ACE_ACCESS_DENIED_ACE_TYPE	1
#define ACE_SYSTEM_AUDIT_ACE_TYPE	2
#define ACE_SYSTEM_ALARM_ACE_TYPE	3

#define ACL_AUTO_INHERIT	0x0001
#define ACL_PROTECTED		0x0002
#define ACL_DEFAULTED		0x0004

#define ACE_ALL_PERMS	(ACE_READ_DATA | ACE_LIST_DIRECTORY | \
	ACE_WRITE_DATA | ACE_ADD_FILE | ACE_APPEND_DATA | \
	ACE_ADD_SUBDIRECTORY | ACE_READ_NAMED_ATTRS | ACE_WRITE_NAMED_ATTRS | \
	ACE_EXECUTE | ACE_DELETE_CHILD | ACE_READ_ATTRIBUTES | \
	ACE_WRITE_ATTRIBUTES | ACE_DELETE | ACE_READ_ACL | ACE_WRITE_ACL | \
	ACE_WRITE_OWNER | ACE_SYNCHRONIZE)

#define ACE_READ_PERMS	(ACE_READ_DATA | ACE_READ_ACL | ACE_READ_ATTRIBUTES | \
	ACE_READ_NAMED_ATTRS)

#define ACE_WRITE_PERMS	(ACE_WRITE_DATA | ACE_APPEND_DATA | \
	ACE_WRITE_ATTRIBUTES | ACE_WRITE_NAMED_ATTRS)

#define ACE_MODIFY_PERMS	(ACE_READ_DATA | ACE_LIST_DIRECTORY | \
	ACE_WRITE_DATA | ACE_ADD_FILE | ACE_APPEND_DATA | \
	ACE_ADD_SUBDIRECTORY | ACE_READ_NAMED_ATTRS | ACE_WRITE_NAMED_ATTRS | \
	ACE_EXECUTE | ACE_DELETE_CHILD | ACE_READ_ATTRIBUTES | \
	ACE_WRITE_ATTRIBUTES | ACE_DELETE | ACE_READ_ACL | ACE_SYNCHRONIZE)

#define ACE_NFSV4_SUP_FLAGS	(ACE_FILE_INHERIT_ACE | \
	ACE_DIRECTORY_INHERIT_ACE | ACE_NO_PROPAGATE_INHERIT_ACE | \
	ACE_INHERIT_ONLY_ACE | ACE_IDENTIFIER_GROUP)

#define ACE_TYPE_FLAGS	(ACE_OWNER | ACE_GROUP | ACE_EVERYONE | \
	ACE_IDENTIFIER_GROUP)
#define ACE_INHERIT_FLAGS	(ACE_FILE_INHERIT_ACE | \
	ACE_DIRECTORY_INHERIT_ACE | ACE_NO_PROPAGATE_INHERIT_ACE | \
	ACE_INHERIT_ONLY_ACE)

#define UFSD_FREE	'0'
#define UFSD_ACL	'1'
#define UFSD_DFACL	'2'
#define ACE_ACL		'3'

#define ACL_NO_TRIVIAL	0x2

#define ACL_APPEND_ID	0x01
#define ACL_COMPACT_FMT	0x02
#define ACL_NORESOLVE	0x04
#define ACL_SID_FMT	0x08

#define GRP_ERROR	1
#define USER_ERROR	2
#define OTHER_ERROR	3
#define CLASS_ERROR	4
#define DUPLICATE_ERROR	5
#define MISS_ERROR	6
#define MEM_ERROR	7
#define ENTRY_ERROR	8

#define EACL_GRP_ERROR		GRP_ERROR
#define EACL_USER_ERROR		USER_ERROR
#define EACL_OTHER_ERROR	OTHER_ERROR
#define EACL_CLASS_ERROR	CLASS_ERROR
#define EACL_DUPLICATE_ERROR	DUPLICATE_ERROR
#define EACL_MISS_ERROR		MISS_ERROR
#define EACL_MEM_ERROR		MEM_ERROR
#define EACL_ENTRY_ERROR	ENTRY_ERROR
#define EACL_INHERIT_ERROR	9
#define EACL_FLAGS_ERROR	10
#define EACL_PERM_MASK_ERROR	11
#define EACL_COUNT_ERROR	12
#define EACL_INVALID_SLOT	13
#define EACL_NO_ACL_ENTRY	14
#define EACL_DIFF_TYPE		15
#define EACL_INVALID_USER_GROUP	16
#define EACL_INVALID_STR	17
#define EACL_FIELD_NOT_BLANK	18
#define EACL_INVALID_ACCESS_TYPE	19
#define EACL_UNKNOWN_DATA	20
#define EACL_MISSING_FIELDS	21
#define EACL_INHERIT_NOTDIR	22

__BEGIN_DECLS

extern int acl(char *__pathp, int __cmd, int __nentries, void *__aclbufp);

extern int facl(int __fildes, int __cmd, int __nentries, void *__aclbufp);

__END_DECLS

#endif /* _ACL_H */
