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
#include <sys/priocntl.h>
#include <sys/procset.h>
#include <stdarg.h>
#include <errno.h>

DECLARE_INLINE_SYSCALL (int, priocntlsys, int pc_version, procset_t *psp,
    int cmd, ...);

/* Docs: http://docs.sun.com/app/docs/doc/816-0212/6m6nd4ncg?a=view
         http://docs.sun.com/app/docs/doc/816-0212/6m6nd4nch?a=view */

static long __priocntl_common (procset_t *ps, int cmd, va_list ap)
{
  void *arg = va_arg (ap, void *);

  if (cmd == PC_GETXPARMS || cmd == PC_SETXPARMS)
    {
      /* fetch up to PC_VAPARMCNT key/values */
      pc_vaparms_t vp;
      int i;
      for (i = 0; ; i++)
        {
          if (i >= PC_VAPARMCNT)
            return EINVAL;

          /* fetch key/value */
          int key = va_arg (ap, int);
          if (key == PC_KY_NULL)
            break;
          vp.pc_parms[i].pc_key = key;
          vp.pc_parms[i].pc_parm = (uintptr_t)va_arg (ap, void *);
        }
      vp.pc_vaparmscnt = i;

      return INLINE_SYSCALL (priocntlsys, 5, PC_VERSION, ps, cmd, arg, &vp);
    }
  else
    {
      return INLINE_SYSCALL (priocntlsys, 4, PC_VERSION, ps, cmd, arg);
    }
}

long priocntl (idtype_t idtype, id_t id, int cmd, ...)
{
  /* convert idtype/id to procset_t */
  procset_t ps;
  setprocset (&ps, POP_AND, idtype, id, P_ALL, 0);

  va_list ap;
  va_start (ap, cmd);
  return __priocntl_common (&ps, cmd, ap);
}

long priocntlset (procset_t *ps, int cmd, ...)
{
  va_list ap;
  va_start (ap, cmd);
  return __priocntl_common (ps, cmd, ap);
}
