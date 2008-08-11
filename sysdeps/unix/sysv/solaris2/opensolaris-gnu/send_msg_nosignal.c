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

#include "send_msg_nosignal.h"
#include <stddef.h>

/* XXX: There is a slight race here. Another thread may call pthread_sigmask
   between __send_msg_nosignal_pre and __send_msg_no_signal_post.  */

int __send_msg_nosignal_pre (struct sigaction *oldact, sigset_t *oldset)
{
  /* block all signals */
  sigset_t fillset;
  if (sigfillset(&fillset) != 0)
    return -1;
  if (sigprocmask(SIG_SETMASK, &fillset, oldset) != 0)
    return -1;

  /* install SIGPIPE handler */
  struct sigaction act;
  act.sa_handler = SIG_IGN;
  if (sigemptyset (&act.sa_mask) != 0)
    return -1;
  act.sa_flags = 0;
  if (sigaction (SIGPIPE, &act, oldact) != 0)
    return -1;

  return 0;
}

int __send_msg_nosignal_post (struct sigaction *oldact, sigset_t *oldset)
{
  /* restore SIGPIPE handler */
  if (sigaction (SIGPIPE, oldact, NULL) != 0)
    return -1;

  /* restore signals */
  if (sigprocmask (SIG_SETMASK, oldset, NULL) != 0)
    return -1;

  return 0;
}
