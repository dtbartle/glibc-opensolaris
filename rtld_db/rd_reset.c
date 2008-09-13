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

#include <rtld_db.h>
#include <rtld_dbP.h>
#include <sys/link.h>
#include <proc_service.h>

#pragma weak ps_pglobal_lookup

rd_err_e rd_reset (struct rd_agent *rdap)
{
  ps_err_e res;
  psaddr_t addr;

  /* Read _r_debug from ld.so (the dynamic case).  */
  if (&ps_pglobal_lookup == NULL)
    return RD_NOCAPAB;
  res = ps_pglobal_lookup (rdap->rd_php, PS_OBJ_LDSO, "_r_debug", &addr);
  if (res == PS_OK )
      rdap->rd_r_debug = (struct r_debug *)addr;
  else
    {
      /* TODO: Scan executable's .dynamic section (the static case).  */

      return RD_DBERR;
    }

  /* Lookup symbols for rtld_db_preinit, rtld_db_postinit,
     rtld_db_dlactivity, and rtld_db_event_msg.  */
  /* TODO: Does this work for static executables?  */
  res = ps_pglobal_lookup (rdap->rd_php, PS_OBJ_LDSO, "rtld_db_preinit", &addr);
  if (res != PS_OK)
    return RD_DBERR;
  rdap->rd_preinit = (void (*)(void *))addr;
  res = ps_pglobal_lookup (rdap->rd_php, PS_OBJ_LDSO, "rtld_db_postinit", &addr);
  if (res != PS_OK)
    return RD_DBERR;
  rdap->rd_postinit = (void (*)(void *))addr;
  res = ps_pglobal_lookup (rdap->rd_php, PS_OBJ_LDSO, "rtld_db_dlactivity", &addr);
  if (res != PS_OK)
    return RD_DBERR;
  rdap->rd_dlactivity = (void (*)(void *))addr;
  res = ps_pglobal_lookup (rdap->rd_php, PS_OBJ_LDSO, "rtld_db_event_msg", &addr);
  if (res != PS_OK)
    return RD_DBERR;
  rdap->rd_event_msg = (rd_event_msg_t *)addr;

  return RD_OK;
}
