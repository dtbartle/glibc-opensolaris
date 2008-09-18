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
#include <priv.h>
#include <bits/libc-lock.h>

__libc_lock_define_recursive (extern, __priv_lock);
libc_freeres_ptr (static priv_data_t *__data);

priv_data_t * __priv_parse_info (const priv_impl_info_t *pii)
{
  priv_data_t *data = malloc (sizeof (priv_data_t));
  if (!data)
    return NULL;
  memset (data, 0, sizeof (*data));
  data->pd_setsize = pii->priv_setsize * sizeof (priv_chunk_t);

  /* Iterate over all priv_info_t's. Note that the first priv_info_t follows
     the header.  */
  priv_info_t *pi = (priv_info_t *)((char *)pii + pii->priv_headersize);
  uint32_t left = pii->priv_globalinfosize;
  while (left)
    {
      switch (pi->priv_info_type)
        {
        case PRIV_INFO_SETNAMES:
        case PRIV_INFO_PRIVNAMES:
          if ((pi->priv_info_type == PRIV_INFO_SETNAMES &&
                data->pd_setnames) || (pi->priv_info_type ==
                PRIV_INFO_PRIVNAMES && data->pd_privnames))
            break;

          /* XXX: In priv_get*byname we linearlly scan the list of strins;
             we could speed this up by sorting the strings here.  */

          priv_info_names_t *pi_names = (priv_info_names_t *)pi;

          /* Allocate memory for the index.  */
          char **name_list = malloc (sizeof (char *) * pi_names->cnt);
          if (!name_list)
            goto err;
          if (pi->priv_info_type == PRIV_INFO_SETNAMES)
            {
              data->pd_setnames = name_list;
              data->pd_setnames_cnt = pi_names->cnt;
            }
          else
            {
              data->pd_privnames = name_list;
              data->pd_privnames_cnt = pi_names->cnt;
            }
          data->pd_privnames_cnt = pi_names->cnt;

          /* Setup the index.  */
          char *names_ptr = pi_names->names;
          char **end_list = name_list + pi_names->cnt;
          for (int i = 0; i < pi_names->cnt; i++)
            {
              name_list[i] = names_ptr;
              names_ptr += strlen (names_ptr) + 1;
            }

          break;

        case PRIV_INFO_BASICPRIVS:
          if (data->pd_basicprivs)
            break;

          if (pi->priv_info_size != data->pd_setsize)
            break;
          data->pd_basicprivs = ((priv_info_set_t *)pi)->set;

          break;
        }

      left -= pi->priv_info_size;
      pi = (priv_info_t *)((char *)pi + pi->priv_info_size);
    }

  return data;

err:

  free (data->pd_setnames);
  free (data->pd_privnames);
  free (data);

  return NULL;
}


void __priv_free_info (priv_data_t *data)
{
  free (data->pd_setnames);
  free (data->pd_privnames);
  free (data);
}


const priv_data_t * __priv_parse_data_cached (void)
{
  if (__data)
    return __data;

  __libc_lock_lock_recursive (__priv_lock);
  __data = __priv_parse_info (getprivimplinfo ());
  __libc_lock_unlock_recursive (__priv_lock);

  return __data;
}
