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

#ifndef _SOCKET_PRIV_H
#define _SOCKET_PRIV_H

#include <pthreadP.h>
#include <atomic.h>

/* Helper code to handle MSG_NOSIGNAL.  */

#define SIGPIPE_DISABLE_DEFINE
#define SIGPIPE_DISABLE \
    atomic_increment (&THREAD_SELF->sigpipe_disabled)
#define SIGPIPE_ENABLE \
    atomic_decrement (&THREAD_SELF->sigpipe_disabled)
#define SIGPIPE_IS_DISABLED \
    (THREAD_GETMEM (THREAD_SELF, sigpipe_disabled) != 0)

#endif /* _SOCKET_PRIV_H */
