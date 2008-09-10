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

#pragma weak ps_pread

rd_err_e rd_loadobj_iter (rd_agent_t *rdap, rl_iter_f *cb, void *clnt_data)
{
  ps_err_e res;

  /* Read r_debug.  */
  struct r_debug r_debug;
  res = ps_pread (rdap->rd_php, rdap->rd_r_debug, &r_debug, sizeof (r_debug));
  if (res != PS_OK)
    return RD_DBERR;

  struct link_map *r_map_ptr = r_debug.r_map;
  while (r_map_ptr)
    {
      /* Read in the current r_map.  */
      struct link_map r_map;
      res = ps_pread (rdap->rd_php, r_map_ptr, &r_map, sizeof (r_map));
      if (res != PS_OK)
        return RD_DBERR;

      /* Fill in rd_loadobj_t.  */
      rd_loadobj_t loadobj = {0};
      loadobj.rl_nameaddr = r_map.l_name;
      loadobj.rl_flags = 0;
      if (r_map.l_relocated)
        loadobj.rl_flags |= RD_FLG_MEM_OBJECT;
      loadobj.rl_base = r_map.l_addr;
      loadobj.rl_data_base = r_map.l_phdr;
      loadobj.rl_lmident = r_map.l_ns;
      /* pl_refnameaddr is unused.  */
      /* rl_plt_base and rl_plt_size are unused.  */
      /* TODO: do we need to worry about these (added in rtld_db v3)?  */
        loadobj.rl_bend = 0; //r_map.l_map_end;
        loadobj.rl_padstart = 0; //r_map.l_map_start;
        loadobj.rl_padend = 0; //r_map.l_map_end;
      loadobj.rl_dynamic = r_map.l_ld;

      if (cb (&loadobj, clnt_data) == 0)
        break;

      r_map_ptr = r_map.l_next;
    }

  return RD_OK;
}
