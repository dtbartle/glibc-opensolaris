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

#include <sys/swap.h>
#include <sys/stat.h>
#include <sys/uadmin.h>
#include <errno.h>

/* XXX: If the size of the device pointed to by path changes between calls
   to swapon and swapoff we might have problems.  */

int
swapon (path)
     const char *path;
{
  struct stat st;
  swapres_t sr;
  int result;

  /* determine path length */
  if(__stat(path, &st) == -1)
    return -1;

  /* call uadmin */
  sr.sr_name = (char*)path;
  sr.sr_start = 0;
  sr.sr_length = st.st_size;
  return uadmin (A_SWAPCTL, SC_ADD, (uintptr_t)&sr);
}