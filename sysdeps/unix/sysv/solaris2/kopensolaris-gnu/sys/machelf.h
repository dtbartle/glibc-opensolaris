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

#ifndef _SYS_MACHELF_H
#define _SYS_MACHELF_H

#include <sys/isa_defs.h>
#include <sys/elf.h>
#include <link.h>

#if defined (_ELF64) && !defined (_ELF32_COMPAT)

typedef Elf64_Xword	Xword;
typedef Elf64_Lword	Lword;
typedef Elf64_Sxword	Sxword;
typedef Elf64_Word	Word;
typedef Elf64_Sword	Sword;
typedef Elf64_Half	Half;
typedef Elf64_Addr	Addr;
typedef Elf64_Off	Off;
typedef uchar_t		Byte;

typedef Elf64_Ehdr	Ehdr;
typedef Elf64_Shdr	Shdr;
typedef Elf64_Sym	Sym;
typedef Elf64_Syminfo	Syminfo;
typedef Elf64_Rela	Rela;
typedef Elf64_Rel	Rel;
typedef Elf64_Nhdr	Nhdr;
typedef Elf64_Phdr	Phdr;
typedef Elf64_Dyn	Dyn;
typedef Elf64_Boot	Boot;
typedef Elf64_Verdef	Verdef;
typedef Elf64_Verdaux	Verdaux;
typedef Elf64_Verneed	Verneed;
typedef Elf64_Vernaux	Vernaux;
typedef Elf64_Versym	Versym;
typedef Elf64_Move	Move;
typedef Elf64_Cap	Cap;

#else

typedef Elf32_Word	Xword;
typedef Elf32_Lword	Lword;
typedef Elf32_Sword	Sxword;
typedef Elf32_Word	Word;
typedef Elf32_Sword	Sword;
typedef Elf32_Half	Half;
typedef Elf32_Addr	Addr;
typedef Elf32_Off	Off;

typedef Elf32_Ehdr	Ehdr;
typedef Elf32_Shdr	Shdr;
typedef Elf32_Sym	Sym;
typedef Elf32_Syminfo	Syminfo;
typedef Elf32_Rela	Rela;
typedef Elf32_Rel	Rel;
typedef Elf32_Nhdr	Nhdr;
typedef Elf32_Phdr	Phdr;
typedef Elf32_Dyn	Dyn;
typedef Elf32_Boot	Boot;
typedef Elf32_Verdef	Verdef;
typedef Elf32_Verdaux	Verdaux;
typedef Elf32_Verneed	Verneed;
typedef Elf32_Vernaux	Vernaux;
typedef Elf32_Versym	Versym;
typedef Elf32_Move	Move;
typedef Elf32_Cap	Cap;

#endif /* _ELF64 */

#endif /* _SYS_MACHELF_H */
