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

#include <sysdep-cancel.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <errno.h>
#include <alloca.h>
#include <assert.h>

int
__pselect (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
	   const struct timespec *timeout, const sigset_t *sigmask)
{
  if (nfds < 0 || nfds > FD_SETSIZE)
    {
      __set_errno(EINVAL);
      return -1;
    }

  /* Set NULL fds to be the empty set.  */
  fd_set emptyfds;
  FD_ZERO (&emptyfds);
  const fd_set *_readfds = readfds ?: &emptyfds;
  const fd_set *_writefds = writefds ?: &emptyfds;
  const fd_set *_exceptfds = exceptfds ?: &emptyfds;

  /* Fill pollfd structure.  */
  struct pollfd *pfd = alloca (nfds * sizeof(struct pollfd));
  int fd;
  nfds_t i = 0;
  for (fd = 0; fd < nfds; fd++)
    {
      if (FD_ISSET (fd, _readfds) || FD_ISSET (fd, _writefds)
            || FD_ISSET (fd, _exceptfds))
        {
          pfd[i].fd = fd;
          pfd[i].events = 0;
          pfd[i].revents = 0;
          if (FD_ISSET (fd, _readfds))
                pfd[i].events |= POLLRDNORM;
          if(FD_ISSET (fd, _writefds))
                pfd[i].events |= POLLWRNORM;
          if(FD_ISSET (fd, _exceptfds))
                pfd[i].events |= POLLRDBAND;
          i++;
        }
    }
  nfds_t num_pfd = i;

  /* ppoll is cancelable so don't implement cancellation here.  */
  int result = ppoll (pfd, num_pfd, timeout, sigmask);
  if (result == -1)
    return -1;

  /* Check for POLLNVAL.  */
  for (i = 0; i < num_pfd; i++)
    {
      if (pfd[i].revents & POLLNVAL)
        {
          __set_errno (EBADFD);
          return -1;
        }
    }

  /* Clear fd_set's.  */
  if (readfds)
    __FD_ZERO (readfds);
  if (writefds)
    __FD_ZERO (writefds);
  if (exceptfds)
    __FD_ZERO (exceptfds);

  /* Fill fd_set's.  */
  int bits = 0;
  for (i = 0; i < num_pfd; i++)
    {
      fd = pfd[i].fd;
      int events = pfd[i].events;
      int revents = pfd[i].revents;
      assert (fd < nfds);

      if (readfds && ((revents & POLLRDNORM) || ((events & POLLRDNORM)
            && (revents & (POLLHUP | POLLERR)))))
        {
          __FD_SET (fd, readfds);
          bits++;
        }
      if (writefds && ((revents & POLLWRNORM) || ((events & POLLWRNORM)
              && (revents & (POLLHUP | POLLERR)))))
        {
          __FD_SET (fd, writefds);
          bits++;
        }
      if (exceptfds && ((revents & POLLRDBAND) || ((events & POLLRDBAND)
              && (revents & (POLLHUP | POLLERR)))))
        {
          __FD_SET (fd, exceptfds);
          bits++;
        }
    }

  return bits;
}

weak_alias (__pselect, pselect)
strong_alias (__pselect, __libc_pselect)
LIBC_CANCEL_HANDLED (); /* handled by ppoll */
