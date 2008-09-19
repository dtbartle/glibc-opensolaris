/* Calls to enable and disable swapping on specified locations.
    OpenSolaris version.
   Copyright (C) 1996, 1997, 2000, 2008 Free Software Foundation, Inc.
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

#ifndef __SYS_SWAP_H
#define __SYS_SWAP_H

/* Docs: http://docs.sun.com/app/docs/doc/816-5167/swapctl-2?a=view */

#include <features.h>
#include <bits/types.h>

/* swapctl cmd values.  */
#define	SC_ADD		1
#define	SC_LIST		2
#define	SC_REMOVE	3
#define	SC_GETNSWP	4
#define	SC_AINFO	5

/* swapctl arg for SC_ADD and SC_REMOVE.  */
typedef struct swapres
{
	char *sr_name;
#if defined(__USE_FILE_OFFSET64)
	__off64_t sr_start;
	__off64_t sr_length;
#else
	__off_t sr_start;
	__off_t sr_length;
#endif
} swapres_t;

typedef struct swapent
{
	char *ste_path;
#if defined(__USE_FILE_OFFSET64)
	__off64_t ste_start;
	__off64_t ste_length;
#else
	__off_t ste_start;
	__off_t ste_length;
#endif
	long ste_pages;
	long ste_free;
	int ste_flags;
} swapent_t;

/* ste_flags values.  */
#define ST_INDEL	1
#define ST_DOINGDEL	2

/* swapctl arg for SC_LIST.  */
typedef struct swaptable {
	int			swt_n;
	swapent_t	swt_ent[1];
} swaptbl_t;

__BEGIN_DECLS

/* Make the block special device PATH available to the system for swapping.
   This call is restricted to the super-user.  */
extern int swapon (__const char *__path) __THROW;

/* Stop using block special device PATH for swapping.  */
extern int swapoff (__const char *__path) __THROW;

extern int swapctl (int cmd, void *arg);

__END_DECLS

#endif /* sys/swap.h */
