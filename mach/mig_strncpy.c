/* Silly pointless function MiG needs.  */

#include <mach.h>

vm_size_t
__mig_strncpy (char *dest, const char *src, vm_size_t len)
{
  return __stpncpy (dst, src, len) - dst;
}
weak_alias (__mig_strncpy, mig_strncpy)
