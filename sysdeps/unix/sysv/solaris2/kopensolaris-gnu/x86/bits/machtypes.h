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

#ifndef _BITS_MACHTYPES_H
#define _BITS_MACHTYPES_H

#include <features.h>

#ifdef __USE_MISC

#define REG_LABEL_PC    0
#define REG_LABEL_SP    1
#define REG_LABEL_BP    2
#ifdef __i386__
# define REG_LABEL_EBX	3
# define REG_LABEL_ESI	4
# define REG_LABEL_EDI	5
# define REG_LABEL_MAX	6
#else
# define REG_LABEL_RBX	3
# define REG_LABEL_R12	4
# define REG_LABEL_R13	5
# define REG_LABEL_R14	6
# define REG_LABEL_R15	7
# define REG_LABEL_MAX	8
#endif

typedef struct _label_t
  {
	long val[REG_LABEL_MAX];
  } label_t;

#endif /* __USE_MISC */

typedef unsigned char	lock_t;

#endif /* _BITS_MACHTYPES_H */
