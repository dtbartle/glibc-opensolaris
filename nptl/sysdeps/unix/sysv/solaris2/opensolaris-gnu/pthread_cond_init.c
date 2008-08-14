/* Copyright (C) 2002, 2003, 2004, 2005, 2007, 2008
    Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca, 2008.

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


#include <shlib-compat.h>
#include "pthreadP.h"
#include <string.h>
#include <sys/synch.h>
#include <synch_priv.h>

static const struct pthread_condattr default_attr =
  {
    .value = 0
  };


int
__pthread_cond_init (cond, cond_attr)
     pthread_cond_t *cond;
     const pthread_condattr_t *cond_attr;
{
  const struct pthread_condattr *icond_attr;

  icond_attr = (struct pthread_condattr *) cond_attr ?: &default_attr;

  memset (cond, 0, sizeof(pthread_cond_t));
  cond->cond_type = (icond_attr->value & 1) ?
      PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE;
  cond->cond_magic = COND_MAGIC;

  return 0;
}
versioned_symbol (libpthread, __pthread_cond_init,
		  pthread_cond_init, GLIBC_2_3_2);
