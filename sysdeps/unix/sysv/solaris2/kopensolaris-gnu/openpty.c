/* Copyright (C) 2009 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>, 2009.

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

#include <streams/stropts.h>

#define __OPENPTY_INIT_SLAVE(slave)                     \
    if (ioctl(slave, I_PUSH, "ptem") == -1 ||           \
            ioctl(slave, I_PUSH, "ldterm") == -1 ||     \
            ioctl(slave, I_PUSH, "ttcompat") == -1) {   \
        if (buf != _buf)                                \
            free (buf);                                 \
    }

#include <login/openpty.c>
