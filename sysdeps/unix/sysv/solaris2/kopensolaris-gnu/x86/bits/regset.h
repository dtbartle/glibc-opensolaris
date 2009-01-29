/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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

#ifndef _BITS_REGSET_H
#define _BITS_REGSET_H

#include <features.h>

typedef struct __fpu
  {
	union
	  {
		struct __fpchip_state
		  {
			__uint32_t __state[27];
			__uint32_t __status;
			__uint32_t __mxcsr;
			__uint32_t __xstatus;
			__uint32_t __pad[2];
			__uint32_t __xmm[4][8];
		  } __fpchip_state;
		struct __fp_emul_space
		  {
			__uint8_t __fp_emul[246];
			__uint8_t __fp_epad[2];
		  } __fp_emul_space;
		__uint32_t __f_fpregs[95];
	  } __fp_reg_set;
  } fpregset_t;

#ifdef __amd64
# define _NGREG		28
#else
# define _NGREG		19
#endif
#define NGREG		_NGREG

typedef int greg_t;

#if defined (_SYSCALL32)
typedef int32_t greg32_t;
typedef int64_t greg64_t;
#endif

typedef greg_t gregset_t[_NGREG];

typedef struct
  {
    gregset_t gregs;
    fpregset_t fpregs;
  } mcontext_t;

#ifdef __USE_MISC

struct fxsave_state
  {
	__uint16_t fx_fcw;
	__uint16_t fx_fsw;
	__uint16_t fx_fctw;
	__uint16_t fx_fop;
#ifdef __amd64__
	__uint64_t fx_rip;
	__uint64_t fx_rdp;
#else
	__uint32_t fx_eip;
	__uint16_t fx_cs;
	__uint16_t __fx_ign0;
	__uint32_t fx_dp;
	__uint16_t fx_ds;
	__uint16_t __fx_ign1;
#endif
	__uint32_t fx_mxcsr;
	__uint32_t fx_mxcsr_mask;
	union
	  {
		__uint16_t fpr_16[5];
		unsigned long long fpr_mmx;
        __uint32_t __fpr_pad[4];
	  } fx_st[8];
#if defined(__amd64)
	upad128_t fx_xmm[16]; /* 128-bit registers */
	upad128_t __fx_ign2[6];
#else
	upad128_t fx_xmm[8];  /* 128-bit registers */
	upad128_t __fx_ign2[14];
#endif
  };

struct fnsave_state
  {
	__uint16_t f_fcw;
	__uint16_t __f_ign0;
	__uint16_t f_fsw;
	__uint16_t __f_ign1;
	__uint16_t f_ftw;
	__uint16_t __f_ign2;
	__uint32_t f_eip;
	__uint16_t f_cs;
	__uint16_t f_fop;
	__uint32_t f_dp;
	__uint16_t f_ds;
	__uint16_t __f_ign3;
	union
	  {
		__uint16_t fpr_16[5];
	  } f_st[8];
  };

typedef struct
  {
	union _kfpu_u
	  {
		struct fxsave_state kfpu_fx;
#ifdef __i386__
		struct fnsave_state kfpu_fn;
#endif
	  } kfpu_u;
	__uint32_t kfpu_status;
	__uint32_t kfpu_xstatus;
  } kfpu_t;

#endif /* __USE_MISC */

#endif /* _BITS_REGSET_H */
