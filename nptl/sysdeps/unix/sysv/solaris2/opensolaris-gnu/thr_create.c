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

#include <pthreadP.h>
#include <thread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int thr_create (void *stack_address, size_t stack_size,
        void *(*start_routine)(void *), void *arg,
        long flags, thread_t *new_thread)
{
  if(flags & ~(THR_BOUND | THR_DETACHED | THR_NEW_LWP | THR_SUSPENDED |
      THR_DAEMON))
    {
      return EINVAL;
    }

  struct pthread_attr iattr;
  memset (&iattr, 0, sizeof(struct pthread_attr));
  iattr.guardsize = __getpagesize ();
  iattr.stackaddr = stack_address;
  iattr.stacksize = stack_size;
  iattr.flags = ATTR_FLAG_STACKADDR |
    ((flags & THR_DETACHED) ? ATTR_FLAG_DETACHSTATE : 0) |
    ((flags & THR_SUSPENDED) ? ATTR_FLAG_SUSPENDED : 0) |
    ((flags & THR_DAEMON) ? ATTR_FLAG_DAEMON : 0);

  return pthread_create ((pthread_t *)new_thread, (pthread_attr_t *)&iattr,
      start_routine, arg);
}