/* Copyright (C) 1995, 1997, 2000, 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_MSG_H
#error "Never use <bits/msq.h> directly; include <sys/msg.h> instead."
#endif

#include <bits/types.h>
#include <bits/wordsize.h>

#define MSG_R	0400
#define MSG_W	0200

#define MSG_RWAIT	01000
#define MSG_WWAIT	02000

/* Define options for message queue functions.  */
#define MSG_NOERROR	010000	/* no error if message is too big */

/* Types used in the structure definition.  */
typedef unsigned long msgqnum_t;
typedef unsigned long msglen_t;

struct msg;

/* Structure of record for one message inside the kernel.
   The type `struct __msg' is opaque.  */
struct msqid_ds
{
  struct ipc_perm msg_perm;	/* structure describing operation permission */
  struct msg *msg_first;	/* pointer to first message on q */
  struct msg *msg_last;		/* pointer to last message on q */
  msglen_t msg_cbytes;		/* current # bytes on q */
  msgqnum_t msg_qnum;		/* number of messages currently on queue */
  msglen_t msg_qbytes;		/* max number of bytes allowed on queue */
  __pid_t msg_lspid;		/* pid of last msgsnd() */
  __pid_t msg_lrpid;		/* pid of last msgrcv() */
  __time_t msg_stime;		/* time of last msgsnd command */
#if __WORDSIZE == 32
  int32_t msg_pad1;
#endif
  __time_t msg_rtime;		/* time of last msgrcv command */
#if __WORDSIZE == 32
  int32_t msg_pad2;
#endif
  __time_t msg_ctime;		/* time of last change */
#if __WORDSIZE == 32
  int32_t msg_pad3;
#endif
  short msg_cv;
  short msg_qnum_cv;
  long msg_pad4[3];
};
