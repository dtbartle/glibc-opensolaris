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

#ifndef _SYS_AUXV_H
#define _SYS_AUXV_H

#ifndef __ASSEMBLER__
typedef struct
  {
	int a_type;
	union
	  {
		long a_val;
		void *a_ptr;
		void (*a_fcn)(void);
	} a_un;
  } auxv_t;
#endif

#define AT_SUN_IFLUSH		2010
#define AT_SUN_CPU		2011

#define AT_SUN_EXECNAME		2014
#define AT_SUN_MMU		2015
#define AT_SUN_LDDATA		2016
#define AT_SUN_AUXFLAGS		2017
#define AT_SUN_EMULATOR		2018
#define AT_SUN_BRANDNAME	2019
#define AT_SUN_BRAND_AUX1	2020
#define AT_SUN_BRAND_AUX2	2021
#define AT_SUN_BRAND_AUX3	2022

/* Passed in AT_SUN_AUXFLAGS.  */
#define AF_SUN_SETUGID		0x01
#define AF_SUN_HWCAPVERIFY	0x02
#define AF_SUN_NOPLM		0x04

#endif /* _SYS_AUXV_H */
