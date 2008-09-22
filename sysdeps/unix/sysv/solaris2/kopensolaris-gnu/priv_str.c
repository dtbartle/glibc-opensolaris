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

#include <privP.h>
#include <zoneP.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/priv-str-to-set-3c  */

priv_set_t *priv_str_to_set (const char *buf, const char *sep,
      const char **endptr)
{
  /* Take a copy of the string since strtok_r will modify it.  */
  char *str = strdup (buf);
  if (!str)
    return NULL;

  priv_set_t *set = priv_allocset ();
  if (!set)
    {
      free (str);
      return NULL;
    }
  priv_emptyset (set);
  const priv_data_t *data = __priv_parse_data_cached ();
  if (!data)
    return NULL;
  priv_set_t *basic = data->pd_basicprivs;

  char *saveptr;
  char *priv = strtok_r (str, sep, &saveptr);
  if (!priv)
    return set;
  do
    {
      if (strcmp (priv, "basic") == 0 && basic)
          priv_union (basic, set);
      else if (strcmp (priv, "all") == 0)
          priv_fillset (set);
      else if (strcmp (priv, "none") == 0)
          priv_emptyset (set);
      else if (strcmp (priv, "zone") == 0)
        {
          priv_set_t *zone = priv_allocset ();
          if (!zone)
            goto inval;
          if (zone_getattr (getzoneid (), ZONE_ATTR_PRIVSET,
                zone, __PRIVSETSIZE) == 0)
            priv_union (zone, set);
          priv_freeset (zone);
        }
      else
        {
          int negate = *str == '-' || *str == '!';
          if (negate)
            str++;
          int privnum = priv_getbyname (str);
          if (privnum == -1)
            goto inval;

          if (negate)
            priv_delset (set, privnum);
          else
            priv_addset (set, privnum);
        }
    }
  while ((priv = strtok_r (NULL, sep, &saveptr))) ;

  free (str);
  return set;

inval:

   priv_freeset (set);
   free (str);
   __set_errno (EINVAL);
  return NULL;
}
