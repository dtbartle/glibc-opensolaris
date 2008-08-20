/* Declarations of fltset_t.
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

#ifndef _SYS_FAULT_H
#define _SYS_FAULT_H

typedef struct
{
    unsigned int word[4];
} fltset_t;

#define FLTILL		1
#define FLTPRIV		2
#define FLTBPT		3
#define FLTTRACE	4
#define FLTACCESS	5
#define FLTBOUNDS	6
#define FLTIOVF		7
#define FLTIZDIV	8
#define FLTFPE		9
#define FLTSTACK	10
#define FLTPAGE		11
#define FLTWATCH	12
#define FLTCPCOVF	13

#endif /* _SYS_FAULT_H */
