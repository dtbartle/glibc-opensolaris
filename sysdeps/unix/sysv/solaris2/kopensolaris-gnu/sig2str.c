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

#include <signal.h>
#include <ctype.h>

/* Based on ideas from sig2str.c in gnulib.  */

#define NUMNAME(name)   { SIG##name, #name }
#define RTNAME(num)     { __SIGRTMIN + num, "RTMIN" #num }

static struct _siglist { int num; char name[8]; } siglist[] =
  {
    NUMNAME (HUP), NUMNAME (INT), NUMNAME (QUIT), NUMNAME (ILL),
    NUMNAME (TRAP), NUMNAME (IOT), NUMNAME (EMT), NUMNAME (FPE),
    NUMNAME (KILL), NUMNAME (BUS), NUMNAME (SEGV), NUMNAME (SYS),
    NUMNAME (PIPE), NUMNAME (ALRM), NUMNAME (TERM), NUMNAME (USR1),
    NUMNAME (USR2), NUMNAME (CHLD), NUMNAME (PWR), NUMNAME (WINCH),
    NUMNAME (URG), NUMNAME (POLL), NUMNAME (IO), NUMNAME (STOP),
    NUMNAME (TSTP), NUMNAME (CONT), NUMNAME (TTIN), NUMNAME (TTOU),
    NUMNAME (VTALRM), NUMNAME (PROF), NUMNAME (XCPU), NUMNAME (XFSZ),
    NUMNAME (WAITING), NUMNAME (LWP), NUMNAME (FREEZE), NUMNAME (THAW),
    NUMNAME (CANCEL), NUMNAME (LOST), NUMNAME (XRES), NUMNAME (JVM1),
    NUMNAME (JVM2), { __SIGRTMIN, "RTMIN" }, RTNAME (+1), RTNAME (+2),
    RTNAME (+3), RTNAME (-3), RTNAME (-2), RTNAME (-1),
    { __SIGRTMAX, "RTMAX"}
  };

#define SIGLIST_SIZE    (sizeof (siglist) / sizeof (siglist[0]))

int sig2str (int signum, char *signame)
{
  for (int i = 0; i < SIGLIST_SIZE; i++)
    {
      if (siglist[i].num == signum)
        {
          strcpy (signame, siglist[i].name);
          return 0;
        }
    }

  return -1;
}


int str2sig (char const *signame, int *signum)
{
  if (isdigit (signame[0]))
    {
      long num = strtol (signame, NULL, 10);
      if (num < 1 || num >= _NSIG)
        {
          return -1;
        }
      else
        {
          *signum = num;
          return 0;
        }
    }

  for (int i = 0; i < SIGLIST_SIZE; i++)
    {
      if (strcmp (siglist[i].name, signame) == 0)
        {
          *signum = siglist[i].num;
          return 0;
        }
    }

  return -1;
}
