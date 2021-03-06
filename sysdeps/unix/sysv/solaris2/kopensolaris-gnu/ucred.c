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
#include <ucredP.h>
#include <auditP.h>
#include <priv.h>
#include <procfs.h>
#include <errno.h>
#include <assert.h>

DECLARE_INLINE_SYSCALL (int, getpeerucred, int fd, ucred_t *ucred);
DECLARE_INLINE_SYSCALL (int, ucred_get, pid_t pid, ucred_t *ucred);

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/ucred-get-3c?a=view
         http://docs.sun.com/app/docs/doc/816-5168/getpeerucred-3c?l=ru&a=view */


ucred_t *_ucred_alloc (void)
{
  size_t uc_size = ucred_size ();
  ucred_t *uc = malloc (uc_size);
  if (uc)
    uc->uc_size = uc_size;
  return uc;
}


ucred_t *ucred_get (pid_t pid)
{
  ucred_t *uc = _ucred_alloc ();
  if (!uc)
    return NULL;

  int res = INLINE_SYSCALL (ucred_get, 2, pid, uc);
  if (res != 0)
    return NULL;

  return uc;
}


void ucred_free (ucred_t *uc)
{
  free(uc);
}


uid_t ucred_geteuid (const ucred_t *uc)
{
  if (uc->uc_credoff == 0)
    {
      __set_errno (EINVAL);
      return (uid_t)-1;
    }

  return (uid_t)((prcred_t *)((char *)uc + uc->uc_credoff))->pr_euid;
}


uid_t ucred_getruid (const ucred_t *uc)
{
  if (uc->uc_credoff == 0)
    {
      __set_errno (EINVAL);
      return (uid_t)-1;
    }

  return (uid_t)((prcred_t *)((char *)uc + uc->uc_credoff))->pr_ruid;
}


uid_t ucred_getsuid (const ucred_t *uc)
{
  if (uc->uc_credoff == 0)
    {
      __set_errno (EINVAL);
      return (uid_t)-1;
    }

  return (uid_t)((prcred_t *)((char *)uc + uc->uc_credoff))->pr_suid;
}


gid_t ucred_getegid (const ucred_t *uc)
{
  if (uc->uc_credoff == 0)
    {
      __set_errno (EINVAL);
      return (gid_t)-1;
    }

  return (gid_t)((prcred_t *)((char *)uc + uc->uc_credoff))->pr_egid;
}


gid_t ucred_getrgid (const ucred_t *uc)
{
  if (uc->uc_credoff == 0)
    {
      __set_errno (EINVAL);
      return (gid_t)-1;
    }

  return (gid_t)((prcred_t *)((char *)uc + uc->uc_credoff))->pr_rgid;
}


gid_t ucred_getsgid (const ucred_t *uc)
{
  if (uc->uc_credoff == 0)
    {
      __set_errno(EINVAL);                                                \
      return (gid_t)-1;                                                    \
    }

  return (gid_t)((prcred_t *)((char *)uc + uc->uc_credoff))->pr_sgid;
}


int ucred_getgroups (const ucred_t *uc, const gid_t **groups)
{
  if (uc->uc_credoff == 0 || groups == NULL)
    {
      __set_errno (EINVAL);
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
  /* Get prpriv_t.  */
  if (uc->uc_privoff == 0)
    {
      __set_errno (EINVAL);
      return NULL;
    }
  prpriv_t * pr = (prpriv_t *)((char *)uc + uc->uc_privoff);

  /* Get priv set number.  */
  int setnum = priv_getsetbyname (set);
  if (setnum == -1)
    return NULL;

  return (priv_set_t *)&pr->pr_sets[setnum * pr->pr_setsize];
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
  /* Get prpriv_t.  */
  if (uc->uc_privoff == 0)
    {
      __set_errno (EINVAL);
      return (unsigned int)-1;
    }
  prpriv_t *pr = (prpriv_t *)((char *)uc + uc->uc_privoff);

  /* Iterate over all priv_info_t's. Note that the first priv_info_t follows
     the list of priv sets.  */
  priv_info_t * pi = (priv_info_t *)&pr->pr_sets[pr->pr_nsets * pr->pr_setsize];
  uint32_t left = pr->pr_infosize;
  while (left)
    {
      if (pi->priv_info_type == PRIV_INFO_FLAGS)
        return ((priv_info_uint_t *)pi)->val & flags;

      left -= pi->priv_info_size;
      pi = (priv_info_t *)((char *)pi + pi->priv_info_size);
    }

  /* We didn't find PRIV_INFO_FLAGS.  */
  __set_errno (EINVAL);
  return (unsigned int)-1;
}


m_label_t *ucred_getlabel (const ucred_t *uc)
{
  extern int is_system_labeled (void);

  if (!is_system_labeled () || uc->uc_labeloff == 0)
    {
      __set_errno (EINVAL);
      return NULL;
    }

  return (m_label_t *)((char *)uc + uc->uc_labeloff);
}


au_id_t ucred_getauid (const ucred_t *uc)
{
  if (uc->uc_audoff == 0)
    return AU_NOAUDITID;
  const auditinfo64_addr_t *info = (auditinfo64_addr_t *)
      ((char *)uc + uc->uc_audoff);

  return info->ai_auid;
}


au_asid_t ucred_getasid (const ucred_t *uc)
{
  if (uc->uc_audoff == 0)
    return (au_asid_t)-1;
  const auditinfo64_addr_t *info = (auditinfo64_addr_t *)
      ((char *)uc + uc->uc_audoff);

  return info->ai_asid;
}


const au_tid64_addr_t * ucred_getatid (const ucred_t *uc)
{
  if (uc->uc_audoff == 0)
    {
      __set_errno (EINVAL);
      return NULL;
    }
  const auditinfo64_addr_t *info = (auditinfo64_addr_t *)
      ((char *)uc + uc->uc_audoff);

  return &info->ai_termid;
}


const au_mask_t * ucred_getamask (const ucred_t *uc)
{
  if (uc->uc_audoff == 0)
    {
      __set_errno (EINVAL);
      return NULL;
    }
  const auditinfo64_addr_t *info = (auditinfo64_addr_t *)
      ((char *)uc + uc->uc_audoff);

  return &info->ai_mask;
}


size_t ucred_size (void)
{
  const priv_impl_info_t *info = getprivimplinfo ();

  return sizeof (ucred_t) + sizeof (prcred_t) + sizeof (prpriv_t) +
    ((int)sysconf (_SC_NGROUPS_MAX) - 1) * sizeof (gid_t) +
    sizeof (priv_chunk_t) * (info->priv_setsize * info->priv_nsets - 1) +
    info->priv_infosize + sizeof (auditinfo64_addr_t) + BSLABEL_T_SIZE;
}


int getpeerucred (int fd, ucred_t **ucred)
{
  ucred_t *uc = *ucred;

  /* alloc ucred if needed */
  if (*ucred == NULL)
    {
      uc = _ucred_alloc ();
      if (!uc)
        return -1;
      *ucred = uc;
    }

  int res = INLINE_SYSCALL (getpeerucred, 2, fd, uc);
  if (res == -1 && *ucred == NULL)
      free (uc);
  else if (res == 0 && *ucred == NULL)
      *ucred = uc;

  return res;
}
