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
#include <syscallP.h>
#include <sys/rctl.h>

/* Docs: http://docs.sun.com/app/docs/doc/816-5167/getrctl-2?a=view.  */

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
