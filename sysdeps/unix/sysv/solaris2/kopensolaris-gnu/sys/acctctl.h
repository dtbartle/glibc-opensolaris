/* Declarations of acctlctl function and types.
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

#ifndef _SYS_ACCTCTL_H
#define _SYS_ACCTCTL_H

#include <sys/types.h>
#include <features.h>

#define AC_PROC		(0x1 << 28)
#define AC_TASK		(0x2 << 28)
#define AC_FLOW		(0x4 << 28)
#define AC_MODE(x)	((x) & 0xf0000000)

#define AC_FILE_SET	0x01
#define AC_FILE_GET	0x02
#define AC_RES_SET	0x04
#define AC_RES_GET	0x08
#define AC_STATE_SET	0x10
#define AC_STATE_GET	0x20
#define AC_OPTION(x)	((x) & 0x0fffffff)

enum
  {
	AC_NONE = 0,
#define AC_NONE			AC_NONE
	AC_PROC_PID = 1,
#define AC_PROC_PID		AC_PROC_PID
	AC_PROC_UID = 2,
#define AC_PROC_UID		AC_PROC_UID
	AC_PROC_GID = 3,
#define AC_PROC_GID		AC_PROC_GID
	AC_PROC_PROJID = 4,
#define AC_PROC_PROJID		AC_PROC_PROJID
	AC_PROC_TASKID = 5,
#define AC_PROC_TASKID		AC_PROC_TASKID
	AC_PROC_CPU = 6,
#define AC_PROC_CPU		AC_PROC_CPU
	AC_PROC_TIME = 7,
#define AC_PROC_TIME		AC_PROC_TIME
	AC_PROC_COMMAND = 8,
#define AC_PROC_COMMAND		AC_PROC_COMMAND
	AC_PROC_TTY = 9,
#define AC_PROC_TTY		AC_PROC_TTY
	AC_PROC_HOSTNAME = 10,
#define AC_PROC_HOSTNAME	AC_PROC_HOSTNAME
	AC_PROC_MICROSTATE = 11,
#define AC_PROC_MICROSTATE	AC_PROC_MICROSTATE
	AC_PROC_FLAG = 12,
#define AC_PROC_FLAG		AC_PROC_FLAG
	AC_PROC_ANCPID = 13,
#define AC_PROC_ANCPID		AC_PROC_ANCPID
	AC_PROC_WAIT_STATUS = 14,
#define AC_PROC_WAIT_STATUS	AC_PROC_WAIT_STATUS
	AC_PROC_ZONENAME = 15,
#define AC_PROC_ZONENAME	AC_PROC_ZONENAME
	AC_PROC_MEM = 16,
#define AC_PROC_MEM		AC_PROC_MEM
	AC_PROC_MAX_RES = 17
#define AC_PROC_MAX_RES		AC_PROC_MAX_RES
  };

enum
  {
	AC_TASK_TASKID = 1,
#define AC_TASK_TASKID		AC_TASK_TASKID
	AC_TASK_PROJID = 2,
#define AC_TASK_PROJID		AC_TASK_PROJID
	AC_TASK_CPU = 3,
#define AC_TASK_CPU		AC_TASK_CPU
	AC_TASK_TIME = 4,
#define AC_TASK_TIME		AC_TASK_TIME
	AC_TASK_HOSTNAME = 5,
#define AC_TASK_HOSTNAME	AC_TASK_HOSTNAME
	AC_TASK_MICROSTATE = 6,
#define AC_TASK_MICROSTATE	AC_TASK_MICROSTATE
	AC_TASK_ANCTASKID = 7,
#define AC_TASK_ANCTASKID	AC_TASK_ANCTASKID
	AC_TASK_ZONENAME = 8
#define AC_TASK_ZONENAME	AC_TASK_ZONENAME
#define A_TASK_MAX_RES		AC_TASK_ZONENAME
  };

enum
  {
	AC_FLOW_SADDR = 1,
#define AC_FLOW_SADDR		AC_FLOW_SADDR
	AC_FLOW_DADDR = 2,
#define AC_FLOW_DADDR		AC_FLOW_DADDR
	AC_FLOW_SPORT = 3,
#define AC_FLOW_SPORT		AC_FLOW_DPORT
	AC_FLOW_DPORT =  4,
#define AC_FLOW_DPORT		AC_FLOW_DPORT
	AC_FLOW_PROTOCOL = 5,
#define AC_FLOW_PROTOCOL	AC_FLOW_PROTOCOL
	AC_FLOW_DSFIELD = 6,
#define AC_FLOW_DSFIELD		AC_FLOW_DSFIELD
	AC_FLOW_CTIME = 7,
#define AC_FLOW_CTIME		AC_FLOW_CTIME
	AC_FLOW_LSEEN = 8,
#define AC_FLOW_LSEEN		AC_FLOW_LSEEN
	AC_FLOW_NBYTES = 9,
#define AC_FLOW_NBYTES		AC_FLOW_NBYTES
	AC_FLOW_NPKTS = 10,
#define AC_FLOW_NPKTS		AC_FLOW_NPKTS
	AC_FLOW_PROJID = 11,
#define AC_FLOW_PROJID		AC_FLOW_PROJID
	AC_FLOW_UID = 12,
#define AC_FLOW_UID		AC_FLOW_UID
	AC_FLOW_ANAME = 13
#define AC_FLOW_ANAME		AC_FLOW_ANAME
#define AC_FLOW_MAX_RES		AC_FLOW_ANAME
  };

#define AC_MAX_RES_TMP	MAX (AC_PROC_MAX_RES, AC_TASK_MAX_RES)
#define AC_MAX_RES	MAX (AC_MAX_RES_TMP, AC_FLOW_MAX_RES)
#define AC_MASK_SZ	BT_BITOUL (AC_MAX_RES + 1)

enum
  {
	AC_OFF = 0,
#define AC_OFF		AC_OFF
	AC_ON = 1
#define AC_ON		AC_ON
  };

typedef struct ac_res
  {
	int ar_id;
	int ar_state;
  } ac_res_t;

__BEGIN_DECLS

extern int acctctl (int, void *, size_t);

__END_DECLS

#endif /* _SYS_ACCTCTL_H */
