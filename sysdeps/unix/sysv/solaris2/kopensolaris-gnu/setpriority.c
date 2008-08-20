/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>.

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

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/procset.h>
#include <sys/priocntl.h>
#include <errno.h>

int
setpriority (enum __priority_which which, id_t who, int prio)
{
  /* convert from PRIO_* to P_* */
  idtype_t type;
  switch(which)
    {
    case PRIO_PROCESS:
      type = P_PID;
    case PRIO_PGRP:
      type = P_PGID;
    case PRIO_USER:
      type = P_UID;
    case PRIO_GROUP:
      type = P_GID;
    case PRIO_SESSION:
      type = P_SID;
    case PRIO_LWP:
      type = P_LWPID;
    case PRIO_TASK:
      type = P_TASKID;
    case PRIO_PROJECT:
      type = P_PROJID;
    case PRIO_ZONE:
      type = P_ZONEID;
    case PRIO_CONTRACT:
      type = P_CTID;
    default:
      __set_errno(EINVAL);
      return -1;
    }

  if(who == 0)
    who = P_MYID;

  if(prio > NZERO)
    prio = NZERO;
  else if(prio < NZERO)
    prio = -NZERO;

  pcnice_t nice;
  nice.pc_val = prio;
  nice.pc_op = PC_SETNICE;
  return priocntl (type, who, PC_DONICE, &nice);
}

libc_hidden_def (setpriority)
