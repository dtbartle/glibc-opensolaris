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

void nss_setent (nss_db_root_t *rootp, nss_db_initf_t initf,
      nss_getent_t *contextpp)
{
  __libc_lock_lock (contextpp->lock);

  /* If we've never called nss_setent then the context is NULL.  */
  if (contextpp->ctx == NULL)
    {
      /* Allocate context.  */
      contextpp->ctx = malloc (sizeof (struct nss_getent_context));
      if (!contextpp->ctx)
        {
          __libc_lock_unlock (contextpp->lock);
          return;
        }
      struct nss_getent_context *ctx = contextpp->ctx;
      memset (ctx, 0, sizeof (*ctx));

      /* Construct names.  */
      nss_db_params_t conf;
      initf (&conf);
      sprintf (ctx->getfuncname, "get%sent", conf.name);
      sprintf (ctx->setfuncname, "set%sent", conf.name);
      sprintf (ctx->endfuncname, "end%sent", conf.name);

      /* Get db lookup func.  */
      ctx->dblookup = __nss_dbname_to_lookup (conf.name);
    }

  struct nss_getent_context *ctx = contextpp->ctx;
  __nss_setent (ctx->setfuncname, ctx->dblookup, &ctx->nip, &ctx->startp,
      &ctx->last_nip, ctx->stayopen, &ctx->stayopen_tmp, 0);

  __libc_lock_unlock (contextpp->lock);
}
