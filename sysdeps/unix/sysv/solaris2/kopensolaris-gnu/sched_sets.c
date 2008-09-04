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

#include <schedP.h>
#include <errno.h>
#include <sys/priocntl.h>
#include <sched.h>

int
__sched_setscheduler (pid_t pid, int policy, const struct sched_param *param)
{
  int errval = __sched_setscheduler_id (P_PID, pid, policy,
      param->sched_priority);
  if (errval != 0)
    {
      __set_errno (errval);
      return -1;
    }
  return 0;
}

libc_hidden_def (__sched_setscheduler)
weak_alias (__sched_setscheduler, sched_setscheduler)
