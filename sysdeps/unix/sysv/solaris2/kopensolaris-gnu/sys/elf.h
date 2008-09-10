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

#ifndef _SYS_ELF_H
#define _SYS_ELF_H

#include <elf.h>

#define PF_SUNW_FAILURE	0x00100000

#define PN_XNUM	0xFFFF

#define	SHT_SUNW_symsort	0x6FFFFFF1
#define	SHT_SUNW_tlssort	0x6FFFFFF2
#define	SHT_SUNW_LDYNSYM	0x6FFFFFF3
#define	SHT_SUNW_dof		0x6FFFFFF4
#define	SHT_SUNW_cap		0x6FFFFFF5

/* TODO: these collide with GNU definitions.  */
#if 0
#define	SHT_SUNW_SIGNATURE	0x6FFFFFF6
#define	SHT_SUNW_ANNOTATE	0x6FFFFFF7
#define	SHT_SUNW_DEBUGSTR	0x6FFFFFF8
#define	SHT_SUNW_DEBUG		0x6FFFFFF9
#endif

#define	SHT_SUNW_verdef		SHT_GNU_verdef
#define	SHT_SUNW_verneed	SHT_GNU_verneed
#define	SHT_SUNW_versym		SHT_GNU_versym

typedef struct
  {
	Elf32_Word c_tag;
	union
	  {
		Elf32_Word c_val;
		Elf32_Addr c_ptr;
	  } c_un;
  } Elf32_Cap;

typedef struct
  {
	Elf64_Xword c_tag;
	union
	  {
		Elf64_Xword c_val;
		Elf64_Addr c_ptr;
	  } c_un;
  } Elf64_Cap;

#endif /* _SYS_ELF_H */
