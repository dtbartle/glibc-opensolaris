/* Header for nscd SELinux access controls.
   Author: Matthew Rickard <mjricka@epoch.ncsc.mil>, 2004.  */

#ifndef _SELINUX_H
#define _SELINUX_H 1

#include "nscd.h"

#ifdef HAVE_SELINUX
/* Global variable to tell if the kernel has SELinux support.  */
extern int selinux_enabled;

/* Define this for AVC stat usage.  */
struct avc_cache_stats;

/* Initialize the userspace AVC.  */
extern void nscd_avc_init (void);
/* Destroy the userspace AVC.  */
extern void nscd_avc_destroy (void);
/* Determine if we are running on an SELinux kernel.  */
extern void nscd_selinux_enabled (int *selinux_enabled);
/* Check if the client has permission for the request type.  */
extern int nscd_request_avc_has_perm (int fd, request_type req);
/* Initialize AVC statistic information.  */
extern void nscd_avc_cache_stats (struct avc_cache_stats *cstats);
/* Display statistics on AVC usage.  */
extern void nscd_avc_print_stats (struct avc_cache_stats *cstats);
#else
# define selinux_enabled 0
# define nscd_avc_init() (void) 0
# define nscd_avc_destroy() (void) 0
# define nscd_selinux_enabled(selinux_enabled) (void) 0
# define nscd_request_avc_has_perm(fd, req) 0
# define nscd_avc_cache_stats(cstats) (void) 0
# define nscd_avc_print_stats(cstats) (void) 0
#endif /* HAVE_SELINUX */

#endif /* _SELINUX_H */
