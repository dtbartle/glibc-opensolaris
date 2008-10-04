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
#include <sys/ucontext.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>

int thr_stksegment (stk)
      stack_t *stk;
{
  struct pthread *self = THREAD_SELF;
  stk->ss_size = THREAD_GETMEM (self, stackblock_size);
  // TODO: handle stacks that grow up
  stk->ss_sp = THREAD_GETMEM (self, stackblock) + stk->ss_size;
  stk->ss_flags = 0;

  return 0;
}
