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

#ifndef _NPTL_SIGACTION
# define _NPTL_SIGACTION
# include <sigaction.c>
#else

#include_next <sigaction.c>
#include <bits/libc-lock.h>
#include <fork.h>

static void sigaction_atfork_prepare (void)
{
  __libc_lock_lock (signal_lock);
}

static void sigaction_atfork_parent (void)
{
  __libc_lock_unlock (signal_lock);
}

static void sigaction_atfork_child (void)
{
  __libc_lock_unlock (signal_lock);
}

void sigaction_atfork (void)
{
  __register_atfork (sigaction_atfork_prepare, sigaction_atfork_parent,
      sigaction_atfork_child, NULL);
}

#endif /* _NPTL_SIGACTION */
