/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>.

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
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <not-cancel.h>

DECLARE_INLINE_SYSCALL (int, so_socketpair, int fds[2]);

int
socketpair (domain, type, protocol, fds)
     int domain;
     int type;
     int protocol;
     int fds[2];
{
  int sock0 = -1;
  int sock1 = -1;
  int result = -1;

  if (fds == NULL)
    {
      __set_errno(EINVAL);
      return -1;
    }

  /* create the pair of sockets */
  sock0 = __socket (domain, type, protocol);
  if (sock0 != -1)
    {
      sock1 = __socket (domain, type, protocol);
      if(sock1 != -1)
        {
          fds[0] = sock0;
          fds[1] = sock1;
          result = INLINE_SYSCALL (so_socketpair, 1, fds);
          if (result != -1)
            {
              /* check if new sockets were created */
              if (fds[0] == sock0)
                sock0 = -1;
              if (fds[1] == sock1)
                sock1 = -1;
            }
        }
    }

  /* close any sockets that were created by failed calls or duplicated */
  if (sock0 != -1)
      close_not_cancel_no_status (sock0);
  if (sock1 != -1)
      close_not_cancel_no_status (sock1);

  return result;
}
