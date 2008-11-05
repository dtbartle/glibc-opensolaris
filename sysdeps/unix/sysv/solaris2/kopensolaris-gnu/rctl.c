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
#include <rctlP.h>

/* Docs: http://docs.sun.com/app/docs/doc/816-5167/getrctl-2?a=view
         http://docs.sun.com/app/docs/doc/816-5168/rctlblk-size-3c?a=view  */

DECLARE_INLINE_SYSCALL (long, rctlsys, int code, const char *name, void *obuf,
    void *nbuf, size_t obufsz, int flags);


int getrctl (const char *name, rctlblk_t *old_rblk, rctlblk_t *new_rblk,
      unsigned int flags)
{
  return (int)INLINE_SYSCALL (rctlsys, 6, SYS_SUB_rctlsys_get, name, old_rblk,
    new_rblk, 0, flags);
}


int setrctl (const char *name, rctlblk_t *old_rblk, rctlblk_t *new_rblk,
      unsigned int flags)
{
  return (int)INLINE_SYSCALL (rctlsys, 6, SYS_SUB_rctlsys_set, name, old_rblk,
    new_rblk, 0, flags);
}


size_t rctllist (char *buf, size_t bufsz)
{
  return (size_t)INLINE_SYSCALL (rctlsys, 6, SYS_SUB_rctlsys_list, NULL, buf,
    NULL, bufsz, 0);
}


int rctlctl (const char *name, rctlblk_t *blk, int flags)
{
  return (int)INLINE_SYSCALL (rctlsys, 6, SYS_SUB_rctlsys_ctl, name, blk,
    NULL, 0, flags);
}


int setprojrctl (const char *name, rctlblk_t *blk, size_t size, int flags)
{
  return (int)INLINE_SYSCALL (rctlsys, 6, SYS_SUB_rctlsys_projset, name,
    NULL, blk, size, flags);
}


hrtime_t rctlblk_get_firing_time (rctlblk_t *rblk)
{
  return ((rctl_opaque_t *)rblk)->rcq_firing_time;
}


int rctlblk_get_global_action (rctlblk_t *rblk)
{
  /* Note: rcq_global_flagaction contains both flags and action.  */
  return ((rctl_opaque_t *)rblk)->rcq_global_flagaction &
    ~RCTL_GLOBAL_ACTION_MASK;
}


int rctlblk_get_global_flags (rctlblk_t *rblk)
{
  /* Note: rcq_global_flagaction contains both flags and action.  */
  return ((rctl_opaque_t *)rblk)->rcq_global_flagaction &
    RCTL_GLOBAL_ACTION_MASK;
}


int rctlblk_get_local_action (rctlblk_t *rblk, int *signalp)
{
  /* Note: rcq_local_flagaction contains both flags and action.  */
  return ((rctl_opaque_t *)rblk)->rcq_local_flagaction &
    ~RCTL_LOCAL_ACTION_MASK;
}


int rctlblk_get_local_flags (rctlblk_t *rblk)
{
  /* Note: rcq_local_flagaction contains both flags and action.  */
  return ((rctl_opaque_t *)rblk)->rcq_local_flagaction &
    RCTL_LOCAL_ACTION_MASK;
}


rctl_priv_t rctlblk_get_privilege (rctlblk_t *rblk)
{
  return ((rctl_opaque_t *)rblk)->rcq_privilege;
}


id_t rctlblk_get_recipient_pid (rctlblk_t *rblk)
{
  return ((rctl_opaque_t *)rblk)->rcq_local_recipient_pid;
}


rctl_qty_t rctlblk_get_value (rctlblk_t *rblk)
{
  return ((rctl_opaque_t *)rblk)->rcq_value;
}


rctl_qty_t rctlblk_get_enforced_value (rctlblk_t *rblk)
{
  return ((rctl_opaque_t *)rblk)->rcq_enforced_value;
}


void rctlblk_set_local_action (rctlblk_t *rblk, unsigned int action,
     int signal)
{
  /* Note: rcq_local_flagaction contains both flags and action.  */
  rctl_opaque_t *_rblk = (rctl_opaque_t *)rblk;
  _rblk->rcq_local_signal = signal;
  _rblk->rcq_local_flagaction = (_rblk->rcq_local_flagaction &
      RCTL_LOCAL_ACTION_MASK) | action;
}


void rctlblk_set_local_flags (rctlblk_t *rblk, int flags)
{
  /* Note: rcq_local_flagaction contains both flags and action.  */
  rctl_opaque_t *_rblk = (rctl_opaque_t *)rblk;
  _rblk->rcq_local_flagaction = (_rblk->rcq_local_flagaction &
      ~RCTL_LOCAL_ACTION_MASK) | flags;
}


void rctlblk_set_privilege (rctlblk_t *rblk, rctl_priv_t privilege)
{
  ((rctl_opaque_t *)rblk)->rcq_privilege = privilege;
}


void rctlblk_set_value (rctlblk_t *rblk, rctl_qty_t value)
{
  ((rctl_opaque_t *)rblk)->rcq_value = value;
}


void  rctlblk_set_recipient_pid (rctlblk_t *rblk, id_t pid)
{
  ((rctl_opaque_t *)rblk)->rcq_local_recipient_pid = pid;
}


size_t rctlblk_size (void)
{
  return sizeof (rctl_opaque_t);
}


int rctl_walk (int (*callback)(const char *rctlname, void *walk_data),
      void *init_data)
{
  size_t len = rctllist (NULL, 0);
  if (len < 0)
    return -1;
  char *names = malloc (len);
  if (!names)
    return -1;
  if (rctllist (names, len) != 0)
    {
      free (names);
      return -1;
    }

  char *namesptr = names;
  while (*namesptr)
    {
      callback (namesptr, init_data);
      namesptr += strlen (namesptr) + 1;
    }

  free (names);
  return 0;
}
