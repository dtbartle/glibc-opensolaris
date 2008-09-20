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

#include <sys/types.h>
#include <errno.h>
#include <mkdevP.h>

major_t __major (const int version, const dev_t devnum)
{
  if ((version != OLDDEV && version != NEWDEV) || devnum == NODEV)
    {
      __set_errno (EINVAL);
      return NODEV;
    }

  if (version == OLDDEV)
    {
      if ((devnum >> ONBITSMINOR) > OMAXMAJ)
        {
          __set_errno (EINVAL);
          return NODEV;
        }

        return devnum >> ONBITSMINOR;
    }
  else /* NEWDEV */
    {
      if ((devnum >> NBITSMINOR) > MAXMAJ)
        {
          __set_errno (EINVAL);
          return NODEV;
        }

        return devnum >> NBITSMINOR;
    }
}


minor_t __minor (const int version, const dev_t devnum)
{
  if ((version != OLDDEV && version != NEWDEV) || devnum == NODEV)
    {
      __set_errno (EINVAL);
      return NODEV;
    }

  if (version == OLDDEV)
    return devnum & OMAXMIN;
  else /* NEWDEV */
    return devnum & MAXMIN;
}


dev_t __makedev (const int version, const major_t majdev, const minor_t mindev)
{
  if (version != OLDDEV && version != NEWDEV)
    {
      __set_errno (EINVAL);
      return NODEV;
    }

  if (version == OLDDEV)
    {
      if (majdev > OMAXMAJ || mindev > OMAXMIN)
        {
          __set_errno (EINVAL);
          return NODEV;
        }
      return (majdev << ONBITSMINOR) | mindev;
    }
  else /* NEWDEV */
    {
      if (majdev > MAXMAJ || mindev > MAXMIN)
        {
          __set_errno (EINVAL);
          return NODEV;
        }

      dev_t devnum = (majdev << NBITSMINOR) | mindev;
      if (devnum == NODEV)
        __set_errno (EINVAL);
      return devnum;
    }
}
