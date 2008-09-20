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

#ifndef _SYS_ATOMIC_H
#define _SYS_ATOMIC_H

#include <features.h>
#include <sys/types.h>
#include <stdint.h>

__BEGIN_DECLS

extern void membar_enter (void);
extern void membar_exit (void);
extern void membar_producer (void);
extern void membar_consumer (void);

extern void atomic_add_8 (volatile uint8_t *, int8_t);
extern void atomic_add_char (volatile unsigned char *, signed char);
extern void atomic_add_16 (volatile uint16_t *, int16_t);
extern void atomic_add_short (volatile unsigned short *, short);
extern void atomic_add_32 (volatile uint32_t *, int32_t);
extern void atomic_add_int (volatile unsigned int *, int);
extern void atomic_add_long (volatile unsigned long *, long);
extern void atomic_add_64 (volatile uint64_t *, int64_t);
extern void atomic_add_ptr (volatile void *, ssize_t);

extern uint8_t atomic_add_8_nv (volatile uint8_t *, int8_t);
extern unsigned char atomic_add_char_nv (volatile unsigned char *, signed char);
extern uint16_t atomic_add_16_nv (volatile uint16_t *, int16_t);
extern unsigned short atomic_add_short_nv (volatile unsigned short *, short);
extern uint32_t atomic_add_32_nv (volatile uint32_t *, int32_t);
extern unsigned int atomic_add_int_nv (volatile unsigned int *, int);
extern unsigned long atomic_add_long_nv (volatile unsigned long *, long);
extern uint64_t atomic_add_64_nv (volatile uint64_t *, int64_t);
extern void * atomic_add_ptr_nv (volatile void *, ssize_t);

extern void atomic_dec_8 (volatile uint8_t *target);
extern void atomic_dec_uchar (volatile unsigned char *target);
extern void atomic_dec_16 (volatile uint16_t *target);
extern void atomic_dec_ushort (volatile unsigned short *target);
extern void atomic_dec_32 (volatile uint32_t *target);
extern void atomic_dec_uint (volatile unsigned int *target);
extern void atomic_dec_ulong (volatile unsigned long *target);
extern void atomic_dec_64 (volatile uint64_t *target);

extern uint8_t atomic_dec_8_nv (volatile uint8_t *target);
extern unsigned char atomic_dec_uchar_nv (volatile unsigned char *target);
extern uint16_t atomic_dec_16_nv (volatile uint16_t *target);
extern unsigned short atomic_dec_ushort_nv (volatile unsigned short *target);
extern uint32_t atomic_dec_32_nv (volatile uint32_t *target);
extern unsigned int atomic_dec_uint_nv (volatile unsigned int *target);
extern unsigned long atomic_dec_ulong_nv (volatile unsigned long *target);
extern uint64_t atomic_dec_64_nv (volatile uint64_t *target);

__END_DECLS

#endif /* _SYS_ATOMIC_H */
