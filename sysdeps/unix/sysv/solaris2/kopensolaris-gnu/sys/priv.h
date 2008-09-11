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

#ifndef _SYS_PRIV_H
#define _SYS_PRIV_H

#include <sys/types.h>

/* privsys codes */
#define	PRIVSYS_SETPPRIV	0
#define	PRIVSYS_GETPPRIV	1
#define	PRIVSYS_GETIMPLINFO	2
#define	PRIVSYS_SETPFLAGS	3
#define	PRIVSYS_GETPFLAGS	4
#define	PRIVSYS_ISSETUGID	5
#define	PRIVSYS_KLPD_REG	6
#define	PRIVSYS_KLPD_UNREG	7

typedef enum priv_op
{
	PRIV_ON,
	PRIV_OFF,
	PRIV_SET
} priv_op_t;

typedef uint32_t priv_chunk_t;
typedef struct priv_set priv_set_t;
typedef const char *priv_ptype_t;
typedef const char *priv_t;

typedef struct priv_impl_info
{
	uint32_t priv_headersize;
	uint32_t priv_flags;
	uint32_t priv_nsets;
	uint32_t priv_setsize;
	uint32_t priv_max;
	uint32_t priv_infosize;
	uint32_t priv_globalinfosize;
} priv_impl_info_t;

#define PRIV_DEBUG		0x0001
#define PRIV_AWARE		0x0002
#define PRIV_AWARE_INHERIT	0x0004
#define __PROC_PROTECT		0x0008
#define NET_MAC_AWARE		0x0010
#define NET_MAC_AWARE_INHERIT	0x0020
#define PRIV_XPOLICY		0x0080
#define PRIV_USER		(PRIV_DEBUG | NET_MAC_AWARE | \
	NET_MAC_AWARE_INHERIT |  PRIV_XPOLICY)

#define PRIV_IMPL_INFO_SIZE(p) \
	((p)->priv_headersize + (p)->priv_globalinfosize)

typedef struct priv_info
{
	uint32_t priv_info_type;
	uint32_t priv_info_size;
} priv_info_t;

typedef struct priv_info_set
{
	priv_info_t info;
	priv_chunk_t set[1];
} priv_info_set_t;

typedef struct priv_info_names
{
	priv_info_t info;
	int cnt;
	char names[1];
} priv_info_names_t;

#define PRIV_PRPRIV_INFO_OFFSET(p) \
	(sizeof (prpriv_t) + sizeof (priv_chunk_t)) * \
	((p)->pr_nsets * (p)->pr_setsize - 1)

#define PRIV_PRPRIV_SIZE(p) \
	(PRIV_PRPRIV_INFO_OFFSET(p) + (p)->pr_infosize)

#define PRIV_ALL	(-1)
#define PRIV_MULTIPLE	(-2)
#define PRIV_NONE	(-3)
#define PRIV_ALLZONE	(-4)
#define PRIV_GLOBAL	(-5)

#endif /* _SYS_PRIV_H */
