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

#include <rtld_db.h>
#include <rtld_dbP.h>
#include <sys/elf.h>
#include <proc_service.h>

/* TODO: This function needs to handle both 32-bit and 64-bit elf files.  */

#pragma weak ps_pread

/* Docs: http://docs.sun.com/app/docs/doc/817-1984/chapter6-43405  */

/* This function is really just a helper, since it doesn't actually use
   any internal ld.so data.  */

rd_err_e rd_get_dyns (rd_agent_t *rdap, psaddr_t addr, void **dynpp,
      size_t *dynpp_sz)
{
  ps_err_e res;

  /* Read Ehdr.  */
  Elf32_Ehdr ehdr;
  res = ps_pread (rdap->rd_php, addr, &ehdr, sizeof (ehdr));
  if (res != PS_OK)
    return RD_ERR;

  /* Determine number of Phdr's.  */
  int nphdr;
  if (ehdr.e_phnum == PN_XNUM)
    {
      if (ehdr.e_shoff == 0)
        return RD_ERR;

      /* Read Shdr.  */
      Elf32_Shdr shdr;
      res = ps_pread (rdap->rd_php, addr + ehdr.e_shoff, &shdr, sizeof (shdr));
      if (res != PS_OK)
        return RD_ERR;

      nphdr = shdr.sh_info;
    }
  else
    {
      nphdr = ehdr.e_phnum;
    }
  if (nphdr == 0)
    return RD_ERR;

  /* Scan all the Phdr's looking for DT_DYNAMIC.  */
  for (int i = 0; i < nphdr; i++)
    {
      Elf32_Phdr phdr, *phdr_ptr = addr + ehdr.e_phoff + (ehdr.e_phentsize * i);
      res = ps_pread (rdap->rd_php, phdr_ptr, &phdr, sizeof (phdr));
      if (res != PS_OK)
        return RD_ERR;

      if (phdr.p_type == PT_DYNAMIC)
        {
          /* Allocate some memory and read in the dynamic data.  */
          void *dynp = malloc (phdr.p_filesz);
          if (dynp == NULL)
            return RD_ERR;
          res = ps_pread (rdap->rd_php, phdr.p_vaddr, dynp, phdr.p_filesz);
          if (res != RD_OK)
            {
              free (dynp);
              return RD_ERR;
            }
          *dynpp = dynp;
          if (dynpp_sz)
            *dynpp_sz = phdr.p_filesz;

          return RD_OK;
        }
    }

  /* We didn't find PT_DYNAMIC.  */
  return RD_DBERR;
}
