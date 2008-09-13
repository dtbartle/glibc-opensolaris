/* Copyright (C) 1991,92,95,96,97,2002,2003 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <not-cancel.h>
#include <stdio.h>

__pid_t
__waitpid_not_cancel (__pid_t pid, int *stat_loc, int options)
{
  int res;
  siginfo_t info;

  /* wait until the child dies */
  options |= WEXITED | WTRAPPED;

  /* implement waitpid by calling waitid */
  if (pid < -1)
    res = waitid_not_cancel (P_PGID, -pid, &info, options);
  else if (pid == -1)
    res = waitid_not_cancel (P_ALL, 0, &info, options);
  else if (pid == 0)
    res = waitid_not_cancel (P_PGID, getpgid(0), &info, options);
  else /* if(pid > 0) */
    res = waitid_not_cancel (P_PID, pid, &info, options);

  if (res == -1)
    return -1;

  /* use info.si_code and info.si_status to set stat_loc */
  if (stat_loc)
    {
      switch (info.si_code)
        {
        case CLD_EXITED:
          *stat_loc = (info.si_status & 0xff) << 8;
          break;
        case CLD_KILLED:
          *stat_loc = (info.si_status & 0x7f);
          break;
        case CLD_DUMPED:
          *stat_loc = (info.si_status & 0x7f) | WCOREFLG;
          break;
        case CLD_TRAPPED:
        case CLD_STOPPED:
          *stat_loc = ((info.si_status & 0xff) << 8) | WSTOPFLG;
          break;
        case CLD_CONTINUED:
          *stat_loc = WCONTFLG;
          break;
        }
    }

  return info.si_pid;
}

__pid_t
__libc_waitpid (__pid_t pid, int *stat_loc, int options)
{
  if (SINGLE_THREAD_P)
    return __waitpid_not_cancel (pid, stat_loc, options);

  int oldtype = LIBC_CANCEL_ASYNC ();

  __pid_t res = __waitpid_not_cancel (pid, stat_loc, options);

  LIBC_CANCEL_RESET (oldtype);

  return res;
}

weak_alias (__libc_waitpid, __waitpid)
libc_hidden_weak (__waitpid)
weak_alias (__libc_waitpid, waitpid)
