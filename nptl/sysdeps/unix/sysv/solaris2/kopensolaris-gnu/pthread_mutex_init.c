/* Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008
   Free Software Foundation, Inc.
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

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <pthreadP.h>
#include <sys/synch.h>
#include <synch_priv.h>

static const struct pthread_mutexattr default_attr =
  {
    /* Default is a normal mutex, not shared between processes.  */
    .mutexkind = PTHREAD_MUTEX_NORMAL
  };


int
__pthread_mutex_init (mutex, mutexattr)
     pthread_mutex_t *mutex;
     const pthread_mutexattr_t *mutexattr;
{
  const struct pthread_mutexattr *imutexattr;

  imutexattr = (const struct pthread_mutexattr *) mutexattr ?: &default_attr;

  int ceiling = (imutexattr->mutexkind & PTHREAD_MUTEXATTR_PRIO_CEILING_MASK)
      >> PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT;

  return mutex_init ((mutex_t *)mutex, imutexattr->mutexkind, (void *)ceiling);
}
strong_alias (__pthread_mutex_init, pthread_mutex_init)
INTDEF(__pthread_mutex_init)
