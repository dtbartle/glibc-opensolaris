/* Declarations of zone functions and types.
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

#ifndef _ZONE_H
#define _ZONE_H

#include <features.h>

#include <sys/zone.h>

__BEGIN_DECLS

/* Public interfaces.  */
extern zoneid_t getzoneid (void);
extern zoneid_t getzoneidbyname (const char *);
extern ssize_t getzonenamebyid (zoneid_t, char *, size_t);

/* Private interfaces.  */
extern int zonept (int, zoneid_t);
extern int zone_get_id (const char *, zoneid_t *);
extern zoneid_t zone_create (const char *, const char *,
    const struct priv_set *, const char *, size_t, const char *, size_t, int *,
    int, int, const bslabel_t *, int);
extern int  zone_boot (zoneid_t);
extern int  zone_destroy (zoneid_t);
extern ssize_t  zone_getattr (zoneid_t, int, void *, size_t);
extern int  zone_setattr (zoneid_t, int, void *, size_t);
extern int  zone_enter (zoneid_t);
extern int  zone_list (zoneid_t *, uint_t *);
extern int  zone_shutdown (zoneid_t);
extern int  zone_version (int *);
extern int  zone_add_datalink (zoneid_t, char *);
extern int  zone_remove_datalink (zoneid_t, char *);
extern int  zone_check_datalink (zoneid_t *, char *);
extern int  zone_list_datalink (zoneid_t, int *, char *);

__END_DECLS

#endif /* _ZONE_H */
