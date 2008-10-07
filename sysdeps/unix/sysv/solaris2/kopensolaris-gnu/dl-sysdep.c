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

#include <link.h>
#include <sys/mman.h>
#include <ldsodefs.h>

#define DL_SYSDEP_INIT	exec_last_load (phdr, phnum)

static inline void exec_last_load (const ElfW(Phdr) *phdr, ElfW(Word) phnum)
{
  /* Check if the last PT_LOAD segment is executable.  */
  GLRO(dl_malloc_prot_exec) = 0;
  for (uint_fast16_t i = 0; i < phnum; ++i)
    if (phdr[i].p_type == PT_LOAD)
      GLRO(dl_malloc_prot_exec) = (phdr[i].p_flags & PF_X) ? PROT_EXEC : 0;
}

#include <elf/dl-sysdep.c>
