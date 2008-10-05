/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>.

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

#include <unistd.h>
#include <streams/stropts.h>
#include <sys/ptms.h>
#include <grp.h>
#include <stddef.h>
#include <memory.h>
#include <errno.h>

#define INIT_GROUP_LEN	0x0100
#define MAX_GROUP_LEN	0x8000

int
grantpt (int fd)
{
  pt_own_t pto;
  pto.pto_ruid = getuid ();
  pto.pto_rgid = -1;

  /* Keep calling getgrnam with a bigger buffer.  */
  size_t len = INIT_GROUP_LEN;
  char *buf = NULL;
  struct group gr, *gro;
  do
    {
      buf = realloc (buf, len);
      if (!buf)
        {
          /* If we can't allocate 64 KB something is wrong.  */
          free(buf);
          return -1;
        }
      gro = NULL;
      int result = getgrnam_r ("tty", &gr, buf, len, &gro);
      if(result == 0)
        {
          /* No entry found.  */
          if(gro == NULL)
            break;
          pto.pto_rgid = gro->gr_gid;
        }
      else if (errno != EINTR && errno != ERANGE && errno != ENOMEM)
        {
          /* Unknown error - assume failure.  */
          break;
        }

      len <<= 1;
    }
  while (len < MAX_GROUP_LEN);
  free (buf);

  /* If getgrnam fails we use the user's gid.  */
  if (pto.pto_rgid == -1)
    pto.pto_rgid = getgid ();

  /* Send OWNERPT down.  */
  struct strioctl si;
  si.ic_cmd = OWNERPT;
  si.ic_timout = 0;
  si.ic_len = sizeof (pt_own_t);
  si.ic_dp = (char *)&pto;

  int res = (ioctl (fd, I_STR, &si) < 0) ? -1 : 0;
  if (res != 0 && errno == ENOTTY)
    __set_errno (EINVAL);
  return res;
}
