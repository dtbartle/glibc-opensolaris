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
#include <sys/ioctl.h>
#include <string.h>


int
setipv4sourcefilter (int s, struct in_addr interface, struct in_addr group,
		     uint32_t fmode, uint32_t numsrc,
		     const struct in_addr *slist)
{
  /* The kernel assumes at least one in_addr.  */
  int imsf_len = IP_MSFILTER_SIZE (numsrc ?: 1);
  int use_alloca = __libc_use_alloca (imsf_len);
  struct ip_msfilter *imsf;
  if (use_alloca)
    imsf = alloca (imsf_len);
  else
    {
      imsf = malloc (imsf_len);
      if (!imsf)
        return -1;
    }

  imsf->imsf_multiaddr = group;
  imsf->imsf_interface = interface;
  imsf->imsf_fmode = fmode;
  imsf->imsf_numsrc = numsrc;
  memcpy (slist, imsf->imsf_slist, numsrc * sizeof (struct in_addr));

  int res = ioctl (s, SIOCSIPMSFILTER, imsf);
  if (res == -1)
    {
      if (!use_alloca)
        free (imsf);
      return -1;
    }

  if (!use_alloca)
    free (imsf);
  return 0;
}
