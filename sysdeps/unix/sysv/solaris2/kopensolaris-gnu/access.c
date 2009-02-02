/* Copyright (C) 1991, 1995, 1996, 1997, 2009 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2009.

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
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <inline-syscall.h>

DECLARE_INLINE_SYSCALL (int, access, const char *, int);

#define E_OK 010

/* Test for access to FILE.  */
int
__access (file, type)
     const char *file;
     int type;
{
  if (file == NULL || (type & ~(R_OK|W_OK|X_OK|F_OK|E_OK)) != 0)
    {
      __set_errno (EINVAL);
      return -1;
    }

  int res = INLINE_SYSCALL (access, 2, file, type);

  /* XXX: This should really be fixed in the kernel.  */
  if (res == 0 && (type & X_OK))
    {
      uid_t uid;
      gid_t gid;

      uid = (type & E_OK) ? geteuid () : getuid ();
      gid = (type & E_OK) ? getegid () : getgid ();
      if (uid == 0 || gid == 0)
        {
          struct stat buf;

          if (stat (file, &buf) != 0)
            return -1;

          /* Test user bit.  */
          if (uid == buf.st_uid)
            {
              if ((buf.st_mode & S_IXUSR) == 0)
                {
                  __set_errno (EACCES);
                  return -1;
                }
              return 0;
            }

          /* Test gid bit.  */
          if (gid == buf.st_gid)
            {
              if ((buf.st_mode & S_IXGRP) == 0)
                {
                  __set_errno (EACCES);
                  return -1;
                }
              return 0;
            }

          /* Test other bit.  */
          if ((buf.st_mode & S_IXOTH) == 0)
            {
              __set_errno (EACCES);
              return -1;
            }
          return 0;
        }
    }

  return res;
}

weak_alias (__access, access)
