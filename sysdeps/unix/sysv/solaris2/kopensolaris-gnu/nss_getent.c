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

#include <nss_sunP.h>
#include <string.h>
#include <bits/libc-lock.h>

nss_status_t nss_getent (nss_db_root_t *rootp, nss_db_initf_t initf,
      nss_getent_t *contextpp, void *args)
{
  __libc_lock_lock (contextpp->lock);

  /* The first time we are called the context is NULL.  */
  if (contextpp->ctx == NULL)
    {
      /* Call setent to initialize the context.  */
      nss_setent (rootp, initf, contextpp);
      if (contextpp->ctx == NULL)
        {
          __libc_lock_unlock (contextpp->lock);
          return NSS_UNAVAIL;
        }
    }

  nss_XbyY_args_t *nssargs = (nss_XbyY_args_t *)args;
  struct nss_getent_context *ctx = contextpp->ctx;

  // TODO: Store nssargs->str2ent in a global table and use it for parsing.

  int res = __nss_getent_r (ctx->getfuncname, ctx->setfuncname,
      ctx->dblookupfunc, &ctx->nip, &ctx->startp, &ctx->last_nip,
      &ctx->stayopen_tmp, 0, nssargs->buf.result, nssargs->buf.buffer,
      nssargs->buf.buflen, &nssargs->returnval, &nssargs->h_errno);

  __libc_lock_unlock (contextpp->lock);

  if (res != 0)
    __set_errno (res);
  return RESULT_TO_STATUS (res);
}
