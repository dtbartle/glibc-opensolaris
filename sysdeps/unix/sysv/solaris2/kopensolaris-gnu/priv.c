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
#include <sys/priocntl.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

DECLARE_INLINE_SYSCALL (int, privsys, int code, priv_op_t op,
    priv_ptype_t type, void *buf, size_t bufsize);

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/6mbb3hrjc
         http://docs.sun.com/app/docs/doc/816-5168/6mbb3hrj7
         http://docs.sun.com/app/docs/doc/816-5167/setppriv-2
         http://docs.sun.com/app/docs/doc/816-5175/privileges-5  */

__libc_lock_define_initialized_recursive (, __priv_lock);
libc_freeres_ptr (static priv_impl_info_t *__info);

/* Note: Almost everything that uses getprivimplinfo assumes it won't fail so
   we assert that this call succeeds.  */
const priv_impl_info_t * getprivimplinfo (void)
{
  if (__info)
    return __info;

  __libc_lock_lock_recursive (__priv_lock);

  /* First call: get header.  */
  priv_impl_info_t _info;
  int res = INLINE_SYSCALL (privsys, 5, SYS_SUB_getimplinfo, 0, 0, &_info,
      sizeof(_info));
  if (res == 0)
    {
      /* Second call: alloc and get full priv_impl_info_t.  */
      size_t info_size = PRIV_IMPL_INFO_SIZE (&_info);
      __info = malloc (info_size);
      assert (__info);
      res = INLINE_SYSCALL (privsys, 5, SYS_SUB_getimplinfo, 0, 0, __info,
          info_size);
      assert (res == 0);
    }

  __libc_lock_unlock_recursive (__priv_lock);
  return __info;
}


int getppriv (priv_ptype_t which, priv_set_t *set)
{
  int setn = priv_getsetbyname (which);
  if (setn == -1)
    return -1;

  return INLINE_SYSCALL (privsys, 5, SYS_SUB_getppriv, 0, (priv_ptype_t)setn,
      (void *)set, __PRIVSETSIZE);
}


int setppriv (priv_op_t op, priv_ptype_t which, const priv_set_t *set)
{
  int setn = priv_getsetbyname (which);
  if (setn == -1)
    return -1;

  return INLINE_SYSCALL (privsys, 5, SYS_SUB_setppriv, op, (priv_ptype_t)setn,
      (void *)set, __PRIVSETSIZE);
}


priv_set_t *priv_allocset (void)
{
  return malloc (__PRIVSETSIZE);
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


void priv_emptyset (priv_set_t *sp)
{
  memset (sp, 0, __PRIVSETSIZE);
}


void priv_fillset(priv_set_t *sp)
{
  memset (sp, ~0, __PRIVSETSIZE);
}


void priv_copyset (const priv_set_t *src, priv_set_t *dst)
{
  memcpy (dst, src, __PRIVSETSIZE);
}


int priv_addset (priv_set_t *sp, const char *priv)
{
  int privn = priv_getbyname (priv);
  if (privn == -1)
    return -1;

  ((priv_chunk_t *)sp)[__PRIVELT (privn)] |= __PRIVMASK (privn);
  return 0;
}


int priv_delset (priv_set_t *sp, const char *priv)
{
  int privn = priv_getbyname (priv);
  if (privn == -1)
    return -1;

  ((priv_chunk_t *)sp)[__PRIVELT (privn)] &= ~__PRIVMASK (privn);
  return 0;
}


void priv_intersect (const priv_set_t *src, priv_set_t *dst)
{
  priv_chunk_t *pcsrc = (priv_chunk_t *)src;
  priv_chunk_t *pcdst = (priv_chunk_t *)dst;
  for (int i = 0; i < __PRIVSETCHUNKS; i++)
    pcdst[__PRIVELT (i)] &= pcsrc[__PRIVELT (i)];
}


void priv_union (const priv_set_t *src, priv_set_t *dst)
{
  priv_chunk_t *pcsrc = (priv_chunk_t *)src;
  priv_chunk_t *pcdst = (priv_chunk_t *)dst;
  for (int i = 0; i < __PRIVSETCHUNKS; i++)
    pcdst[__PRIVELT (i)] |= pcsrc[__PRIVELT (i)];
}


void priv_inverse(priv_set_t *sp)
{
  priv_chunk_t *pcsp = (priv_chunk_t *)sp;
  for (int i = 0; i < __PRIVSETCHUNKS; i++)
    pcsp[i] = ~pcsp[i];
}


boolean_t priv_isemptyset (const priv_set_t *sp)
{
  priv_chunk_t *pcsp = (priv_chunk_t *)sp;
  for (int i = 0; i < __PRIVSETCHUNKS; i++)
    if (pcsp[i])
      return _B_FALSE;
  return _B_TRUE;
}


boolean_t priv_isfullset (const priv_set_t *sp)
{
  priv_chunk_t *pcsp = (priv_chunk_t *)sp;
  for (int i = 0; i < __PRIVSETCHUNKS; i++)
    if (~pcsp[i])
      return _B_FALSE;
  return _B_TRUE;
}


boolean_t priv_ismember (const priv_set_t *sp, const char *priv)
{
  int privn = priv_getbyname (priv);
  if (privn == -1)
    return _B_FALSE;

  return (((priv_chunk_t *)sp)[__PRIVELT (privn)] & __PRIVMASK (privn)) ?
      _B_TRUE : _B_FALSE;
}


boolean_t priv_issubset (const priv_set_t *src, const priv_set_t *dst)
{
  priv_chunk_t *pcsrc = (priv_chunk_t *)src;
  priv_chunk_t *pcdst = (priv_chunk_t *)dst;
  for (int i = 0; i < __PRIVSETCHUNKS; i++)
    if ((pcsrc[__PRIVELT (i)] & pcdst[__PRIVELT (i)]) != pcsrc[__PRIVELT (i)])
      return _B_FALSE;
  return _B_TRUE;
}


int priv_set (priv_op_t op, priv_ptype_t which, ...)
{
  va_list ap;
  va_start (ap, which);

  priv_set_t *pset = priv_allocset ();
  if (!pset)
    return -1;

  const char *priv;
  while ((priv = va_arg (ap, const char *)))
    {
      if (priv_addset (pset, priv) == -1)
        return -1;
    }

  int ret;
  if (which == NULL)
    {
      /* Set all sets.  */
      for (int i = 0; i < __PRIVSETCHUNKS; i++)
        {
          ret = setppriv (op, which, pset);
          if (ret == -1)
            break;
        }
    }
  else
    {
      ret = setppriv (op, which, pset);
    }

  priv_freeset (pset);
  return 0;
}

boolean_t priv_ineffect (const char *priv)
{
  priv_set_t *pset = priv_allocset ();
  if (!pset)
    return _B_FALSE;

  int res = getppriv (PRIV_EFFECTIVE, pset);
  if (res == -1)
    return _B_FALSE;

  boolean_t ret = priv_ismember (pset, priv);

  priv_freeset (pset);

  return ret;
}
