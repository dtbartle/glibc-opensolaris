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
#include <atomic.h>
#include <assert.h>

nss_status_t nss_search (nss_db_root_t *rootp, nss_db_initf_t initf,
      int search_fnum, void *search_args)
{
  pthread_mutex_lock (&rootp->lock);

  /* If we've never called nss_search then the context is NULL.  */
  if (rootp->s == NULL)
    {
      /* Determine dbid.  */
      nss_db_params_t conf;
      initf (&conf);
      int dbid = __nss_get_dbid (conf.name);
      if (dbid == -1)
        {
          pthread_mutex_unlock (&rootp->lock);
          return NSS_ERROR;
        }

      /* Allocate context.  */
      rootp->s = malloc (sizeof (struct nss_db_state));
      if (!rootp->s)
        {
          pthread_mutex_unlock (&rootp->lock);
          return NSS_ERROR;
        }
      struct nss_db_state *ctx = rootp->s;
      memset (ctx, 0, sizeof (*ctx));

      /* Get db lookup func.  */
      ctx->dblookupfunc = __nss_get_dblookupfunc (dbid);

      /* Get dbtable.  */
      ctx->dbtable = __nss_get_dbtable (dbid);
      assert (ctx->dbtable);
    }

  struct nss_db_state *ctx = rootp->s;

  /* Make sure we know about search_fnum.  */
  if (search_fnum < 0 || search_fnum >= _NSS_DBENTRY_MAX)
    {
      pthread_mutex_unlock (&rootp->lock);
      return NSS_ERROR;
    }
  const char *searchfuncname = ctx->dbtable[search_fnum];

  nss_XbyY_args_t* nssargs = (nss_XbyY_args_t *)search_args;

  /* The rest of this is based on the code in nss/getXXbyYY_r.c.  */

  service_user *nip;
  union
  {
    lookup_function l;
    void *ptr;
  } fct;

  int no_more;
  enum nss_status status = NSS_STATUS_UNAVAIL;

  if (!ctx->startp_initialized)
    {
      no_more = ctx->dblookupfunc (&nip, searchfuncname, &fct.ptr);
      if (no_more)
        {
          void *tmp_ptr = (service_user *) -1l;
          PTR_MANGLE (tmp_ptr);
          ctx->startp = tmp_ptr;
        }
      else
        {
          void *tmp_ptr = fct.l;
          PTR_MANGLE (tmp_ptr);
          ctx->start_fct = tmp_ptr;
          tmp_ptr = nip;
          PTR_MANGLE (tmp_ptr);
          ctx->startp = tmp_ptr;
        }

      /* Make sure start_fct and startp are written before
         startp_initialized.  */
      atomic_write_barrier ();
      ctx->startp_initialized = true;
    }
  else
    {
      fct.l = ctx->start_fct;
      PTR_DEMANGLE (fct.l);
      nip = ctx->startp;
      PTR_DEMANGLE (nip);
      no_more = nip == (service_user *) -1l;
    }

  while (no_more == 0)
    {
      status = DL_CALL_FCT (fct.l, (nssargs->buf.result, nssargs->buf.buffer,
          nssargs->buf.buflen, &errno));

      /* The status is NSS_STATUS_TRYAGAIN and errno is ERANGE the
          provided buffer is too small.  In this case we should give
          the user the possibility to enlarge the buffer and we should
          not simply go on with the next service (even if the TRYAGAIN
          action tells us so).  */
      if (status == NSS_STATUS_TRYAGAIN && errno == ERANGE)
        break;

      no_more = __nss_next (&nip, searchfuncname, &fct.ptr, status, 0);
    }

  nss_status_t res;
  if (status == NSS_STATUS_SUCCESS || status == NSS_STATUS_NOTFOUND)
    res = NSS_SUCCESS;
  else
    res = NSS_ERROR;

  if (errno == ERANGE && status != NSS_STATUS_TRYAGAIN)
    __set_errno (EINVAL);

  pthread_mutex_unlock (&rootp->lock);

  return res;
}
