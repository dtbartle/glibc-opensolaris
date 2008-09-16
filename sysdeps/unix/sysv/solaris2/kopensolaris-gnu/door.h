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

#ifndef _DOOR_H
#define _DOOR_H

#include <sys/door.h>
#include <ucred.h>
#include <features.h>

typedef void door_server_func_t (door_info_t *);

__BEGIN_DECLS

int door_create (void (*)(void *, char *, size_t, door_desc_t *, uint_t),
    void *, uint_t);
int door_revoke (int);
int door_info (int, door_info_t *);
int door_call (int, door_arg_t *);
int door_return (char *, size_t, door_desc_t *, uint_t);
int door_cred (door_cred_t *);
int door_ucred (ucred_t **);
int door_bind (int);
int door_unbind (void);
int door_getparam (int, int, size_t *);
int door_setparam (int, int, size_t);
door_server_func_t *door_server_create (door_server_func_t *);

__END_DECLS

#endif /* _DOOR_H */
