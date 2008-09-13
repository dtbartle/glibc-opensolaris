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

#pragma weak ps_pread

rd_err_e rd_event_getmsg (rd_agent_t *rdap, rd_event_msg_t *emsg)
{
  /* Read rd_event_msg.  */
  ps_err_e res = ps_pread (rdap->rd_php, rdap->rd_event_msg, emsg,
      sizeof (*emsg));
  if (res != PS_OK)
    return RD_DBERR;
  return RD_OK;
}
