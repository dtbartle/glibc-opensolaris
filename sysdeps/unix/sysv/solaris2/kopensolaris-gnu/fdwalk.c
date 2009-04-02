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
#include <sys/resource.h>

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/fdwalk-3c  */

int fdwalk (int (*func)(void *, int), void *cd)
{
  int res = 0;
  DIR *dir;

  dir = opendir ("/proc/self/fd");
  if (dir)
    {
      /* Note that fdwalk is not required to be thread-safe so we don't need to
         use the _r version.  */
      struct dirent *dirent;
      while ((dirent = readdir (dir)))
	{
	  int fd;

	  if (dirent->d_name[0] == '.')
	    continue;
	  fd = atoi (dirent->d_name);
	  if (fd == dirfd (dir))
	    continue;
	  res = (*func)(cd, fd);
	  if (res != 0)
	    break;
	}

      (void) closedir (dir);
    }
  else
    {
      struct rlimit rlim;
      int fd;

      if (getrlimit (RLIMIT_NOFILE, &rlim) != 0)
	return -1;
      for (fd = 0; fd < rlim.rlim_max; fd++)
	{
	  res = (*func)(cd, fd);
	  if (res != 0)
	    break;
	}
    }

  return res;
}
