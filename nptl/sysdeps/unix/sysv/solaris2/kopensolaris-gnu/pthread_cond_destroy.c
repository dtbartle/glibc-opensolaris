/* Copyright (C) 2002, 2003, 2004, 2007, 2008 Free Software Foundation, Inc.
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

#include <shlib-compat.h>
#include <errno.h>
#include "pthreadP.h"
#include <string.h>


int
__pthread_cond_destroy (cond)
     pthread_cond_t *cond;
{
  // TODO: make sure we're done with cond (EBUSY)

  cond->cond_magic = -1;
  return 0;
}
versioned_symbol (libpthread, __pthread_cond_destroy,
		  pthread_cond_destroy, GLIBC_2_3_2);
