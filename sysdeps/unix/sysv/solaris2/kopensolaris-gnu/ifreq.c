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

#include <net/if.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <not-cancel.h>
#include <memory.h>

void
__ifreq (struct ifreq **ifreqs, int *num_ifs, int sockfd)
{
  struct ifconf ifc;
  int nifs;
  char *buf;

  /* Determine number of interfaces.  */
  if (__ioctl (sockfd, SIOCGIFNUM, &nifs) != 0)
      return;

  /* Get interfaces.  */
  ifc.ifc_len = nifs * sizeof(struct ifreq);
  buf = malloc (ifc.ifc_len);
  ifc.ifc_buf = buf;
  if (buf == NULL)
      return;
  if (__ioctl (sockfd, SIOCGIFCONF, &ifc) != 0)
    {
      free (buf);
      return;
    }

  *ifreqs = (struct ifreq *)buf;
  *num_ifs = nifs;
}
