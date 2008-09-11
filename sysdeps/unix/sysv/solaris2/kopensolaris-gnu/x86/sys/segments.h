/* Declaration of segments.
   Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_SEGMENTS_H
#define _SYS_SEGMENTS_H 1

#define IDXTOSEL(s)		((s) << 3)
#define SEL_GDT(s, r)	(IDXTOSEL(s) | r)

#define SEL_UPL		3

#define GDT_LWPFS	55
#define GDT_LWPGS	56

#define LWPFS_SEL	SEL_GDT(GDT_LWPFS, SEL_UPL)
#define LWPGS_SEL	SEL_GDT(GDT_LWPGS, SEL_UPL)

#ifdef __i386__

typedef struct user_desc
  {
	uint32_t usd_lolimit:16;
	uint32_t usd_lobase:16;
	uint32_t usd_midbase:8;
	uint32_t usd_type:5;
	uint32_t usd_dpl:2;
	uint32_t usd_p:1;
	uint32_t usd_hilimit:4;
	uint32_t usd_avl:1;
	uint32_t usd_reserved:1;
	uint32_t usd_def32:1;
	uint32_t usd_gran:1;
	uint32_t usd_hibase:8;
  } user_desc_t;

typedef struct system_desc
  {
	uint32_t ssd_lolimit:16;
	uint32_t ssd_lobase:16;
	uint32_t ssd_midbase:8;
	uint32_t ssd_type:4;
	uint32_t ssd_zero:1;
	uint32_t ssd_dpl:2;
	uint32_t ssd_p:1;
	uint32_t ssd_hilimit:4;
	uint32_t ssd_avl:1;
	uint32_t ssd_reserved:2;
	uint32_t ssd_gran:1;
	uint32_t ssd_hibase:8;
 } system_desc_t;

#else

typedef struct user_desc
  {
	uint64_t usd_lolimit:16;
	uint64_t usd_lobase:16;
	uint64_t usd_midbase:8;
	uint64_t usd_type:5;
	uint64_t usd_dpl:2;
	uint64_t usd_p:1;
	uint64_t usd_hilimit:4;
	uint64_t usd_avl:1;
	uint64_t usd_long:1;
	uint64_t usd_def32:1;
	uint64_t usd_gran:1;
	uint64_t usd_hibase:8;
  } user_desc_t;

typedef struct system_desc
  {
	uint64_t ssd_lolimit:16;
	uint64_t ssd_lobase:16;
	uint64_t ssd_midbase:8;
	uint64_t ssd_type:4;
	uint64_t ssd_zero1:1;
	uint64_t ssd_dpl:2;
	uint64_t ssd_p:1;
	uint64_t ssd_hilimit:4;
	uint64_t ssd_avl:1;
	uint64_t ssd_resv1:2;
	uint64_t ssd_gran:1;
	uint64_t ssd_hibase:8;
	uint64_t ssd_hi64base:32;
	uint64_t ssd_resv2:8;
	uint64_t ssd_zero2:5;
	uint64_t ssd_resv3:19;
  } system_desc_t;

#endif /* __i386__ */

#endif /* _SYS_SEGMENTS_H */
