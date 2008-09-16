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

#ifndef _SYS_PRIV_NAMES_H
#define _SYS_PRIV_NAMES_H

#define	PRIV_CONTRACT_EVENT	((const char *)"contract_event")
#define	PRIV_CONTRACT_IDENTITY	((const char *)"contract_identity")
#define	PRIV_CONTRACT_OBSERVER	((const char *)"contract_observer")
#define	PRIV_CPC_CPU		((const char *)"cpc_cpu")
#define	PRIV_DTRACE_KERNEL	((const char *)"dtrace_kernel")
#define	PRIV_DTRACE_PROC	((const char *)"dtrace_proc")
#define	PRIV_DTRACE_USER	((const char *)"dtrace_user")
#define	PRIV_FILE_CHOWN		((const char *)"file_chown")
#define	PRIV_FILE_CHOWN_SELF	((const char *)"file_chown_self")
#define	PRIV_FILE_DAC_EXECUTE	((const char *)"file_dac_execute")
#define	PRIV_FILE_DAC_READ	((const char *)"file_dac_read")
#define	PRIV_FILE_DAC_SEARCH	((const char *)"file_dac_search")
#define	PRIV_FILE_DAC_WRITE	((const char *)"file_dac_write")
#define	PRIV_FILE_DOWNGRADE_SL	((const char *)"file_downgrade_sl")
#define	PRIV_FILE_LINK_ANY	((const char *)"file_link_any")
#define	PRIV_FILE_OWNER		((const char *)"file_owner")
#define	PRIV_FILE_SETID		((const char *)"file_setid")
#define	PRIV_FILE_UPGRADE_SL	((const char *)"file_upgrade_sl")
#define	PRIV_FILE_FLAG_SET	((const char *)"file_flag_set")
#define	PRIV_GRAPHICS_ACCESS	((const char *)"graphics_access")
#define	PRIV_GRAPHICS_MAP	((const char *)"graphics_map")
#define	PRIV_IPC_DAC_READ	((const char *)"ipc_dac_read")
#define	PRIV_IPC_DAC_WRITE	((const char *)"ipc_dac_write")
#define	PRIV_IPC_OWNER		((const char *)"ipc_owner")
#define	PRIV_NET_BINDMLP	((const char *)"net_bindmlp")
#define	PRIV_NET_ICMPACCESS	((const char *)"net_icmpaccess")
#define	PRIV_NET_MAC_AWARE	((const char *)"net_mac_aware")
#define	PRIV_NET_PRIVADDR	((const char *)"net_privaddr")
#define	PRIV_NET_RAWACCESS	((const char *)"net_rawaccess")
#define	PRIV_PROC_AUDIT		((const char *)"proc_audit")
#define	PRIV_PROC_CHROOT	((const char *)"proc_chroot")
#define	PRIV_PROC_CLOCK_HIGHRES	((const char *)"proc_clock_highres")
#define	PRIV_PROC_EXEC		((const char *)"proc_exec")
#define	PRIV_PROC_FORK		((const char *)"proc_fork")
#define	PRIV_PROC_INFO		((const char *)"proc_info")
#define	PRIV_PROC_LOCK_MEMORY	((const char *)"proc_lock_memory")
#define	PRIV_PROC_OWNER		((const char *)"proc_owner")
#define	PRIV_PROC_PRIOCNTL	((const char *)"proc_priocntl")
#define	PRIV_PROC_SESSION	((const char *)"proc_session")
#define	PRIV_PROC_SETID		((const char *)"proc_setid")
#define	PRIV_PROC_TASKID	((const char *)"proc_taskid")
#define	PRIV_PROC_ZONE		((const char *)"proc_zone")
#define	PRIV_SYS_ACCT		((const char *)"sys_acct")
#define	PRIV_SYS_ADMIN		((const char *)"sys_admin")
#define	PRIV_SYS_AUDIT		((const char *)"sys_audit")
#define	PRIV_SYS_CONFIG		((const char *)"sys_config")
#define	PRIV_SYS_DEVICES	((const char *)"sys_devices")
#define	PRIV_SYS_IPC_CONFIG	((const char *)"sys_ipc_config")
#define	PRIV_SYS_LINKDIR	((const char *)"sys_linkdir")
#define	PRIV_SYS_MOUNT		((const char *)"sys_mount")
#define	PRIV_SYS_IP_CONFIG	((const char *)"sys_ip_config")
#define	PRIV_SYS_NET_CONFIG	((const char *)"sys_net_config")
#define	PRIV_SYS_NFS		((const char *)"sys_nfs")
#define	PRIV_SYS_RES_CONFIG	((const char *)"sys_res_config")
#define	PRIV_SYS_RESOURCE	((const char *)"sys_resource")
#define	PRIV_SYS_SMB		((const char *)"sys_smb")
#define	PRIV_SYS_SUSER_COMPAT	((const char *)"sys_suser_compat")
#define	PRIV_SYS_TIME		((const char *)"sys_time")
#define	PRIV_SYS_TRANS_LABEL	((const char *)"sys_trans_label")
#define	PRIV_VIRT_MANAGE	((const char *)"virt_manage")
#define	PRIV_WIN_COLORMAP	((const char *)"win_colormap")
#define	PRIV_WIN_CONFIG		((const char *)"win_config")
#define	PRIV_WIN_DAC_READ	((const char *)"win_dac_read")
#define	PRIV_WIN_DAC_WRITE	((const char *)"win_dac_write")
#define	PRIV_WIN_DEVICES	((const char *)"win_devices")
#define	PRIV_WIN_DGA		((const char *)"win_dga")
#define	PRIV_WIN_DOWNGRADE_SL	((const char *)"win_downgrade_sl")
#define	PRIV_WIN_FONTPATH	((const char *)"win_fontpath")
#define	PRIV_WIN_MAC_READ	((const char *)"win_mac_read")
#define	PRIV_WIN_MAC_WRITE	((const char *)"win_mac_write")
#define	PRIV_WIN_SELECTION	((const char *)"win_selection")
#define	PRIV_WIN_UPGRADE_SL	((const char *)"win_upgrade_sl")
#define	PRIV_XVM_CONTROL	((const char *)"xvm_control")
#define	PRIV_EFFECTIVE		((const char *)"Effective")
#define	PRIV_INHERITABLE	((const char *)"Inheritable")
#define	PRIV_PERMITTED		((const char *)"Permitted")
#define	PRIV_LIMIT		((const char *)"Limit")

#endif /* _SYS_PRIV_NAMES_H */
