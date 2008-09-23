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
#include <grp.h>
#include <unistd.h>
#include <alloca.h>
#include <stdlib.h>
#include <string.h>

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


struct group * __getgrnam_r_sun (const char *name, struct group *gbuf,
      char *buf, size_t buflen)
{
  struct group *bufp;
  return (getgrnam_r (name, gbuf, buf, buflen, &bufp) == 0) ? bufp : NULL;
}


struct group * __getgrgid_r_sun (gid_t gid, struct group *gbuf, char *buf,
      size_t buflen)
{
  struct group *bufp;
  return (getgrgid_r (gid, gbuf, buf, buflen, &bufp) == 0) ? bufp : NULL;
}


struct group * __getgrent_r_sun (struct group *gbuf, char *buf, size_t buflen)
{
  struct group *bufp;
  return (getgrent_r (gbuf, buf, buflen, &bufp) == 0) ? bufp : NULL;
}


struct group * __fgetgrent_r_sun (FILE *fp, struct group *gbuf, char *buf,
      size_t buflen)
{
  struct group *bufp;
  return (fgetgrent_r (fp, gbuf, buf, buflen, &bufp) == 0) ? bufp : NULL;
}


int __getopt_sun (int argc, char * const argv[], const char *optstring)
{
  size_t len = strlen (optstring) + 2;
  int use_alloca = __libc_use_alloca (len);
  char *optstr;
  if (use_alloca)
    optstr = alloca (len);
  else
    {
      optstr = malloc (len);
      if (!optstr)
        return -1;
    }

  optstr[0] = '+';
  memcpy (optstr + 1, optstring, len - 1);

  int res = getopt (argc, argv, optstr);

  if (!use_alloca)
    free (optstr);

  return res;
}


int __sigwait_sun (sigset_t * set)
{
  return sigtimedwait (set, NULL, NULL);
}


struct protoent * __getprotoent_r_sun ()
{
}


struct protoent * __getprotobyname_r_sun ()
{
}


struct protoent * __getprotobynumber_r_sun ()
{
}
