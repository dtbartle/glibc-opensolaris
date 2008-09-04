/* Copyright (C) 2002, 2003, 2005, 2006, 2008 Free Software Foundation, Inc.
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

#include <string.h>
#include <pthreadP.h>
#include <synchP.h>


int
__pthread_mutex_destroy (mutex)
     pthread_mutex_t *mutex;
{
  if (mutex->mutex_lockbyte != LOCKBYTE_UNSET ||
      mutex->mutex_cond_waiters > 0)
    return EBUSY;

  if (mutex->mutex_type & LOCK_ROBUST)
    memset (mutex, 0, sizeof(mutex_t));
  else
    mutex->mutex_magic = -1;

  return 0;
}
strong_alias (__pthread_mutex_destroy, pthread_mutex_destroy)
INTDEF(__pthread_mutex_destroy)
