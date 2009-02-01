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

#ifndef _PORT_H
#define _PORT_H

#include <sys/types.h>
#include <sys/port.h>

int port_create (void);
int port_associate (int, int, uintptr_t, int, void *);
int port_dissociate (int, int, uintptr_t);
int port_send (int, int, void *);
int port_sendn (int [], int [], uint_t, int, void *);
int port_get (int, port_event_t *, struct timespec *);
int port_getn (int, port_event_t [], uint_t, uint_t *, struct timespec *);
int port_alert (int, int, int, void *);

#endif /* _PORT_H */
