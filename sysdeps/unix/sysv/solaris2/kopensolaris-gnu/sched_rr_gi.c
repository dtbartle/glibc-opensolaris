/* Copyright (C) 1996, 1997, 2009 Free Software Foundation, Inc.
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

#include <errno.h>
#include <schedP.h>
#include <sched.h>
#include <sys/priocntl.h>
#include <sys/types.h>


/* Get the SCHED_RR interval for the named process.  */
int
__sched_rr_get_interval (pid_t pid, struct timespec *t)
{
  if (pid == 0)
    pid = P_MYID;

  pcparms_t parms = {0};
  parms.pc_cid = PC_CLNULL;
  if (priocntl (P_PID, pid, PC_GETPARMS, &parms) == -1)
    return -1;
  int policy = __sched_class_to_policy (parms.pc_cid);
  if (policy == -1)
    return -1;

  t->tv_sec = 0;
  t->tv_nsec = 0;
  rtparms_t *rtparms = (rtparms_t *)parms.pc_clparms;
  fxparms_t *fxparms = (fxparms_t *)parms.pc_clparms;
  switch (policy)
    {
    case SCHED_FIFO:
    case SCHED_RR:
      if (rtparms->rt_tqnsecs != RT_TQINF)
        {
          t->tv_sec = rtparms->rt_tqsecs;
          t->tv_nsec = rtparms->rt_tqnsecs;
        }
      break;

    case SCHED_FX:
      if (fxparms->fx_tqnsecs != FX_TQINF)
        {
          t->tv_sec = fxparms->fx_tqsecs;
          t->tv_nsec = fxparms->fx_tqnsecs;
          break;
        }
    }

  return 0;
}

weak_alias (__sched_rr_get_interval, sched_rr_get_interval)
