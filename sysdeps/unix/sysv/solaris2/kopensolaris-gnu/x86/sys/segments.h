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

#endif /* _SYS_SEGMENTS_H */
