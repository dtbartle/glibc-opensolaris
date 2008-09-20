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

#include <pwd.h>
#include <unistd.h>

struct passwd * __getpwnam_r_sun (const char *name, struct passwd *pwbuf,
      char *buf, size_t buflen)
{
  struct passwd *bufp;
  return (getpwnam_r (name, pwbuf, buf, buflen, &bufp) == 0) ? bufp : NULL;
}

struct passwd * __getpwuid_r_sun (uid_t uid, struct passwd *pwbuf, char *buf,
     size_t buflen)
{
  struct passwd *bufp;
  return (getpwuid_r (uid, pwbuf, buf, buflen, &bufp) == 0) ? bufp : NULL;
}

struct passwd * __getpwent_r_sun (struct passwd *pwbuf, char *buf, size_t buflen)
{
  struct passwd *bufp;
  return (getpwent_r (pwbuf, buf, buflen, &bufp) == 0) ? bufp : NULL;
}

struct passwd * __fgetpwent_r_sun (FILE *fp, struct passwd *pwbuf, char *buf,
      size_t buflen)
{
  struct passwd *bufp;
  return (fgetpwent_r (fp, pwbuf, buf, buflen, &bufp) == 0) ? bufp : NULL;
}

#if 0
int __getopt_sun (int argc, char * const argv[], const char *optstring)
{
 // TODO
}
#endif
