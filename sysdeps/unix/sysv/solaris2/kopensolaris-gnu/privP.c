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
#include <stdarg.h>
#include <grp.h>
#include <bits/libc-lock.h>

__libc_lock_define_recursive (extern, __priv_lock);
libc_freeres_ptr (static priv_data_t *__data);
static priv_set_t *__suidset = NULL;

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
          data->pd_basicprivs = (priv_set_t *)((priv_info_set_t *)pi)->set;

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


/* Specify what privileges an suid root binary needs.  */
int __init_suid_priv (int flags, ...)
{
  int res = 0;
  priv_set_t *permit = NULL, *inherit = NULL, *scratch = NULL;

  /* Check flags.  */
  if (flags != PU_LIMITPRIVS && flags != PU_CLEARLIMITSET)
    return -1;

  /* We can only initialize once.  */
  if (__suidset)
    return -1;

  /* Do nothing if we are running as root but not setuid root.  */
  uid_t uid = getuid ();
  uid_t euid = geteuid ();
  if (uid == 0 && euid == 0)
    return 0;

  /* Allocate a scratch set.  */
  scratch = priv_allocset ();
  if (!scratch)
    goto error;

  /* Get the basic set.  */
  const priv_data_t *pd = __priv_parse_data_cached ();
  if (!pd)
    goto error;
  priv_set_t *basic = pd->pd_basicprivs;

  /* Get the inherited set.  */
  inherit = priv_allocset ();
  if (!inherit)
    goto error;
  if (getppriv (PRIV_INHERITABLE, inherit) != 0)
    goto error;

  /* Get the permitted set.  */
  permit = priv_allocset ();
  if (!permit)
    goto error;
  if (getppriv (PRIV_PERMITTED, permit) != 0)
    goto error;

  /* Get passed privileges.  */
  __suidset = priv_allocset ();
  if (!__suidset)
    goto error;
  priv_emptyset (__suidset);
  va_list ap;
  va_start (ap, flags);
  const char *priv;
  while ((priv = va_arg (ap, const char *)))
    if (priv_addset (__suidset, priv) != 0)
      goto error;

  /* Make sure that the passed privileges are a subset of the current
     permitted privileges.  */
  if (priv_issubset (__suidset, permit) != B_TRUE)
    goto error;

  /* Set the effective privileges to the inherited ones.  */
  if (setppriv (PRIV_SET, PRIV_EFFECTIVE, inherit) != 0)
    goto error;

  /* Set the permitted privileges to those currently permitted privileges in
     set of the ones passed in, the inherited ones, and the basic set.  */
  priv_copyset (__suidset, scratch);
  priv_union (inherit, scratch);
  if (basic)
    priv_union (basic, scratch);
  priv_intersect (permit, scratch);
  if (setppriv (PRIV_SET, PRIV_PERMITTED, scratch) != 0)
    goto error;

  /* Check if we need to set the limit set.  */
  if (flags & PU_CLEARLIMITSET)
    {
      priv_emptyset (scratch);
      if (setppriv (PRIV_SET, PRIV_LIMIT, scratch) != 0)
        goto error;
    }
  else if (flags & PU_LIMITPRIVS)
    {
      if (setppriv (PRIV_SET, PRIV_LIMIT, scratch) != 0)
        goto error;
    }

  /* Change the uid to the caller's uid if we're setuid root.  */
  if (euid == 0 && setreuid (uid, uid) != 0)
    goto error;

  goto out;

error:
  res = -1;
  if (__suidset)
    {
      priv_freeset (__suidset);
      __suidset = NULL;
    }
  if (euid == 0)
    setreuid (uid, uid);

out:
  priv_freeset (permit);
  priv_freeset (inherit);
  priv_freeset (scratch);

  return res;
}


// TODO
#if 0
int __init_daemon_priv (int flags, uid_t uid, gid_t gid, ...)
{
}


void __fini_daemon_priv (const char *priv, ...)
{
}
#endif


/* Enable or disable those privileges passed in __init_suid_priv.  */
int __priv_bracket (priv_op_t op)
{
  if (op != PRIV_ON && op != PRIV_OFF)
    {
      __set_errno (EINVAL);
      return -1;
    }

  /* We can only toggle privileges if __init_suid_priv was called.  */
  if (__suidset)
    return setppriv (op, PRIV_EFFECTIVE, __suidset);
  else
    return 0;
}


/* Permanently disable those privileges passed in __init_suid_priv.  */
void __priv_relinquish (void)
{
  if (__suidset)
    {
      setppriv (PRIV_OFF, PRIV_PERMITTED, __suidset);
      priv_freeset (__suidset);
      __suidset = NULL;
    }
}
