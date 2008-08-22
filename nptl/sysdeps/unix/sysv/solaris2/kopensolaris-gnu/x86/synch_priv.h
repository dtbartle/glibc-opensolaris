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

#ifndef _SYNCH_PRIV_H
#define _SYNCH_PRIV_H

/* mutex helper macros */
#define mutex_type			flags.mbcp_type_un.mtype_rcount.count_type1
#define	mutex_magic			flags.magic
#define mutex_flag			flags.flag1
#define mutex_ceiling		flags.ceiling
#define mutex_rcount		flags.mbcp_type_un.mtype_rcount.count_type2
#define mutex_owner			data.data32.owner
#define mutex_lockword32	lock.lock32.lockword
#define mutex_lockword64	lock.owner64
#define mutex_lockbyte		lock.lock64.pad[7]
#define mutex_waiters		lock.lock64.pad[6]
#define mutex_cond_waiters	data.data32.cond_waiters
#define mutex_ownerpid		lock.lock32.ownerpid
#define RECURSION_MAX		255 /* UCHAR_MAX */
#define LOCKBYTE_SET        0x01
#define LOCKBYTE_UNSET      0x00
#define LOCKWORD32_SET_NO_WAITERS   0x01000000
#define LOCKWORD32_UNSET_NO_WAITERS 0x00000000
#define LOCKWORD64_SET_NO_WAITERS   0x0100000000000000
#define LOCKWORD64_UNSET_NO_WAITERS 0x0000000000000000
#define MUTEX_OWNERPID_SHIFT	0

/* condition variable helper macros */
#define cond_type			flags.type
#define cond_magic			flags.magic
#define cond_clockid		flags.flag[1]
#define cond_waiters_user	flags.flag[2]
#define cond_waiters_kernel	flags.flag[3]

/* semaphore helper macros */
#define sema_count		count
#define sema_type		type
#define sema_waiters	flags[7]

#endif /* _SYNCH_PRIV_H */
