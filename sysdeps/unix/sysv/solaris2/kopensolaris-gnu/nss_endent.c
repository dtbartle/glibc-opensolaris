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

#include <nssP.h>
#include <string.h>
#include <pthread.h>

void nss_endent (nss_db_root_t *rootp, nss_db_initf_t initf,
      nss_getent_t *contextpp)
{
  if (contextpp->ctx == NULL)
    return;

  pthread_mutex_lock (&contextpp->lock);

  struct nss_getent_context *ctx = contextpp->ctx;
  __nss_endent (ctx->endfuncname, ctx->dblookupfunc, &ctx->nip, &ctx->startp,
      &ctx->last_nip, 0);

  /* Free context.  */
  free (contextpp->ctx);
  contextpp->ctx = NULL;

  pthread_mutex_unlock (&contextpp->lock);
}
