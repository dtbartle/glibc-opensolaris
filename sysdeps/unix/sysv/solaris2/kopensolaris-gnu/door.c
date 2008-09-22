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

#include <sysdep-cancel.h>
#include <inline-syscall.h>
#include <doorP.h>
#include <ucredP.h>
#include <libio/libioP.h>
#include <atomic.h>
#include <thread.h>
#include <dlfcn.h>
#include <alloca.h>

static pid_t __door_private_pid, __door_unref_pid;
static void * door_server_create_default (door_info_t *);
static door_server_func_t *door_server_create_proc = &door_server_create_default;
static int (*thr_create_ptr) (void *, size_t, void * (*)(void *), void *,
    long, thread_t *);

/* Arguments are passed normally with the 6th argument always the subcode.  */

DECLARE_INLINE_SYSCALL (int, door, long, long, long, long, long, long subcode);


int door_info (int d, door_info_t *info)
{
  return INLINE_SYSCALL (door, 6, d, (long)info, 0, 0, 0, SYS_SUB_door_info);
}


int door_bind (int d)
{
  return INLINE_SYSCALL (door, 6, d, 0, 0, 0, 0, SYS_SUB_door_bind);
}


int door_unbind (void)
{
  return INLINE_SYSCALL (door, 6, 0, 0, 0, 0, 0, SYS_SUB_door_unbind);
}


int door_revoke (int d)
{
  return INLINE_SYSCALL (door, 6, d, 0, 0, 0, 0, SYS_SUB_door_revoke);
}


int door_getparam(int d, int param, size_t *out)
{
  return INLINE_SYSCALL (door, 6, d, param, (long)out, 0, 0,
    SYS_SUB_door_getparam);
}


int door_setparam (int d, int param, size_t val)
{
  return INLINE_SYSCALL (door, 6, d, param, val, 0, 0, SYS_SUB_door_setparam);
}


int door_call (int d, door_arg_t* params)
{
  if (SINGLE_THREAD_P)
    return INLINE_SYSCALL (door, 6, d, (long)params, 0, 0, 0,
      SYS_SUB_door_call);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int res = INLINE_SYSCALL (door, 6, d, (long)params, 0, 0, 0,
    SYS_SUB_door_call);

  LIBC_CANCEL_RESET (oldtype);

  return res;
}


int door_return (char *data_ptr, size_t data_size, door_desc_t *desc_ptr,
     uint_t num_desc)
{
  ucontext_t uc;
  if (getcontext (&uc) != 0)
    return -1;

  door_return_desc_t drd;
  drd.desc_ptr = desc_ptr;
  drd.desc_num = num_desc;

  return INLINE_SYSCALL (door, 6, (long)data_ptr, data_size, (long)&drd,
      (long)uc.uc_stack.ss_sp, uc.uc_stack.ss_size, SYS_SUB_door_return);
}


door_server_func_t * door_server_create (door_server_func_t *create_proc)
{
  while (1)
    {
      door_server_func_t *cur_proc = door_server_create_proc;
      door_server_func_t *old_proc = atomic_compare_and_exchange_val_acq (
          &door_server_create_proc, create_proc, cur_proc);
      if (old_proc == cur_proc)
        return old_proc;
    }
}


static void * door_create_default_proc (void *arg)
{
  pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, NULL);
  door_return (NULL, 0, NULL, 0);

  return arg;
}


static void * door_server_create_default (door_info_t *info)
{
  if (!thr_create_ptr)
    {
      void *libpthread = __libc_dlopen ("libpthread.so");
      if (!libpthread)
        return NULL;
      thr_create_ptr = __libc_dlsym (libpthread, "thr_create");
      if (!thr_create_ptr)
        return NULL;
    }

  /* The default server create action is to create a server thread. We use
     thr_create since we want to create this as a daemon thread.  */
  thr_create_ptr (NULL, 0, door_create_default_proc, NULL, THR_DETACHED, NULL);

  return NULL;
}


static void * door_unref_proc (void *arg)
{
  /* We may get interrupted so loop.  */
  while (INLINE_SYSCALL (door, 6, 0, 0, 0, 0, 0, SYS_SUB_door_unrefsys) &&
      errno == EINTR) ;

  return NULL;
}


int door_create (void (*server_procedure)(void *cookie, char *argp,
      size_t arg_size, door_desc_t *dp, uint_t n_desc), void *cookie,
      unsigned int attributes)
{
  // TODO: remove
  if (attributes & ~(DOOR_NO_CANCEL | DOOR_REFUSE_DESC | DOOR_PRIVATE | \
        DOOR_UNREF | DOOR_UNREF_MULTI))
    abort ();

  /* We lock the io list lock as fork() locks it before forking. This allows us
     to be safe in the face of a fork.  */
  _IO_list_lock ();

  return INLINE_SYSCALL (door, 6, (long)server_procedure, (long)cookie, attributes,
      0, 0, SYS_SUB_door_create);

  pid_t pid = getpid ();
  if (__door_private_pid != pid && (attributes & DOOR_PRIVATE) == 0)
    {
      /* We haven't created the first server.  */
      (*door_server_create_proc) (NULL);
      __door_private_pid = pid;
    }
  if (__door_unref_pid != pid && (attributes & (DOOR_UNREF | DOOR_UNREF_MULTI)))
    {
      /* We haven't created the unreferenced thread.  */
      thr_create (NULL, 0, door_unref_proc, NULL, THR_DAEMON, NULL);
      __door_unref_pid = pid;
    }

  _IO_list_unlock ();
}


int door_ucred (ucred_t **info)
{
  ucred_t *uc = *info;
  if (!uc)
    {
      uc = _ucred_alloc ();
      if (!uc)
        return -1;
    }

  int res = INLINE_SYSCALL (door, 6, (long)uc, 0, 0, 0, 0, SYS_SUB_door_ucred);
  if (res != 0)
    {
      if (!*info)
        free (uc);
      return -1;
    }

  *info = uc;

  return 0;
}


int door_cred (door_cred_t *info)
{
  ucred_t *uc = alloca (ucred_size ());
  int res = INLINE_SYSCALL (door, 6, (long)uc, 0, 0, 0, 0, SYS_SUB_door_ucred);
  if (res != 0)
    return -1;

  info->dc_euid = ucred_geteuid (uc);
  info->dc_ruid = ucred_getruid (uc);
  info->dc_egid = ucred_getegid (uc);
  info->dc_rgid = ucred_getrgid (uc);
  info->dc_pid = ucred_getpid (uc);

  return 0;
}
