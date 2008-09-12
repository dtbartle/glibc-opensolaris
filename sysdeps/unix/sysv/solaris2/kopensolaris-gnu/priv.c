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

#include <inline-syscall.h>
#include <privP.h>
#include <priv.h>
#include <sys/priocntl.h>
#include <string.h>

DECLARE_INLINE_SYSCALL (int, privsys, int code, priv_op_t op,
    priv_ptype_t type, void *buf, size_t bufsize, int itype);

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/6mbb3hrjc?a=view
         http://docs.sun.com/app/docs/doc/816-5167/setppriv-2?a=view */

__libc_lock_define_initialized_recursive (, __priv_lock);
libc_freeres_ptr (static priv_impl_info_t *__info);

const priv_impl_info_t * getprivimplinfo (void)
{
  if (__info)
    return __info;

  __libc_lock_lock_recursive (__priv_lock);

  /* First call: get header.  */
  priv_impl_info_t _info;
  int result = INLINE_SYSCALL (privsys, 6, PRIVSYS_GETIMPLINFO, 0, 0, &_info,
      sizeof(_info), 0);
  if (result == 0)
    {
      /* Second call: alloc and get full priv_impl_info_t.  */
      size_t info_size = PRIV_IMPL_INFO_SIZE (&_info);
      __info = malloc (info_size);
      result = INLINE_SYSCALL (privsys, 6, PRIVSYS_GETIMPLINFO, 0, 0, __info,
          info_size, 0);
      if (result != 0)
        {
          free (__info);
          __info = NULL;
        }
    }

  __libc_lock_unlock_recursive (__priv_lock);
  return __info;
}


priv_set_t *priv_allocset (void)
{
  const priv_impl_info_t *pii = getprivimplinfo ();
  if (!pii)
    return NULL;

  return malloc (pii->priv_setsize * sizeof (priv_chunk_t));
}


void priv_freeset (priv_set_t *sp)
{
  free (sp);
}


int priv_getbyname (const char *privname)
{
  const priv_data_t *pd = __priv_parse_data_cached ();
  if (!pd)
    return -1;

  for (uint32_t i = 0; i < pd->pd_privnames_cnt; i++)
    {
      if (strcasecmp (pd->pd_privnames[i], privname) == 0)
        return i;
    }

  __set_errno (EINVAL);
  return -1;
}


const char *priv_getbynum (int privnum)
{
  const priv_data_t *pd = __priv_parse_data_cached ();
  if (!pd)
    return NULL;

  if (privnum < 0 || privnum >= pd->pd_privnames_cnt)
    {
      __set_errno (EINVAL);
      return NULL;
    }

  return pd->pd_privnames[privnum];
}


int priv_getsetbyname (const char *privsetname)
{
  const priv_data_t *pd = __priv_parse_data_cached ();
  if (!pd)
    return -1;

  for (uint32_t i = 0; i < pd->pd_setnames_cnt; i++)
    {
      if (strcasecmp (pd->pd_setnames[i], privsetname) == 0)
        return i;
    }

  __set_errno (EINVAL);
  return -1;
}


const char *priv_getsetbynum (int privsetnum)
{
  const priv_data_t *pd = __priv_parse_data_cached ();
  if (!pd)
    return NULL;

  if (privsetnum < 0 || privsetnum >= pd->pd_setnames_cnt)
    {
      __set_errno (EINVAL);
      return NULL;
    }

  return pd->pd_setnames[privsetnum];
}
