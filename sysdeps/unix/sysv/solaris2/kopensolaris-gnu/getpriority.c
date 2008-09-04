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

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/procset.h>
#include <sys/priocntl.h>
#include <limits.h>
#include <errno.h>
#include <priorityP.h>

int
getpriority (enum __priority_which which, id_t who)
{
  idtype_t type = __prio_to_p (which);
  if (type == -1)
    return -1;

  if(who == 0)
    who = P_MYID;

  pcnice_t nice;
  nice.pc_val = 0;
  nice.pc_op = PC_GETNICE;
  if (priocntl (type, who, PC_DONICE, &nice) == -1)
    return -1;

  return nice.pc_val;
}

libc_hidden_def (getpriority)
