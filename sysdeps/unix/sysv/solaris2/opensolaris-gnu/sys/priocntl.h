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

#ifndef _SYS_PRIOCNTL_H
#define _SYS_PRIOCNTL_H

#include <sys/types.h>
#include <sys/procset.h>

#define PC_VERSION		1

#define PC_GETCID		0
#define PC_GETCLINFO	1
#define PC_SETPARMS		2
#define PC_GETPARMS		3
#define PC_ADMIN		4
#define PC_GETPRIRANGE	5
#define PC_DONICE		6
#define PC_SETXPARMS	7
#define PC_GETXPARMS	8
#define PC_SETDFLCL		9
#define PC_GETDFLCL		10

#define PC_CLNULL		-1

#define PC_CLNMSZ		16
#define PC_CLINFOSZ		(32 / sizeof (int))
#define PC_CLPARMSZ		(32 / sizeof (int))

#define PC_GETNICE		0
#define PC_SETNICE		1

typedef struct pcinfo
{
	id_t pc_cid;
	char pc_clname[PC_CLNMSZ];
	int pc_clinfo[PC_CLINFOSZ];
} pcinfo_t;

typedef struct pcparms
{
	id_t pc_cid;
	int pc_clparms[PC_CLPARMSZ];
} pcparms_t;

typedef struct pcnice
{
	int pc_val;
	int pc_op;
} pcnice_t;

#define PC_VAPARMCNT	8
#define PC_KY_NULL		0
#define PC_KY_CLNAME	1

typedef struct pc_vaparm
{
	int pc_key;
	unsigned long long pc_parm;
} pc_vaparm_t;

typedef struct pc_vaparms
{
	unsigned int pc_vaparmscnt;
	pc_vaparm_t pc_parms[PC_VAPARMCNT];
} pc_vaparms_t;

typedef struct pcpri
{
	id_t pc_cid;
	pri_t pc_clpmax;
	pri_t pc_clpmin;
} pcpri_t;

typedef struct pcadmin
{
	id_t pc_cid;
	__caddr_t pc_cladmin;
} pcadmin_t;

#endif /* _SYS_PRIOCNTL_H */
