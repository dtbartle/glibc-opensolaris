/* Declarations of procset structures.
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

#ifndef _SYS_PROCSET_H
#define _SYS_PROCSET_H

#include <sys/types.h>
#include <features.h>

#if defined __USE_MISC || defined __USE_XOPEN
typedef enum
{
	P_PID,
	P_PPID,
	P_PGID,
	P_SID,
	P_CID,
	P_UID,
	P_GID,
	P_ALL,
	P_LWPID,
	P_TASKID,
	P_PROJID,
	P_POOLID,
	P_ZONEID,
	P_CTID,
	P_CPUID,
	P_PSETID
} idtype_t;
#endif

#define	P_INITPID	1
#define	P_INITUID	0
#define	P_INITPGID	0

#ifdef __USE_MISC
typedef enum idop
{
	POP_DIFF,
	POP_AND,
	POP_OR,
	POP_XOR
} idop_t;
#endif

typedef struct procset
{
	idop_t p_op;
	idtype_t p_lidtype;
	id_t p_lid;
	idtype_t p_ridtype;
	id_t p_rid;
} procset_t;

#define	setprocset(psp, op, lidtype, lid, ridtype, rid) \
	(psp)->p_op			= (op); \
	(psp)->p_lidtype	= (lidtype); \
	(psp)->p_lid		= (lid); \
	(psp)->p_ridtype	= (ridtype); \
	(psp)->p_rid		= (rid);

#endif /* _SYS_PROCSET_H */
