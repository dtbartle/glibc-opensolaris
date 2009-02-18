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

#include <inline-syscall.h>
#include <schedP.h>
#include <sys/priocntl.h>
#include <bits/libc-lock.h>

/* XXX: We don't deal with custom schedulers.  */

/* XXX: We only set sched_param.sched_priority.  */

/* TODO: Cleanup errno usage.  */

/* Note: Because SCHED_FIFO and SCHED_RR map to the same scheduler, we need to
   do additional work if we encounter either schedulers.  */

/* SCHED_SYS has cid == 0 always. */
static pcinfo_t __sched_policies[] = {
  {-1, "TS", {0}},	/* SCHED_OTHER */
  {-1, "RT", {0}},	/* SCHED_FIFO */
  {-1, "RT", {0}},	/* SCHED_RR */
  {0, "SYS", {0}},	/* SCHED_SYS */
  {-1, "IA", {0}},	/* SCHED_IA */
  {-1, "FSS", {0}},	/* SCHED_FSS */
  {-1, "FX", {0}},	/* SCHED_FX */
};

__libc_lock_define_initialized (static, lock);

int __sched_policy_to_class (int policy)
{
  if (policy < 0 || policy >= _SCHED_NEXT)
    {
      __set_errno (EINVAL);
      return -1;
    }

  __libc_lock_lock (lock);

  /* Try to get cid from clname.  */
  if (__sched_policies[policy].pc_cid == -1)
    {
      priocntl (0, 0, PC_GETCID, &__sched_policies[policy]);
    }

  __libc_lock_unlock (lock);

  return __sched_policies[policy].pc_cid;
}

int __sched_class_to_policy (int cid)
{
  int policy = -1;

  __libc_lock_lock (lock);

  for (int i = 0; i < _SCHED_NEXT; i++)
    {
      if (__sched_policies[i].pc_cid == -1)
        priocntl (0, 0, PC_GETCID, &__sched_policies[i]);

      if (__sched_policies[i].pc_cid == cid)
        {
          policy = i;
          break;
        }
    }

  __libc_lock_unlock (lock);

  if (policy == -1)
    __set_errno (EINVAL);

  return policy;
}

int __sched_getparam_id (int idtype, id_t id, int *priority)
{
  pcprio_t prio;
  prio.pc_op = PC_GETPRIO;
  int result = priocntl (idtype, id, PC_DOPRIO, &prio);
  if (result != 0)
    return errno;

  *priority = prio.pc_val;

  return 0;
}

int __sched_setparam_id (int idtype, id_t id, int priority)
{
  /* We need pc_cid to be valid in the PC_SETPRIO call.  */
  pcprio_t prio;
  prio.pc_op = PC_GETPRIO;
  int result = priocntl (idtype, id, PC_DOPRIO, &prio);
  if (result != 0)
    return errno;

  prio.pc_op = PC_SETPRIO;
  prio.pc_val = priority;
  result = priocntl (idtype, id, PC_DOPRIO, &prio);
  if (result != 0)
    return errno;

  return 0;
}

int __sched_getscheduler_id (int idtype, id_t id, int *policy, int *priority)
{
  pcprio_t prio;
  prio.pc_op = PC_GETPRIO;
  int result = priocntl (idtype, id, PC_DOPRIO, &prio);
  if (result != 0)
    return errno;

  *policy = __sched_class_to_policy (prio.pc_cid);
  if (*policy == -1)
    return errno;
  if (priority)
    *priority = prio.pc_val;

  if (*policy == SCHED_FIFO || *policy == SCHED_RR)
    {
      pcparms_t parms;
      parms.pc_cid = PC_CLNULL;
      if (priocntl (idtype, id, PC_GETPARMS, parms) == -1)
        return errno;
      *policy = (((rtparms_t *)parms.pc_clparms)->rt_tqnsecs == RT_TQINF) ?
        SCHED_FIFO : SCHED_RR;
    }

  return 0;
}

int __sched_setscheduler_id (int idtype, id_t id, int policy, int priority)
{
  pcprio_t prio;
  prio.pc_op = PC_SETPRIO;
  prio.pc_val = priority;
  prio.pc_cid = __sched_policy_to_class (policy);
  if (prio.pc_cid == -1)
    return errno;

  int result = priocntl (idtype, id, PC_DOPRIO, &prio);
  if (result != 0)
    return errno;

  if (policy == SCHED_FIFO || policy == SCHED_RR)
    {
      // TODO
    }

  return 0;
}

int __sched_get_rt_priorities (int *minpri, int *maxpri)
{
  /* Force the class info for the RT scheduler to be fetched.  */
  if (__sched_policy_to_class (SCHED_FIFO) == -1)
    return -1;

  *minpri = 0;
  *maxpri = ((rtinfo_t *)__sched_policies[SCHED_FIFO].pc_clinfo)->rt_maxpri;

  return 0;
}
