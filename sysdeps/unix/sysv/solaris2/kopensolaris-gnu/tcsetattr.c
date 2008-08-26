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

#include <sys/ioctl.h>
#include <termios.h>
#include <errno.h>

int
tcsetattr (fd, optional_actions, termios_p)
     int fd;
     int optional_actions;
     const struct termios *termios_p;
{
  switch (optional_actions)
    {
    case TCSANOW:
      return __ioctl (fd, TCSETS, termios_p);
    case TCSADRAIN:
      return __ioctl (fd, TCSETSW, termios_p);
    case TCSAFLUSH:
      return __ioctl (fd, TCSETSF, termios_p);
    default:
      __set_errno (EINVAL);
      return -1;
    }
}

libc_hidden_def(tcsetattr)
