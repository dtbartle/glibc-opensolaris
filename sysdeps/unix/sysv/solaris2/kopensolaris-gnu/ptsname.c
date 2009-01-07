/* Copyright (C) 1998, 2000, 2001, 2002, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Zack Weinberg <zack@rabi.phys.columbia.edu>, 1998.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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

#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdio-common/_itoa.h>
#include <errno.h>
#include <sys/ptms.h>
#include <streams/stropts.h>
#include <sys/sysmacros.h>

/* Directory where we can find the slave pty nodes.  */
#define _PATH_DEVPTS "/dev/pts/"

/* Static buffer for `ptsname'.  */
static char buffer[sizeof (_PATH_DEVPTS) + 20];

/* Return the pathname of the pseudo terminal slave assoicated with
   the master FD is open on, or NULL on errors.
   The returned storage is good until the next call to this function.  */
char *
ptsname (int fd)
{
  return __ptsname_r (fd, buffer, sizeof (buffer)) != 0 ? NULL : buffer;
}


/* Store at most BUFLEN characters of the pathname of the slave pseudo
   terminal associated with the master FD is open on in BUF.
   Return 0 on success, otherwise an error number.  */
int
__ptsname_r (int fd, char *buf, size_t buflen)
{
    if (buf == NULL)
    {
        __set_errno (EINVAL);
        return EINVAL;
    }

    /* isatty doesn't work on ptm's.  */
    struct strioctl si;
    si.ic_cmd = ISPTM;
    si.ic_len = 0;
    si.ic_timout = 0;
    si.ic_dp = NULL;
    if (ioctl(fd, I_STR, &si) != 0)
      {
        __set_errno (ENOTTY);
        return ENOTTY;
      }

    /* Get the minor number of the pts.  */
    struct stat st;
    if (fstat (fd, &st) < 0)
        return -1;
    int ptyno = minor (st.st_rdev);

    /* Buffer we use to print the number in.  For a maximum size for
       `int' of 8 bytes we never need more than 20 digits.  */
    char numbuf[21];
    const char *devpts = _PATH_DEVPTS;
    const size_t devptslen = strlen (_PATH_DEVPTS);
    char *p;

    numbuf[sizeof (numbuf) - 1] = '\0';
    p = _itoa_word (ptyno, &numbuf[sizeof (numbuf) - 1], 10, 0);

    if (buflen < devptslen + (&numbuf[sizeof (numbuf)] - p))
      {
        __set_errno (ERANGE);
        return ERANGE;
      }

    memcpy (__stpcpy (buf, devpts), p, &numbuf[sizeof (numbuf)] - p);

    return 0;
}
weak_alias (__ptsname_r, ptsname_r)
