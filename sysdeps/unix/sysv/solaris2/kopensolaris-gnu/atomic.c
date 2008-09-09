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

/* We need the full patch to atomic.h or we'll get include/atomic.h.  */
#include "sysdeps/unix/sysv/solaris2/kopensolaris-gnu/atomic.h"
#include <membar.h>

/* TODO */

void membar_enter ()
{
  __membar_enter ();
}


void membar_exit ()
{
  __membar_exit ();
}


void membar_producer ()
{
  __membar_producer ();
}


void membar_consumer ()
{
  __membar_consumer ();
}
