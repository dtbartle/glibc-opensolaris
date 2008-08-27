/* Declarations of privilege functions and types.
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

#ifndef _SYS_DOOR_H
#define _SYS_DOOR_H

#include <sys/types.h>

typedef unsigned long long door_ptr_t;
typedef unsigned int door_attr_t;
typedef unsigned long long door_id_t;

typedef struct door_info
  {
	pid_t di_target;
	door_ptr_t di_proc;
	door_ptr_t di_data;
	door_attr_t di_attributes;
	door_id_t di_uniquifier;
	int di_resv[4];
  } door_info_t;

#endif /* _SYS_DOOR_H */
