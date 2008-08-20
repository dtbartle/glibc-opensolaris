/* Copyright (C) 1997,98,99,2000,02,08 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
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

#include <net/if.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <not-cancel.h>
#include <memory.h>

/* TODO: we might need to query the interfaces separately */
unsigned int
if_nametoindex (const char *ifname)
{
  struct lifreq lifr;
  int fd = __opensock ();

  if (fd < 0)
    return 0;

  strncpy (lifr.lifr_name, ifname, sizeof (lifr.lifr_name));
  if (__ioctl (fd, SIOCGLIFINDEX, &lifr) < 0)
    {
      close_not_cancel_no_status (fd);
      return -1;
    }
  close_not_cancel_no_status (fd);
  return lifr.lifr_index;
}
libc_hidden_def (if_nametoindex)


char *
if_indextoname (unsigned int ifindex, char *ifname)
{
  struct if_nameindex *idx;
  struct if_nameindex *p;
  char *result = NULL;

  idx = if_nameindex ();

  if (idx != NULL)
    {
      for (p = idx; p->if_index || p->if_name; ++p)
        if (p->if_index == ifindex)
          {
            result = strncpy (ifname, p->if_name, IFNAMSIZ);
            break;
          }

      if_freenameindex (idx);

      if (result == NULL)
        __set_errno (ENXIO);
    }
  return result;
}
libc_hidden_def (if_indextoname)


void
if_freenameindex (struct if_nameindex *ifn)
{
  struct if_nameindex *ptr = ifn;
  while (ptr->if_name || ptr->if_index)
    {
      free (ptr->if_name);
      ++ptr;
    }
  free (ifn);
}
libc_hidden_def (if_freenameindex)


struct if_nameindex *
if_nameindex (void)
{
  int fd = __opensock ();
  int flags = LIFC_NOXMIT | LIFC_TEMPORARY | LIFC_ALLZONES;
  unsigned int nifs, i;
  char *buf;
  struct if_nameindex *idx = NULL;
  struct lifnum lifn;
  struct lifconf lifc;
  struct lifreq *lifr;

  if (fd < 0)
    return NULL;

  /* determine number of interfaces */
  lifn.lifn_family = AF_UNSPEC;
  lifn.lifn_flags = flags;
  if (__ioctl (fd, SIOCGLIFNUM, &lifn) < 0)
    {
      close_not_cancel_no_status (fd);
      return NULL;
    }
  nifs = lifc.lifc_len;

  /* get interfaces */
  lifc.lifc_family = AF_UNSPEC;
  lifc.lifc_flags = flags;
  lifc.lifc_len = nifs * sizeof(struct lifreq);
  lifc.lifc_buf = buf = malloc (lifc.lifc_len);
  if (buf == NULL)
    {
      close_not_cancel_no_status (fd);
      return NULL;
    }
  if (__ioctl (fd, SIOCGLIFCONF, &lifc) < 0)
    {
      close_not_cancel_no_status (fd);
      free (buf);
      return NULL;
    }
  lifr = lifc.lifc_req;

  idx = malloc ((nifs + 1) * sizeof (struct if_nameindex));
  if (idx == NULL)
    {
      close_not_cancel_no_status (fd);
      free (buf);
      return NULL;
    }

  /* TODO: apparently we might get duplicate interfaces */
  for (i = 0; i < nifs; ++i)
    {
      idx[i].if_name = __strdup (lifr->lifr_name);
      if (idx[i].if_name == NULL)
        {
          close_not_cancel_no_status (fd);
          free (buf);
          free (idx);
          return NULL;
        }
      idx[i].if_index = if_nametoindex (lifr->lifr_name);
    }

  idx[i].if_index = 0;
  idx[i].if_name = NULL;

  close_not_cancel_no_status (fd);
  free(buf);
  return idx;
}
libc_hidden_def (if_nameindex)
