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
#include <sys/types.h>
#include <sys/param.h>
#include <portP.h>

/* SYS_port returns a 64-bit int but the port_* calls return a 32-bit int, so
   we can't implement these directly in syscalls.list.  Whenever the 2nd
   argument is not a port we need to specify PORT_SYS_NOPORT.

   port_getn and port_sendn are special in that they may return after only
   some of the ports have been acted on before the timeout occured. In this
   case, the first 32-bits of the the return specify the number of acted on
   ports, and the second 32-bits specify the error that occured (currently
   this is always ETIME).  */

DECLARE_INLINE_SYSCALL (int64_t, port, int, ...);


int port_create (void)
{
  /* The 2nd argument is the version of port_create, currently 0.  */
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 2,
    SYS_SUB_port_create | PORT_SYS_NOPORT, 0);
  return ret.rval1;
}

int port_associate (int port, int source, uintptr_t object,
      int events, void *user)
{
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 6, SYS_SUB_port_associate, port, source,
    object, events, user);
  return ret.rval1;
}

int port_dissociate (int port, int source, uintptr_t object)
{
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 4, SYS_SUB_port_dissociate, port,
      source, object);
  return ret.rval1;
}

int port_send (int port, int events, void *user)
{
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 4, SYS_SUB_port_send, port, events, user);
  return ret.rval1;
}

int port_sendn (int ports[], int errors[], unsigned int nent,
      int events, void *user)
{
  /* Note that we cannot have more than PORT_MAX_LIST ports in a single
     syscall so we may need to split ports across multiple syscalls.  */

  rval_t ret;
  int nevents = 0;
  for (unsigned int i = 0; i < nent; i += PORT_MAX_LIST)
    {
      int errval = __systemcall (&ret.rvals, SYS_port, SYS_SUB_port_sendn |
        PORT_SYS_NOPORT, &ports[i], &errors[i], MIN (nent - i, PORT_MAX_LIST),
        events, user);
      if (errval == 0 || errval == ETIME)
          nevents += ret.rval1;
      if (errval != 0)
        {
          __set_errno (errval);
          break;
        }
    }

  return nevents;
}

int port_get (int port, port_event_t *pe, struct timespec *to)
{
  time_t sec = to ? to->tv_sec : 0;
  long nsec = to ? to->tv_nsec : 0;
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 6, SYS_SUB_port_get, port, pe, sec, nsec, to);
  return ret.rval1;
}

int port_getn (int port, port_event_t list[], unsigned int max,
      unsigned int *nget, struct timespec *timeout)
{
  rval_t ret;
  int errval = __systemcall (&ret.rvals, SYS_port, SYS_SUB_port_getn, port, list,
    max, *nget, timeout);
  if (errval == 0 || errval == ETIME)
    *nget = ret.rval1;

  if (errval != 0)
    {
      __set_errno (errval);
      return -1;
    }
  return 0;
}

int port_alert (int port, int flags, int events, void *user)
{
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 5, SYS_SUB_port_alert, port, flags,
    events, user);
  return ret.rval1;
}
