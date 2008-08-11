/* Copyright (C) 2003, 2004, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2003.

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
#include <pthreadP.h>


int
__pthread_getaffinity_new (pthread_t th, size_t cpusetsize, cpu_set_t *cpuset)
{
  return ENOSYS;
}
strong_alias (__pthread_getaffinity_new, __pthread_getaffinity_np)
weak_alias (__pthread_getaffinity_new, pthread_getaffinity_np)

stub_warning (pthread_getaffinity_np)
#include <stub-tag.h>
