/* Copyright (C) 1993, 1997-2002, 2003, 2004, 2007, 2008
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Per Bothner <bothner@cygnus.com>.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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
   02111-1307 USA.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License.  This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  */

#include <libio/iopopen.c>

/* OpenSolaris's libgen expects two exports: _insert and _delete. It uses
   these to insert/delete from proc_file_chain in its implementation of
   p2open.  */

int _insert (pid_t pid, int fd)
{
  _IO_proc_file *fp = malloc (sizeof (_IO_proc_file));
  if (!fp)
    return -1;

  fp->pid = pid;

  /* The only thing we ever call on fp is _IO_fileno, so this is the only
     field that we need to worry about.  */
  fp->file.file._fileno = fd;

  /* Link into proc_file_chain. */
#ifdef _IO_MTSAFE_IO
  _IO_cleanup_region_start_noarg (unlock);
  _IO_lock_lock (proc_file_chain_lock);
#endif
  fp->next = proc_file_chain;
  proc_file_chain = fp;
#ifdef _IO_MTSAFE_IO
  _IO_lock_unlock (proc_file_chain_lock);
  _IO_cleanup_region_end (0);
#endif

  return 0;
}

pid_t _delete (int fd)
{
  pid_t pid = (pid_t)-1;
#ifdef _IO_MTSAFE_IO
  _IO_cleanup_region_start_noarg (unlock);
  _IO_lock_lock (proc_file_chain_lock);
#endif
  _IO_proc_file **ptr = &proc_file_chain;
  for ( ; *ptr != NULL; ptr = &(*ptr)->next)
    {
      if ((*ptr)->file.file._fileno == fd)
        {
          _IO_proc_file *fp = *ptr;
          pid = fp->pid;
          *ptr = fp->next;
          free (fp);
          break;
        }
    }
#ifdef _IO_MTSAFE_IO
  _IO_lock_unlock (proc_file_chain_lock);
  _IO_cleanup_region_end (0);
#endif

  return pid;
}
