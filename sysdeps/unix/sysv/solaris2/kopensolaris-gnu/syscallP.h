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

#ifndef _SYSCALL_PRIV_H
#define _SYSCALL_PRIV_H

/* SYS_pgrpsys */
#define SYS_SUB_getpgrp     0
#define SYS_SUB_setpgrp     1
#define SYS_SUB_getsid      2
#define SYS_SUB_setsid      3
#define SYS_SUB_getpgid     4
#define SYS_SUB_setpgid     5

/* SYS_signal */
#define SYS_SUB_signal      0
#define SYS_SUB_sigset      1
#define SYS_SUB_sighold     2
#define SYS_SUB_sigrelse    3
#define SYS_SUB_sigignore   4
#define SYS_SUB_sigpause    5

/* SYS_msgsys */
#define SYS_SUB_msgget      0
#define SYS_SUB_msgctl      1
#define SYS_SUB_msgrcv      2
#define SYS_SUB_msgsnd      3
#define SYS_SUB_msgids      4
#define SYS_SUB_msgsnap     5

/* SYS_shmsys */
#define SYS_SUB_shmat       0
#define SYS_SUB_shmctl      1
#define SYS_SUB_shmdt       2
#define SYS_SUB_shmget      3
#define SYS_SUB_shmids      4

/* SYS_semsys */
#define SYS_SUB_semctl      0
#define SYS_SUB_semget      1
#define SYS_SUB_semop       2
#define SYS_SUB_semids      3
#define SYS_SUB_semtimedop  4

/* SYS_utssys */
#define SYS_SUB_uname       0 /* obsolete */
/* subcode 1 unused */
#define SYS_SUB_ustat       2
#define SYS_SUB_fusers      3

/* SYS_tasksys */
#define SYS_SUB_settaskid   0
#define SYS_SUB_gettaskid   1
#define SYS_SUB_getprojid   2

/* SYS_exacctsys */
#define SYS_SUB_getacct     0
#define SYS_SUB_putacct     1
#define SYS_SUB_wracct      2

/* SYS_getpagesizes */
#define SYS_SUB_getpagesizes    0
#define SYS_SUB_getpagesizes2   1

/* SYS_rctlsys */
#define SYS_SUB_rctlsys_get     0
#define SYS_SUB_rctlsys_set     1
#define SYS_SUB_rctlsys_list    2
#define SYS_SUB_rctlsys_ctl     3
#define SYS_SUB_rctlsys_projset 4

/* SYS_sidsys */
#define SYS_SUB_allocids        0
#define SYS_SUB_idmap_reg       1
#define SYS_SUB_idmap_unreg     2

/* SYS_fsat */
#define SYS_SUB_openat          0
#define SYS_SUB_openat64        1
#define SYS_SUB_fstatat64       2
#define SYS_SUB_fstatat         3
#define SYS_SUB_fchownat        4
#define SYS_SUB_unlinkat        5
#define SYS_SUB_futimesat       6
#define SYS_SUB_renameat        7
#define SYS_SUB_accessat        8
#define SYS_SUB_openattrdirat   9

/* SYS_lwp_park */
#define SYS_SUB_lwp_park            0
#define SYS_SUB_lwp_unpark          1
#define SYS_SUB_lwp_unpark_all      2
#define SYS_SUB_lwp_unpark_cancel   3
#define SYS_SUB_lwp_set_park        4

/* SYS_sendfilev */
#define SYS_SUB_sendfilev       0
#define SYS_SUB_sendfilev64     1

/* SYS_privsys */
#define SYS_SUB_setppriv       0
#define SYS_SUB_getppriv       1
#define SYS_SUB_getimplinfo    2
#define SYS_SUB_setpflags      3
#define SYS_SUB_getpflags      4
#define SYS_SUB_issetugid      5

/* SYS_ucredsys */
#define SYS_ucred_get       0
#define SYS_getpeerucred    1

/* SYS_sigpending */
#define SYS_SUB_sigpending  1
#define SYS_SUB_sigfillset  2

/* SYS_context */
#define SYS_SUB_getcontext  0
#define SYS_SUB_setcontext  1
#define SYS_SUB_getustack   2
#define SYS_SUB_setustack   3

/* SYS_forksys */
#define SYS_SUB_forkx       0
#define SYS_SUB_forkallx    1
#define SYS_SUB_vforkx      2

/* SYS_coresys */
#define SYS_SUB_core_set_options            1
#define SYS_SUB_core_get_options            2
#define SYS_SUB_core_set_global_path        3
#define SYS_SUB_core_get_global_path        4
#define SYS_SUB_core_set_process_path       5
#define SYS_SUB_core_get_process_path       6
#define SYS_SUB_core_set_global_content     7
#define SYS_SUB_core_get_global_content     8
#define SYS_SUB_core_set_process_content    9
#define SYS_SUB_core_get_process_content    10
#define SYS_SUB_core_set_default_path       11
#define SYS_SUB_core_get_default_path       12
#define SYS_SUB_core_set_default_content    13
#define SYS_SUB_core_get_default_content    14

/* SYS_lgrpsys / SYS_meminfosys */
#define SYS_SUB_meminfo             0
#define SYS_SUB_lgrp_generation     1
#define SYS_SUB_lgrp_version        2
#define SYS_SUB_lgrp_snapshot       3
#define SYS_SUB_lgrp_affinity_set   4
#define SYS_SUB_lgrp_affinity_get   5
#define SYS_SYB_lgrp_latency        6
#define SYS_SUB_lgrp_home           7

/* SYS_rusagesys */
#define SYS_SUB_getrusage           0
#define SYS_SUB_getrusage_chld      1
#define SYS_SUB_getrusage_lwp       2
#define SYS_SUB_getvmusage          3

/* TODO: SYS_port */

/* SYS_door */
#define SYS_SUB_door_create     0
#define SYS_SUB_door_revoke     1
#define SYS_SUB_door_info       2
#define SYS_SUB_door_call       3
#define SYS_SUB_door_return     4

/* SYS_pset */
#define SYS_SUB_pset_create         0
#define SYS_SUB_pset_destroy        1
#define SYS_SUB_pset_assign         2
#define SYS_SUB_pset_info           3
#define SYS_SUB_pset_bind           4
#define SYS_SUB_pset_getloadavg     5
#define SYS_SUB_pset_list           6
#define SYS_SUB_pset_setattr        7
#define SYS_SUB_pset_getattr        8
#define SYS_SUB_pset_assign_forced  9

/* SYS_rwlock */
#define SYS_SUB_lwp_rwlock_rdlock       0
#define SYS_SUB_lwp_rwlock_wrlock       1
#define SYS_SUB_lwp_rwlock_tryrdlock    2
#define SYS_SUB_lwp_rwlock_trywrlock    3
#define SYS_SUB_lwp_rwlock_unlock       4

/* SYS_zone */
#define SYS_SUB_zone_create         0
#define SYS_SUB_zone_destroy        1
#define SYS_SUB_zone_getattr        2
#define SYS_SUB_zone_enter          3
#define SYS_SUB_zone_list           4
#define SYS_SUB_zone_shutdown       5
#define SYS_SUB_zone_lookup         6
#define SYS_SUB_zone_boot           7
#define SYS_SUB_zone_version        8
#define SYS_SUB_zone_setattr        9
#define SYS_SUB_zone_add_datalink   10
#define SYS_SUB_zone_del_datalink   11
#define SYS_SUB_zone_check_datalink 12
#define SYS_SUB_zone_list_datalink  13

#endif /* _SYSCALL_PRIV_H */
