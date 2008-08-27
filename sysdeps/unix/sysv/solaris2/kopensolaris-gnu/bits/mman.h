/* Definitions for POSIX memory map interface.  OpenSolaris version.
   Copyright (C) 1997, 2000, 2003, 2005, 2006, 2008
    Free Software Foundation, Inc.
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

#ifndef _SYS_MMAN_H
# error "Never use <bits/mman.h> directly; include <sys/mman.h> instead."
#endif


/* Protections are chosen from these bits, OR'd together.  The
   implementation does not necessarily support PROT_EXEC or PROT_WRITE
   without PROT_READ.  The only guarantees are that no writing will be
   allowed without PROT_WRITE and no access will be allowed for PROT_NONE. */

#define PROT_READ	0x1		/* Page can be read.  */
#define PROT_WRITE	0x2		/* Page can be written.  */
#define PROT_EXEC	0x4		/* Page can be executed.  */
#define PROT_NONE	0x0		/* Page can not be accessed.  */

/* Sharing types (must choose one and only one of these).  */
#define MAP_SHARED	0x01		/* Share changes.  */
#define MAP_PRIVATE	0x02		/* Changes are private.  */
#ifdef __USE_MISC
# define MAP_TYPE	0x0f		/* Mask for type of mapping.  */
#endif

/* Other flags.  */
#define MAP_FIXED	0x10		/* Interpret addr exactly.  */
#ifdef __USE_MISC
# define MAP_FILE	0
# define MAP_ANONYMOUS	0x100		/* Don't use a file.  */
# define MAP_ANON	MAP_ANONYMOUS
#endif

/* These are OpenSolaris-specific.  */
#ifdef __USE_MISC
# define MAP_NORESERVE	0x40		/* Don't check for reservations.  */
# define MAP_ALIGN	0x200		/* Address specifies alignment.  */
# define MAP_TEXT	0x200		/* Map code segment.  */
# define MAP_INITDATA	0x800		/* Map data segment.  */
# define MAP_RENAME	0x20		/* Rename private pages to file.  */
# define _MAP_NEW	0x80000000	/* Never use this.  */
#endif

/* Flags to `msync'.  */
#define MS_ASYNC	1		/* Sync memory asynchronously.  */
#define MS_SYNC		4		/* Synchronous memory sync.  */
#define MS_INVALIDATE	2		/* Invalidate the caches.  */

/* These are OpenSolaris-specific.  */
#ifdef __USE_MISC

/* mctl functions */
# define MC_SYNC	1
# define MC_LOCK	2
# define MC_UNLOCK	3
# define MC_ADVISE	4
# define MC_LOCKAS	5
# define MC_UNLOCKAS	6
# define MC_HAT_ADVISE	7

/* MC_HAT_ADVISE arg */
# define MHA_MAPSIZE_VA	0x1
# define MHA_MAPSIZE_BSSBRK	0x2
# define MHA_MAPSIZE_STACK	0x3

# include <sys/types.h>

# define MISYS_MEMINFO	0x0

typedef struct meminfo
  {
    const uint64_t *mi_inaddr;
    const unsigned int *mi_info_req;
    uint64_t *mi_outdata;
    unsigned int *mi_validity;
    int mi_info_count;
  } meminfo_t;

/* info_req field */
# define MEMINFO_SHIFT		16
# define MEMINFO_MASK		(0xFF << MEMINFO_SHIFT)
# define MEMINFO_VPHYSICAL	(0x01 << MEMINFO_SHIFT)
# define MEMINFO_VLGRP		(0x02 << MEMINFO_SHIFT)
# define MEMINFO_VPAGESIZE	(0x03 << MEMINFO_SHIFT)
# define MEMINFO_VREPLCNT	(0x04 << MEMINFO_SHIFT)
# define MEMINFO_VREPL		(0x05 << MEMINFO_SHIFT)
# define MEMINFO_VREPL_LGRP	(0x06 << MEMINFO_SHIFT)
# define MEMINFO_PLGRP		(0x07 << MEMINFO_SHIFT)

/* max address count for meminfo */
# define MAX_MEMINFO_CNT	256

/* max request types */
# define MAX_MEMINFO_REQ	31

#endif /* __USE_MISC */

/* Flags for `mlockall'.  */
#define MCL_CURRENT	1		/* Lock all currently mapped pages.  */
#define MCL_FUTURE	2		/* Lock all additions to address
					   space.  */

/* Flags for `mremap'.  */
#ifdef __USE_GNU
# define MREMAP_MAYMOVE	1
# define MREMAP_FIXED	2
#endif

/* Advice to `madvise'.  */
#ifdef __USE_MISC
# define MADV_NORMAL	 0	/* No further special treatment.  */
# define MADV_RANDOM	 1	/* Expect random page references.  */
# define MADV_SEQUENTIAL 2	/* Expect sequential page references.  */
# define MADV_WILLNEED	 3	/* Will need these pages.  */
# define MADV_DONTNEED	 4	/* Don't need these pages.  */
# define MADV_REMOVE	 9	/* Remove these pages and resources.  */
# define MADV_DONTFORK	 10	/* Do not inherit across fork.  */
# define MADV_DOFORK	 11	/* Do inherit across fork.  */
#endif

/* These are OpenSolaris-specific.  */
#ifdef __USE_MISC
# define MADV_FREE				5
# define MADV_ACCESS_DEFAULT	6
# define MADV_ACCESS_LWP		7
# define MADV_ACCESS_MANY		8
#endif

/* The POSIX people had to invent similar names for the same things.  */
#ifdef __USE_XOPEN2K
# define POSIX_MADV_NORMAL	0 /* No further special treatment.  */
# define POSIX_MADV_RANDOM	1 /* Expect random page references.  */
# define POSIX_MADV_SEQUENTIAL	2 /* Expect sequential page references.  */
# define POSIX_MADV_WILLNEED	3 /* Will need these pages.  */
# define POSIX_MADV_DONTNEED	4 /* Don't need these pages.  */
#endif

struct memcntl_mha
  {
	unsigned int mha_cmd;
    unsigned int mha_flags;
    size_t mha_pagesize;
  };

__BEGIN_DECLS

#if defined __USE_MISC
extern int getpagesizes (size_t *__pagesize, int __nelem);
extern int getpagesizes2 (size_t *__pagesize, int __nelem);
extern int meminfo (const uint64_t *__inaddr, int,
    const unsigned int *__addr_count, int __info_req, uint64_t *__info_count,
    unsigned int *__outdata);
extern int memcntl (__caddr_t addr, size_t len, int cmd, __caddr_t arg,
    int attr, int mask);

#endif

__END_DECLS
