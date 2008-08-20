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
#include <signal.h>
#include <errno.h>

int
__sigwait (const sigset_t *set, int *sig)
{
  /* sigwait returns the errno directly and doesn't touch the
      global errno value so we need to be careful */
  int save_errno = errno;

  if (set == NULL || sig == NULL)
    return EINVAL;

  /* sigtimedwait is cancelable so don't implement cancellation here;
    we also don't check for SIGCANCEL since we do that in sigtimedwait */
  int result = sigtimedwait (set, NULL, NULL);
  if (result == -1)
    {
      result = errno;
      __set_errno (save_errno);
    }
  else
    {
      *sig = result;
    }

  return 0;
}

libc_hidden_def (__sigwait)
weak_alias (__sigwait, sigwait)
LIBC_CANCEL_HANDLED (); /* handled by sigtimedwait */
