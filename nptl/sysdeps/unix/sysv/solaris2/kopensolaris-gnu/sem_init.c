/* Copyright (C) 2002, 2007, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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

#include <errno.h>
#include <semaphore.h>
#include "semaphoreP.h"
#include <sys/synch.h>
#include <synchP.h>


int
__new_sem_init (sem, pshared, value)
     sem_t *sem;
     int pshared;
     unsigned int value;
{
  int type = pshared ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE;
  int errval = sema_init (sem, value, type, NULL);
  if (errval != 0)
    {
      __set_errno (errval);
      return -1;
    }

  return 0;
}
weak_alias (__new_sem_init, sem_init)
