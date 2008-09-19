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

#include <stdlib.h>
#include <dirent.h>

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/fdwalk-3c  */

int fdwalk (int (*func)(void *, int), void *cd)
{
  DIR *dir = opendir ("/proc/self/fd");
  if (!dir)
    return -1;

  /* Note that fdwalk is not required to be thread-safe so we don't need to
     use the _r version.  */
  struct dirent *dirent;
  while ((dirent = readdir (dir)))
    {
      if (dirent->d_name[0] == '.')
        continue;
      int fd = atoi (dirent->d_name);
      if (fd == dirfd (dir))
        continue;
      (*func)(cd, fd);
    }

  return 0;
}
