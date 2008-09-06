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
#include <port.h>

/* SYS_port returns a 64-bit int but the port_* calls return a 32-bit int, so
   we can't implement these directly in syscalls.list.  Whenever the 2nd
   argument is not a port we need to specify PORT_SYS_NOPORT.

   port_getn and port_sendn are special in that they may return after only
   some of the ports have been acted on before the timeout occured. In this
   case, the first 32-bits of the the return specify the number of acted on
   ports, and the second 32-bits specify the error that occured (currently
   this is always ETIME). */

DECLARE_INLINE_SYSCALL (int64_t, port, int, ...);

int port_create (void)
{
  /* The 2nd argument is the version on PORT_CREATE, currently 0.  */
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 2, PORT_CREATE | PORT_SYS_NOPORT, 0);
  return ret.rval1;
}

int port_associate (int port, int source, uintptr_t object,
      int events, void *user)
{
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 6, PORT_ASSOCIATE, port, source, object,
      events, user);
  return ret.rval1;
}

int port_dissociate (int port, int source, uintptr_t object)
{
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 4, PORT_DISSOCIATE, port, source, object);
  return ret.rval1;
}

int port_send (int port, int events, void *user)
{
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 4, PORT_SEND, port, events, user);
  return ret.rval1;
}

// TODO
#if 0
int port_sendn (int ports[], int errors[], uint_t nent, int events, void *user)
{
  /* Note that we cannot have more than PORT_MAX_LIST ports in a single
     syscall so we may need to split ports across multiple syscalls.  */

  // need PORT_SYS_NOPORT
}
#endif

int port_get (int port, port_event_t *pe, struct timespec *to)
{
  time_t sec = to ? to->tv_sec : 0;
  long nsec = to ? to->tv_nsec : 0;
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 6, PORT_GET, port, pe, sec, nsec, to);
  return ret.rval1;
}

// TODO
#if 0
int port_getn (int port, port_event_t list[], uint_t max, uint_t *nget,
      struct timespec *timeout)
{
}
#endif

int port_alert (int port, int flags, int events, void *user)
{
  rval_t ret;
  ret.rval64 = INLINE_SYSCALL (port, 5, PORT_ALERT, port, flags, events, user);
  return ret.rval1;
}
