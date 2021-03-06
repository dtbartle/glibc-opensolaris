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

#define LWPGS_SEL	0x01C3

static int
create_thread_arch (ucontext_t *ctx, struct pthread *pd,
           const struct pthread_attr *attr, STACK_VARIABLES_PARMS)
{
  /* Clone the segment registers (except gs - see below).  */
  ucontext_t _ctx;
  _ctx.uc_flags = UC_CPU;
  if (getcontext(&_ctx) != 0)
    return errno;
  ctx->uc_mcontext.gregs[CS] = _ctx.uc_mcontext.gregs[CS];
  ctx->uc_mcontext.gregs[DS] = _ctx.uc_mcontext.gregs[DS];
  ctx->uc_mcontext.gregs[ES] = _ctx.uc_mcontext.gregs[ES];
  ctx->uc_mcontext.gregs[FS] = _ctx.uc_mcontext.gregs[FS];
  ctx->uc_mcontext.gregs[SS] = _ctx.uc_mcontext.gregs[SS];

  /* Setup the stack (note that it grows down).  */
  uint32_t *stack_ptr = (uint32_t *)((uintptr_t)((uint32_t *)stackaddr - 1) &
    ~(STACK_ALIGN - 1)) + 1;
  *--stack_ptr = (uint32_t)pd; /* arg 1 */
  *--stack_ptr = 0; /* return addr (thread_start never returns) */
  ctx->uc_mcontext.gregs[UESP] = (greg_t)stack_ptr;
  ctx->uc_mcontext.gregs[EBP] = 0;
  ctx->uc_mcontext.gregs[EIP] = (greg_t)start_thread;
  ctx->uc_flags |= UC_CPU;

  /* This is a hack to get the kernel to set gs for us.  */
  ctx->uc_mcontext.gregs[GS] = (greg_t)LWPGS_SEL;
  ctx->uc_mcontext.gregs[ESP] = (greg_t)pd;

  return 0;
}
