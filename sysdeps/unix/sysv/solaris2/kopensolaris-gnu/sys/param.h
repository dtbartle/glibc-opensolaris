/* Copyright (C) 1995, 1996, 1997, 1998, 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H	1

#include <limits.h>

/* BSD names for some <limits.h> values.  */

#define	NBBY		CHAR_BIT
#ifndef	NGROUPS
# define NGROUPS		NGROUPS_MAX
#endif
#define	MAXSYMLINKS	20
#define	CANBSIZ		MAX_CANON
#define	NCARGS		ARG_MAX
#define MAXPATHLEN      PATH_MAX
#define NOFILE          OPEN_MAX


#include <sys/types.h>

/* Bit map related macros.  */
#define	setbit(a,i)	((a)[(i)/NBBY] |= 1<<((i)%NBBY))
#define	clrbit(a,i)	((a)[(i)/NBBY] &= ~(1<<((i)%NBBY)))
#define	isset(a,i)	((a)[(i)/NBBY] & (1<<((i)%NBBY)))
#define	isclr(a,i)	(((a)[(i)/NBBY] & (1<<((i)%NBBY))) == 0)

/* Macros for counting and rounding.  */
#ifndef howmany
# define howmany(x, y)	(((x)+((y)-1))/(y))
#endif
#define	roundup(x, y)	((((x)+((y)-1))/(y))*(y))
#define powerof2(x)	((((x)-1)&(x))==0)

/* Macros for min/max.  */
#define	MIN(a,b)	(((a)<(b))?(a):(b))
#define	MAX(a,b)	(((a)>(b))?(a):(b))

#define NODEV	(dev_t)-1

/* Unit of `st_blocks'.  */
#define DEV_BSIZE       512

/* Maximum hostname length.  */
#define MAXHOSTNAMELEN  256

#include <unistd.h>

#define PAGESIZE	sysconf(_SC_PAGESIZE)
#define MAXPID		(pid_t)sysconf(_SC_MAXPID)
#define MAXEPHUID	(uid_t)sysconf(_SC_EPHID_MAX)
#define MAXNAMELEN	256
#define TYPICALMAXPATHLEN	64
#define MAXLINKNAMELEN	32

#define UID_NOBODY	60001
#define GID_NOBODY	UID_NOBODY
#define GID_SYS		3
#define UID_DLADM	15
#define MAXUID		2147483647

#define NS_PACKETSZ	512
#define NS_MAXDNAME	1025
#define NS_MAXMSG	65535
#define NS_MAXCDNAME	255
#define NS_MAXLABEL	63
#define NS_HFIXEDSZ	12
#define NS_QFIXEDSZ	4
#define NS_RRFIXEDSZ	10
#define NS_INT32SZ	4
#define NS_INT16SZ	2
#define NS_INT8SZ	1
#define NS_INADDRSZ	4
#define NS_IN6ADDRSZ	16
#define NS_CMPRSFLGS	0xc0
#define NS_DEFAULTPORT	53

#define NGROUPS_UMIN	0
#define NGROUPS_UMAX	32
#define NGROUPS_MAX_DEFAULT	16

#include <sys/isa_defs.h>

#define MAXBSIZE	8192
#define DEV_BSIZE	512
#define DEV_BSHIFT	9
#define MAXFRAG		8
#ifdef  _LP64
# define MAXOFF_T	0x7fffffffffffffffl
# define MAXOFFSET_T	0x7fffffffffffffffl
#else
# define MAXOFF_T	0x7fffffffl
# define MAXOFFSET_T	0x7fffffffffffffffLL
#endif

#ifdef _LITTLE_ENDIAN
# define lobyte(X)	(((unsigned char *)&(X))[0])
# define hibyte(X)	(((unsigned char *)&(X))[1])
# define loword(X)	(((ushort_t *)&(X))[0])
# define hiword(X)	(((ushort_t *)&(X))[1])
#endif
#ifdef _BIG_ENDIAN
# define lobyte(X)	(((unsigned char *)&(X))[1])
# define hibyte(X)	(((unsigned char *)&(X))[0])
# define loword(X)	(((ushort_t *)&(X))[1])
# define hiword(X)	(((ushort_t *)&(X))[0])
#endif

#endif	/* sys/param.h */
