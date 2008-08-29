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

#ifndef _SYS_SYNCH_H
#define _SYS_SYNCH_H

#define __need_synch_bits
#include <bits/synch.h>

/* general *_type values */
#define USYNC_THREAD	0x00
#define USYNC_PROCESS	0x01

/* mutex_type values */
#define LOCK_NORMAL		USYNC_THREAD
#define LOCK_SHARED		USYNC_PROCESS
#define LOCK_ERRORCHECK		0x02
#define LOCK_RECURSIVE		0x04
#define LOCK_PRIO_INHERIT	0x10
#define LOCK_PRIO_PROTECT	0x20
#define LOCK_ROBUST		0x40

/* deprecated */
#define USYNC_PROCESS_ROBUST	0x08

/* mutex_flag values */
#define	LOCK_OWNERDEAD		0x01
#define	LOCK_NOTRECOVERABLE	0x02
#define	LOCK_INITED		0x04
#define	LOCK_UNMAPPED		0x08

#define MUTEX_MAGIC		0x4d58 /* "MX" */
#define SEMA_MAGIC		0x534d /* "SM" */
#define COND_MAGIC		0x4356 /* "CV" */
#define RWL_MAGIC		0x5257 /* "RW" */

/* mutex initializers */
#define	DEFAULTMUTEX	\
	{{0, 0, 0, {USYNC_THREAD}, MUTEX_MAGIC}, \
	{{{0, 0, 0, 0, 0, 0, 0, 0}}}, 0}
#define	SHAREDMUTEX	\
	{{0, 0, 0, {USYNC_PROCESS}, MUTEX_MAGIC}, \
	{{{0, 0, 0, 0, 0, 0, 0, 0}}}, 0}
#define	RECURSIVEMUTEX	\
	{{0, 0, 0, {USYNC_THREAD|LOCK_RECURSIVE}, MUTEX_MAGIC}, \
	{{{0, 0, 0, 0, 0, 0, 0, 0}}}, 0}
#define	ERRORCHECKMUTEX	\
	{{0, 0, 0, {USYNC_THREAD|LOCK_ERRORCHECK}, MUTEX_MAGIC}, \
	{{{0, 0, 0, 0, 0, 0, 0, 0}}}, 0}
#define	RECURSIVE_ERRORCHECKMUTEX	\
	{{0, 0, 0, {USYNC_THREAD|LOCK_RECURSIVE|LOCK_ERRORCHECK}, \
	MUTEX_MAGIC}, {{{0, 0, 0, 0, 0, 0, 0, 0}}}, 0}

/* condition variable initializers */
#define	DEFAULTCV	\
	{{{0, 0, 0, 0}, USYNC_THREAD, COND_MAGIC}, 0}
#define	SHAREDCV	\
	{{{0, 0, 0, 0}, USYNC_PROCESS, COND_MAGIC}, 0}

/* semaphore initializers */
#define	DEFAULTSEMA	\
	{0, USYNC_THREAD, SEMA_MAGIC, {0, 0, 0}, {0, 0}}
#define	SHAREDSEMA	\
	{0, USYNC_PROCESS, SEMA_MAGIC, {0, 0, 0}, {0, 0}}

/* reader/writer lock initializers */
#define	DEFAULTRWLOCK	\
	{0, USYNC_THREAD, RWL_MAGIC, DEFAULTMUTEX, DEFAULTCV, DEFAULTCV}
#define	SHAREDRWLOCK	\
	{0, USYNC_PROCESS, RWL_MAGIC, SHAREDMUTEX, SHAREDCV, SHAREDCV}

#endif /* _SYS_SYNCH_H */
