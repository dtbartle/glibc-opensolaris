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
#include <unistd.h>
#include <ucred.h>
#include <errno.h>
#include <ucredP.h>
#include <assert.h>

DECLARE_INLINE_SYSCALL (int, getpeerucred, int fd, ucred_t *ucred);
DECLARE_INLINE_SYSCALL (int, ucred_get, pid_t pid, ucred_t *ucred);
DECLARE_INLINE_SYSCALL (int, syslabeling, void);

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/ucred-get-3c?a=view
         http://docs.sun.com/app/docs/doc/816-5168/getpeerucred-3c?l=ru&a=view */

ucred_t *ucred_get (pid_t pid)
{
  size_t uc_size = ucred_size ();
  ucred_t *uc = malloc (uc_size);
  if (!uc)
    return NULL;
  uc->uc_size = uc_size;

  INLINE_SYSCALL (ucred_get, 2, pid, uc);

  return uc;
}


void ucred_free (ucred_t *uc)
{
  free(uc);
}


#define MAKE_PRCRED_T_CALL(field, type)                                     \
  type ucred_get##field (const ucred_t *uc)                                 \
  {                                                                         \
    if (uc->uc_credoff == 0)                                                \
      {                                                                     \
        __set_errno(EINVAL);                                                \
        return (type)-1;                                                    \
      }                                                                     \
    return (type)((prcred_t *)((char *)uc + uc->uc_credoff))->pr_##field;   \
   }

MAKE_PRCRED_T_CALL (euid, uid_t)
MAKE_PRCRED_T_CALL (ruid, uid_t)
MAKE_PRCRED_T_CALL (suid, uid_t)
MAKE_PRCRED_T_CALL (egid, gid_t)
MAKE_PRCRED_T_CALL (rgid, gid_t)
MAKE_PRCRED_T_CALL (sgid, gid_t)


int ucred_getgroups (const ucred_t *uc, const gid_t **groups)
{
  if (uc->uc_credoff == 0 || groups == NULL)
    {
      __set_errno(EINVAL);
      return -1;
    }

  /* The docs say that *groups should always be free'd, so we make sure
     it's NULL if there are no groups.  */
  prcred_t *cred = (prcred_t *)((char *)uc + uc->uc_credoff);
  if (cred->pr_ngroups > 0)
    *groups = cred->pr_groups;
  else
    *groups = NULL;

  return cred->pr_ngroups;
}


const priv_set_t *ucred_getprivset (const ucred_t *uc, const char *set)
{
  // TODO
  __set_errno (ENOSYS);
  return NULL;
}


pid_t ucred_getpid (const ucred_t *uc)
{
  if(uc->uc_pid == (pid_t)-1)
    __set_errno (EINVAL);

  return uc->uc_pid;
}


projid_t ucred_getprojid (const ucred_t *uc)
{
  if(uc->uc_projid == (projid_t)-1)
    __set_errno (EINVAL);

  return uc->uc_projid;
}


zoneid_t ucred_getzoneid (const ucred_t *uc)
{
  if(uc->uc_zoneid == (zoneid_t)-1)
    __set_errno (EINVAL);

  return uc->uc_zoneid;
}


unsigned int ucred_getpflags (const ucred_t *uc, unsigned int flags)
{
  // TODO
  __set_errno (ENOSYS);
  return -1;
}


m_label_t *ucred_getlabel (const ucred_t *uc)
{
  int syslabeling = INLINE_SYSCALL (syslabeling, 0);
  if (!syslabeling || uc->uc_labeloff == 0)
    {
      __set_errno (EINVAL);
      return NULL;
    }

  return (m_label_t *)((char *)uc + uc->uc_labeloff);
}


size_t ucred_size (void)
{
    extern int __getprivimplinfo_cached (priv_impl_info_t **info);

    /* the docs don't say what to do in case of error */
    priv_impl_info_t *info;
    assert (__getprivimplinfo_cached (&info) == 0);

    /* XXX: We shouldn't use AUDITINFO64_ADDR_T_SIZE and BSLABEL_T_SIZE.  */
    return sizeof(ucred_t) + sizeof(prcred_t) + sizeof(prpriv_t) +
        ((int)sysconf (_SC_NGROUPS_MAX) - 1) * sizeof(gid_t) +
        sizeof(priv_chunk_t) * (info->priv_setsize * info->priv_nsets - 1) +
        info->priv_infosize + AUDITINFO64_ADDR_T_SIZE + BSLABEL_T_SIZE;
}


int getpeerucred (int fd, ucred_t **ucred)
{
  ucred_t *uc = *ucred;

  /* alloc ucred if needed */
  if(*ucred == NULL)
    {
      size_t uc_size = ucred_size ();
      ucred_t *uc = malloc (uc_size);
      if (!uc)
        return -1;
      uc->uc_size = uc_size;
      *ucred = uc;
    }

  int result = INLINE_SYSCALL (getpeerucred, 2, fd, uc);
  if (result == -1 && *ucred == NULL)
      free (uc);
  else if (result == 0 && *ucred == NULL)
      *ucred = uc;

  return result;
}
