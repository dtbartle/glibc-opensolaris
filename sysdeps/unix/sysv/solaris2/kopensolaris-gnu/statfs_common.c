/* statfs -- Return information about the filesystem on which FILE resides.
   Copyright (C) 1996, 1997, 2002, 2009 Free Software Foundation, Inc.
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

#include <errno.h>
#include <sys/statfs.h>
#include <sys/statvfs.h>
#include <sys/fstyp.h>
#include <stddef.h>

/* Return information about the filesystem on which FILE resides.  */
int
STATFS_FUNC (STATFS_ARG file, STATFS_STRUCT *buf)
{
  STATVFS_STRUCT vbuf;
  int res = STATVFS_FUNC (file, &vbuf);
  if (res != 0)
    return -1;

  int fsid = sysfs (GETFSIND, vbuf.f_basetype);
  if (fsid == -1)
    return -1;

  buf->f_type = 0;
  buf->f_bsize = vbuf.f_bsize;
  buf->f_blocks = vbuf.f_blocks;
  buf->f_bfree = vbuf.f_bfree;
  buf->f_bavail = vbuf.f_bavail;
  buf->f_files = vbuf.f_files;
  buf->f_ffree = vbuf.f_ffree;
  buf->f_fsid = fsid;
  buf->f_namelen = vbuf.f_namemax;
  buf->f_frsize = vbuf.f_frsize;
  memset (&buf->f_spare, 0, sizeof (buf->f_spare));

  return 0;
}
