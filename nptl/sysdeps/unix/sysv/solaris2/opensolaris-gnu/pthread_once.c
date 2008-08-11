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

#include "pthreadP.h"
#include <bits/libc-lock.h>

unsigned long int __fork_generation attribute_hidden;

__libc_lock_define_initialized (static, once_lock);

static void
clear_once_control (void *arg)
{
  pthread_once_t *once_control = (pthread_once_t *) arg;

  *once_control = 0;
  __libc_lock_unlock (once_lock);
}

/* XXX: This code breaks with fork - but so does sun's libc.  */

int
__pthread_once (once_control, init_routine)
     pthread_once_t *once_control;
     void (*init_routine) (void);
{
  if (*once_control == PTHREAD_ONCE_INIT)
    {
      __libc_lock_lock (once_lock);

      if (*once_control == PTHREAD_ONCE_INIT)
	{
	  /* This thread is the first here.  Do the initialization.
	     Register a cleanup handler so that in case the thread gets
	     interrupted the initialization can be restarted.  */
	  pthread_cleanup_push (clear_once_control, once_control);

	  init_routine ();

	  pthread_cleanup_pop (0);

	  *once_control = !PTHREAD_ONCE_INIT;
	}

      __libc_lock_unlock (once_lock);
    }

  return 0;
}
weak_alias (__pthread_once, pthread_once)
strong_alias (__pthread_once, __pthread_once_internal)
