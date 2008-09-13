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

#include <sysdep-cancel.h>
#include <inline-syscall.h>
#include <door.h>

/* Arguments are passed normally with the 6th argument always the subcode.  */

DECLARE_INLINE_SYSCALL (int, door, long, long, long, long, long, long subcode);


int door_info (int d, door_info_t *info)
{
  return INLINE_SYSCALL (door, 6, d, (long)info, 0, 0, 0, DOOR_INFO);
}


int door_bind (int d)
{
  return INLINE_SYSCALL (door, 6, d, 0, 0, 0, 0, DOOR_BIND);
}


int door_unbind (void)
{
  return INLINE_SYSCALL (door, 6, 0, 0, 0, 0, 0, DOOR_UNBIND);
}


int door_revoke (int d)
{
  return INLINE_SYSCALL (door, 6, d, 0, 0, 0, 0, DOOR_REVOKE);
}


int door_getparam(int d, int param, size_t *out)
{
  return INLINE_SYSCALL (door, 6, d, param, (long)out, 0, 0, DOOR_GETPARAM);
}


int door_setparam (int d, int param, size_t val)
{
  return INLINE_SYSCALL (door, 6, d, param, val, 0, 0, DOOR_SETPARAM);
}


int door_call (int d, door_arg_t* params)
{
  if (SINGLE_THREAD_P)
    return INLINE_SYSCALL (door, 6, d, (long)params, 0, 0, 0, DOOR_SETPARAM);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int res = INLINE_SYSCALL (door, 6, d, (long)params, 0, 0, 0, DOOR_SETPARAM);

  LIBC_CANCEL_RESET (oldtype);

  return res;
}
