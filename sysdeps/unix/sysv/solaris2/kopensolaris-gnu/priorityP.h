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

static inline
idtype_t __prio_to_p (enum __priority_which which)
{
  /* convert from PRIO_* to P_* */
  switch(which)
    {
    case PRIO_PROCESS:
      return P_PID;
    case PRIO_PGRP:
      return P_PGID;
    case PRIO_USER:
      return P_UID;
    case PRIO_GROUP:
      return P_GID;
    case PRIO_SESSION:
      return P_SID;
    case PRIO_LWP:
      return P_LWPID;
    case PRIO_TASK:
      return P_TASKID;
    case PRIO_PROJECT:
      return P_PROJID;
    case PRIO_ZONE:
      return P_ZONEID;
    case PRIO_CONTRACT:
      return P_CTID;
    default:
      __set_errno(EINVAL);
      return -1;
    }
}
