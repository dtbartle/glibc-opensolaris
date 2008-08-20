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

#include <sys/types.h>
#include <sys/regset.h>
#include <sys/stack.h>
#include <ucontext.h>
#include <stdarg.h>
#include <assert.h>

void
__restorecontext (void)
{
  ucontext_t uc;
  assert (getcontext (&uc) == 0);
  assert (setcontext (uc.uc_link) == 0);
}

void
makecontext (ucontext_t *ucp, void (*func) (void), int argc, ...)
{
  /* setup the stack (note that it grows down) */
  void *stack_addr = ucp->uc_stack.ss_sp + ucp->uc_stack.ss_size -
    (argc + 1) * sizeof(uint32_t);
  uint32_t *stack_ptr = (uint32_t *)((uint32_t)stack_addr &
    ~(STACK_ALIGN - 1));
  ucp->uc_mcontext.gregs[UESP] = (greg_t)stack_ptr;
  *stack_ptr++ = __restorecontext; /* return addr */
  va_list ap;
  va_start (ap, argc);
  while (argc--)
    *stack_ptr++ = (uint32_t)va_arg (ap, char *); /* arg */
  ucp->uc_mcontext.gregs[EIP] = (greg_t)func;
}
