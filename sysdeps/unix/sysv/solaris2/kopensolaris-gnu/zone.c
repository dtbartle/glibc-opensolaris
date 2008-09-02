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

#include <inline-syscall.h>
#include "priv_priv.h"
#include <zone.h>
#include <dlfcn.h>

DECLARE_INLINE_SYSCALL (zoneid_t, zone_create, zone_def *def);
DECLARE_INLINE_SYSCALL (zoneid_t, zone_lookup, const char *name);


zoneid_t getzoneid (void)
{
  return INLINE_SYSCALL (zone_lookup, 1, NULL);
}


zoneid_t getzoneidbyname (const char *name)
{
  return INLINE_SYSCALL (zone_lookup, 1, name);
}


ssize_t getzonenamebyid (zoneid_t id, char *buf, size_t buflen)
{
  return zone_getattr (id, ZONE_ATTR_NAME, buf, buflen);
}


zoneid_t zone_create (const char *name, const char *root,
      const struct priv_set *privs, const char *rctlbuf, size_t rctlbufsz,
      const char *zfsbuf, size_t zfsbufsz, int *extended_error, int match,
      int doi, const bslabel_t *label, int flags)
{
  priv_impl_info_t *info;
  int res = __getprivimplinfo_cached (&info);
  if (res != 0)
    return -1;

  zone_def def;
  def.zone_name = name;
  def.zone_root = root;
  def.zone_privs = privs;
  def.zone_privssz = info->priv_setsize * sizeof (priv_chunk_t);
  def.rctlbuf = rctlbuf;
  def.rctlbufsz = rctlbufsz;
  def.extended_error = extended_error;
  def.zfsbuf = zfsbuf;
  def.zfsbufsz = zfsbufsz;
  def.match = match;
  def.doi = doi;
  def.label = label;
  def.flags = flags;

  return INLINE_SYSCALL (zone_create, 1, &def);
}


int (*_zone_get_id)(const char *, zoneid_t *);

int zone_get_id (const char *str, zoneid_t *idp)
{
  /* libzonecfg.so.1 has the real function.  */
  void *lzc = __libc_dlopen ("libzonecfg.so.1");
  if (lzc)
    {
      _zone_get_id = __libc_dlsym (lzc, "zone_get_id");
      if (_zone_get_id)
        return _zone_get_id (str, idp);
    }

  return ENOSYS;
}
