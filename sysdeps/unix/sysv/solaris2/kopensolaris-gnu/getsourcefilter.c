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

#include <netinet/in.h>
#include <alloca.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/param.h>


int
getsourcefilter (int s, uint32_t interface, const struct sockaddr *group,
		 socklen_t grouplen, uint32_t *fmode, uint32_t *numsrc,
		 struct sockaddr_storage *slist)
{
  if (grouplen < SA_LEN (group))
    {
      __set_errno (ENOPROTOOPT);
      return -1;
    }

  /* The kernel assumes at least one sockaddr_storage.  */
  int gf_len = GROUP_FILTER_SIZE (*numsrc ?: 1);
  int use_alloca = __libc_use_alloca (gf_len);
  struct group_filter *gf;
  if (use_alloca)
    gf = alloca (gf_len);
  else
    {
      gf = malloc (gf_len);
      if (!gf)
        return -1;
    }

  gf->gf_interface = interface;
  memcpy (&gf->gf_group, group, SA_LEN (group));
  gf->gf_numsrc = *numsrc;

  int res = ioctl (s, SIOCGMSFILTER, gf);
  if (res == -1)
    {
      if (!use_alloca)
        free (gf);
      return -1;
    }

  *fmode = gf->gf_fmode;
  *numsrc = MIN (gf->gf_numsrc, *numsrc);
  memcpy (slist, gf->gf_slist, *numsrc * sizeof (struct sockaddr_storage));

  if (!use_alloca)
    free (gf);
  return 0;
}
