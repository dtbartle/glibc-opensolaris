/* Copyright (C) 2002 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.

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

#include <unistd.h>
#include <list.h>
#include "fork.h"
#include <tls.h>
#include <bits/libc-lock.h>


static struct fork_handler pthread_child_handler;


void
__libc_pthread_init (ptr, reclaim)
     unsigned long int *ptr;
     void (*reclaim) (void);
{
  /* Remember the pointer to the generation counter in libpthread.  */
  __fork_generation_pointer = ptr;

  /* Called by a child after fork.  */
  pthread_child_handler.handler = reclaim;

  /* The fork handler needed by libpthread.  */
  list_add_tail (&pthread_child_handler.list, &__fork_child_list);

  /* We have a macro which is used in asm code describing data layout.
     Make sure it does not get out of date.  */
  if (offsetof (struct pthread, header.data.multiple_threads)
      != MULTIPLE_THREADS_OFFSET)
    {
#define str_n_len(str) str, sizeof (str) - 1
      __libc_write (STDERR_FILENO,
		    str_n_len ("*** MULTIPLE_THREADS_OFFSET out of date\n"));
      _exit (1);
    }
}
