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

#include <stddef.h>
#include <errno.h>
#include <termios.h>

/* Solaris stores the standard input and output baud rates in bits
   16-19 and 0-3, respectively. If an extension speed is used then we
   set CIBAUDEXT and CBAUDEXT for input and output, respectively, and
   shift the speed left/right by 4 bits, for set/get, respectively.  */

speed_t
cfgetospeed (termios_p)
     const struct termios *termios_p;
{
  speed_t speed = (termios_p->c_cflag & CBAUD);
  if (termios_p->c_cflag & CBAUDEXT)
    speed <<= 4;
  return speed;
}

speed_t
cfgetispeed (termios_p)
     const struct termios *termios_p;
{
  speed_t speed = (termios_p->c_cflag & CBAUD) >> 16;
  if (termios_p->c_cflag & CBAUDEXT)
    speed <<= 4;
  return speed;
}

int
cfsetospeed  (termios_p, speed)
     struct termios *termios_p;
     speed_t speed;
{
  if (speed > __MAX_BAUD)
    {
      __set_errno(EINVAL);
      return -1;
    }

  termios_p->c_cflag &= ~(CBAUDEXT | CBAUD);
  if (speed > CBAUD)
    termios_p->c_cflag |= CBAUDEXT | (speed >> 4);
  else
    termios_p->c_cflag |= speed;

  return 0;
}
libc_hidden_def (cfsetospeed)

int
cfsetispeed (termios_p, speed)
     struct termios *termios_p;
     speed_t speed;
{
  if (speed > __MAX_BAUD)
    {
      __set_errno(EINVAL);
      return -1;
    }

  termios_p->c_cflag &= ~(CIBAUDEXT | CIBAUD);
  if (speed > CBAUD)
    termios_p->c_cflag |= CIBAUDEXT | ((speed >> 4) << 16);
  else
    termios_p->c_cflag |= (speed << 16);

  return 0;
}
libc_hidden_def (cfsetispeed)
