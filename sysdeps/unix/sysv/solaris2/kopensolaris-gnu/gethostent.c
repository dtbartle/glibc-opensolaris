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

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/* XXX: These are not reentrant.  */

struct hostent *getipnodebyname (const char *name, int af, int flags,
      int *error_num)
{
  /* XXX: We ignore flags.  */
  struct hostent *hostent = gethostbyname2 (name, af);
  if (!hostent && error_num)
    *error_num = h_errno;
  return hostent;
}


struct hostent *getipnodebyaddr (const void *addr, size_t len, int af,
      int *error_num)
{
  struct hostent *hostent = gethostbyaddr (addr, len, af);
  if (!hostent && error_num)
    *error_num = h_errno;
  return hostent;
}


void freehostent (struct hostent *ip)
{
  /* This does nothing by design.  */
}
