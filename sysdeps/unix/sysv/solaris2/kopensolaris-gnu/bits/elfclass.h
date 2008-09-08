/* This file specifies the native word size of the machine, which indicates
   the ELF file class used for executables and shared objects on this
   machine.  */

#ifndef _LINK_H
# error "Never use <bits/elfclass.h> directly; include <link.h> instead."
#endif

#include <bits/wordsize.h>

#define __ELF_NATIVE_CLASS __WORDSIZE

/* The entries in the .hash table always have a size of 32 bits.  */
typedef uint32_t Elf_Symndx;

typedef struct
  {
	Elf32_Sword eb_tag;
	union
	  {
		Elf32_Word eb_val;
		Elf32_Addr eb_ptr;
		Elf32_Off eb_off;
	  } eb_un;
  } Elf32_Boot;

typedef struct
  {
	Elf64_Xword eb_tag;
	union
	  {
		Elf64_Xword eb_val;
		Elf64_Addr eb_ptr;
		Elf64_Off eb_off;
	  } eb_un;
  } Elf64_Boot;

typedef uint64_t	Elf32_Lword;
typedef uint64_t	Elf64_Lword;

#define DT_SUNW_AUXILIARY	0x6000000d
#define DT_SUNW_RTLDINF		0x6000000e
#define DT_SUNW_FILTER		0x6000000f
#define DT_SUNW_CAP		0x60000010
#define DT_SUNW_SYMTAB		0x60000011
#define DT_SUNW_SYMSZ		0x60000012
#define DT_SUNW_ENCODING	0x60000013
#define DT_SUNW_SORTENT		0x60000013
#define DT_SUNW_SYMSORT		0x60000014
#define DT_SUNW_SYMSORTSZ	0x60000015
#define DT_SUNW_TLSSORT		0x60000016
#define DT_SUNW_TLSSORTSZ	0x60000017
#define DT_SUNW_STRPAD		0x60000019
#define DT_SUNW_LDMACH		0x6000001b

#define NT_PRSTATUS	1
#define NT_PRFPREG	2
#define NT_PRPSINFO	3
#define NT_PRXREG	4
#define NT_PLATFORM	5
#define NT_AUXV		6
#define NT_GWINDOWS	7
#define NT_ASRS		8
#define NT_LDT		9
#define NT_PSTATUS	10
#define NT_PSINFO	13
#define NT_PRCRED	14
#define NT_UTSNAME	15
#define NT_LWPSTATUS	16
#define NT_LWPSINFO	17
#define NT_PRPRIV	18
#define NT_PRPRIVINFO	19
#define NT_CONTENT	20
#define NT_ZONENAME	21
#define NT_NUM		21
