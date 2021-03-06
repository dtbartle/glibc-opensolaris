/* Convert Inet number to ASCII representation.
   Copyright (C) 1997, 1998, 2000, 2001, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>


char *
inet_ntoa_r (struct in_addr in, char *buffer)
{
  unsigned char *bytes = (unsigned char *) &in;
  __snprintf (buffer, sizeof (buffer), "%d.%d.%d.%d",
	      bytes[0], bytes[1], bytes[2], bytes[3]);

  return buffer;
}
