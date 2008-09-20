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

#include <sys/atomic.h>
#include <stdint.h>

/* This pulls in include/atomic.h rather than sysdeps/.../atomic.h.  */
#include <atomic.h>

/* membar_* */

void membar_enter (void)
{
  atomic_full_barrier ();
}

void membar_exit (void)
{
  atomic_full_barrier ();
}

void membar_producer (void)
{
  atomic_write_barrier ();
}

void membar_consumer (void)
{
  atomic_read_barrier ();
}

/* atomic_add_* */

void atomic_add_8 (volatile uint8_t *target, int8_t delta)
{
  atomic_add (target, delta);
}

void atomic_add_char (volatile unsigned char *target, signed char delta)
{
  atomic_add (target, delta);
}

void atomic_add_16 (volatile uint16_t *target, int16_t delta)
{
  atomic_add (target, delta);
}

void atomic_add_short (volatile unsigned short *target, short delta)
{
  atomic_add (target, delta);
}

void atomic_add_32 (volatile uint32_t *target, int32_t delta)
{
  atomic_add (target, delta);
}

void atomic_add_int (volatile unsigned int *target, int delta)
{
  atomic_add (target, delta);
}

void atomic_add_long (volatile unsigned long *target, long delta)
{
  atomic_add (target, delta);
}

void atomic_add_64 (volatile uint64_t *target, int64_t delta)
{
  atomic_add (target, delta);
}

void atomic_add_ptr (volatile void *target, ssize_t delta)
{
  atomic_add ((char **)target, delta);
}

uint8_t atomic_add_8_nv (volatile uint8_t *target, int8_t delta)
{
  return atomic_exchange_and_add (target, delta);
}

unsigned char atomic_add_char_nv (volatile unsigned char *target, signed char delta)
{
  return atomic_exchange_and_add (target, delta);
}

uint16_t atomic_add_16_nv (volatile uint16_t *target, int16_t delta)
{
  return atomic_exchange_and_add (target, delta);
}

unsigned short atomic_add_short_nv (volatile unsigned short *target, short delta)
{
  return atomic_exchange_and_add (target, delta);
}

uint32_t atomic_add_32_nv (volatile uint32_t *target, int32_t delta)
{
  return atomic_exchange_and_add (target, delta);
}

unsigned int atomic_add_int_nv (volatile unsigned int *target, int delta)
{
  return atomic_exchange_and_add (target, delta);
}

unsigned long atomic_add_long_nv (volatile unsigned long *target, long delta)
{
  return atomic_exchange_and_add (target, delta);
}

uint64_t atomic_add_64_nv (volatile uint64_t *target, int64_t delta)
{
  return atomic_exchange_and_add (target, delta);
}

void *atomic_add_ptr_nv (volatile void *target, ssize_t delta)
{
  return atomic_exchange_and_add ((char **)target, delta);
}

/* atomic_dec_* */

void atomic_dec_8 (volatile uint8_t *target)
{
  atomic_decrement (target);
}

void atomic_dec_uchar (volatile unsigned char *target)
{
  atomic_decrement (target);
}

void atomic_dec_16 (volatile uint16_t *target)
{
  atomic_decrement (target);
}

void atomic_dec_ushort (volatile unsigned short *target)
{
  atomic_decrement (target);
}

void atomic_dec_32 (volatile uint32_t *target)
{
  atomic_decrement (target);
}

void atomic_dec_uint (volatile unsigned int *target)
{
  atomic_decrement (target);
}

void atomic_dec_ulong (volatile unsigned long *target)
{
  atomic_decrement (target);
}

void atomic_dec_64 (volatile uint64_t *target)
{
  atomic_decrement (target);
}

uint8_t atomic_dec_8_nv (volatile uint8_t *target)
{
  return atomic_decrement_val (target);
}

unsigned char atomic_dec_uchar_nv (volatile unsigned char *target)
{
  return atomic_decrement_val (target);
}

uint16_t atomic_dec_16_nv (volatile uint16_t *target)
{
  return atomic_decrement_val (target);
}

unsigned short atomic_dec_ushort_nv (volatile unsigned short *target)
{
  return atomic_decrement_val (target);
}

uint32_t atomic_dec_32_nv (volatile uint32_t *target)
{
  return atomic_decrement_val (target);
}

unsigned int atomic_dec_uint_nv (volatile unsigned int *target)
{
  return atomic_decrement_val (target);
}

unsigned long atomic_dec_ulong_nv (volatile unsigned long *target)
{
  return atomic_decrement_val (target);
}

uint64_t atomic_dec_64_nv (volatile uint64_t *target)
{
  return atomic_decrement_val (target);
}
