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
#include <memory.h>
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

  /* Fill pollfd structure.  */
  int pfd_len = nfds * sizeof(struct pollfd);
  int use_alloca = __libc_use_alloca (pfd_len);
  struct pollfd *pfd;
  if (use_alloca)
    pfd = alloca (pfd_len);
  else
    {
      pfd = malloc (pfd_len);
      if (!pfd)
        return -1;
    }

  int fd;
  nfds_t i = 0;
  for (fd = 0; fd < nfds; fd++)
    {
      if ((readfds && FD_ISSET (fd, readfds)) ||
          (writefds && FD_ISSET (fd, writefds)) ||
          (exceptfds && FD_ISSET (fd, exceptfds)))
        {
          pfd[i].fd = fd;
          pfd[i].events = 0;
          pfd[i].revents = 0;
          if (readfds && FD_ISSET (fd, readfds))
                pfd[i].events |= POLLRDNORM;
          if (writefds && FD_ISSET (fd, writefds))
                pfd[i].events |= POLLWRNORM;
          if (exceptfds && FD_ISSET (fd, exceptfds))
                pfd[i].events |= POLLRDBAND;
          i++;
        }
    }
  nfds_t num_pfd = i;

  /* ppoll is cancelable so don't implement cancellation here.  */
  int result = ppoll (pfd, num_pfd, timeout, sigmask);
  if (result == -1)
    {
      if (!use_alloca)
        free (pfd);
      return -1;
    }

  /* Check for POLLNVAL.  */
  for (i = 0; i < num_pfd; i++)
    {
      if (pfd[i].revents & POLLNVAL)
        {
          if (!use_alloca)
            free (pfd);
          __set_errno (EBADFD);
          return -1;
        }
    }

  /* clear fd_set's */
  for (fd = 0; fd < nfds; fd++)
    {
      if (readfds)
          FD_CLR (fd, readfds);
      if (writefds)
          FD_CLR (fd, writefds);
      if (exceptfds)
          FD_CLR (fd, exceptfds);
    }

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

  if (!use_alloca)
    free (pfd);
  return bits;
}

weak_alias (__pselect, pselect)
strong_alias (__pselect, __libc_pselect)
LIBC_CANCEL_HANDLED (); /* handled by ppoll */
