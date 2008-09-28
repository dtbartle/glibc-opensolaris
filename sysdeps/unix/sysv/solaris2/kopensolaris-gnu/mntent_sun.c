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

#include <mntentP.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/ioctl.h>
#define _SUN_SOURCE
#include <sys/mnttab.h>

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/resetmnttab-3c  */

#define _MNT_CMP(x, y, f) \
	(!y->f || (y->f && strcmp (x->f, y->f) == 0))


int getmntent (FILE *fp, struct mnttab *mt)
{
  struct extmnttab emt;
  int res = ioctl (fileno (fp), MNTIOC_GETMNTENT, &emt);
  if (res != 0)
    return -1;

  mt->mnt_special = emt.mnt_special;
  mt->mnt_mountp = emt.mnt_mountp;
  mt->mnt_fstype = emt.mnt_fstype;
  mt->mnt_mntopts = emt.mnt_mntopts;
  mt->mnt_time = emt.mnt_time;

  return 0;
}

int getmntany (FILE *fp, struct mnttab *mt, struct mnttab *mtpref)
{
  int res;
  while ((res = getmntent (fp, mt)) == 0)
    {
      if (_MNT_CMP (mt, mtpref, mnt_special) &&
          _MNT_CMP (mt, mtpref, mnt_mountp) &&
          _MNT_CMP (mt, mtpref, mnt_fstype) &&
          _MNT_CMP (mt, mtpref, mnt_mntopts) &&
          _MNT_CMP (mt, mtpref, mnt_time))
        return 0;
    }

  return res;
}


int getextmntent(FILE *fp, struct extmnttab *emt, int len)
{
  int res = ioctl (fileno (fp), MNTIOC_GETMNTENT, emt);
  if (res != 0)
    return -1;
  return 0;
}


char *mntopt (char **opts)
{
  char *optsp = *opts;

  /* Strip leading spaces.  */
  while (*optsp == ' ')
    optsp++;

  /* Find comma.  */
  char *ret = optsp;
  while (*optsp != ',' && *optsp != '\0')
    optsp++;

  /* Replace comma with null terminator.  */
  if (*optsp == ',')
    optsp++;
  *opts = optsp;

  return ret;
}


char * hasmntopt (struct mnttab *mt, char *opt)
{
  /* We make a copy of mnt_mntopts since we modify it.  */
  char buf[MNT_LINE_MAX + 1];
  strncpy (buf, mt->mnt_mntopts, sizeof (buf))[MNT_LINE_MAX] = '\0';

  char *opts = buf;
  char *optp;
  size_t len = strlen (opt);
  while (*(optp = mntopt (&opts)))
    {
      /* Check if opt matched, taking into account delimiters (e.g. '=').  */
      if (strncmp (optp, opt, len) == 0 && !isalnum (optp[len]))
        return mt->mnt_mntopts + (optp - buf);
    }

  return NULL;
}


void resetmnttab (FILE *fp)
{
  rewind (fp);
}
