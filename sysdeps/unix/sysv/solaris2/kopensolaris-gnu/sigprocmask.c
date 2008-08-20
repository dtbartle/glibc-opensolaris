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
#include <signal.h>
#include <memory.h>

DECLARE_INLINE_SYSCALL (int64_t, lwp_sigmask, int how, unsigned int bits0,
    unsigned int bits1);

int
__sigprocmask (how, set, oset)
     int how;
     const sigset_t *set;
     sigset_t *oset;
{
  /* we don't want people blocking SIGCANCEL */
  sigset_t tmpset;
  if (set != NULL && __builtin_expect (__sigismember(set, SIGCANCEL), 0))
    {
      memcpy (&tmpset, set, sizeof(sigset_t));
      __sigdelset (&tmpset, SIGCANCEL);
      set = &tmpset;
    }

  /* we need to convert from sigset_t to two bit fields */
  unsigned int bits0, bits1;
  if (set)
    {
      bits0 = set->__sigbits[0];
      bits1 = set->__sigbits[1];
    }
  else
    {
        bits0 = bits1 = how = 0;
    }

  /* we call lwp_sigmask to set the per-thread sigmask */
  rval_t result;
  result.rval64 = INLINE_SYSCALL (lwp_sigmask, 3, how, bits0, bits1);

  /* now we need to convert from two bit fields to sigset_t */
  if (oset)
    {
      oset->__sigbits[0] = result.rval1;
      oset->__sigbits[1] = result.rval2;
      oset->__sigbits[2] = oset->__sigbits[3] = 0;
    }

  return 0;
}

weak_alias (__sigprocmask, sigprocmask)
