/* Copyright (C) 1995, 1996, 1997, 1999, 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_IPC_H
# error "Never use <bits/ipc.h> directly; include <sys/ipc.h> instead."
#endif

#include <bits/types.h>
#include <bits/wordsize.h>

/* Mode bits for `msgget', `semget', and `shmget'.  */
#define IPC_ALLOC	0100000		/* entry currently allocated */
#define IPC_CREAT	0001000		/* create key if key does not exist */
#define IPC_EXCL	0002000		/* fail if key exists */
#define IPC_NOWAIT	0004000		/* return error on wait */

/* Control commands for `msgctl', `semctl', and `shmctl'.  */
#define IPC_RMID	10		/* remove identifier */
#define IPC_SET		11		/* set `ipc_perm' options */
#define IPC_STAT	12		/* get `ipc_perm' options */

/* Special key values.  */
#define IPC_PRIVATE	((key_t) 0)	/* private key */


/* Data structure used to pass permission information to IPC operations.  */
struct ipc_perm
  {
    __uid_t uid;			/* owner's user ID */
    __gid_t gid;			/* owner's group ID */
    __uid_t cuid;			/* creator's user ID */
    __gid_t cgid;			/* creator's group ID */
    __mode_t mode;			/* read/write permission */
    unsigned int seq;		/* slot usage sequence number */
    __key_t key;			/* key */
#if __WORDSIZE == 32
    int pad[4];
#endif
  };
