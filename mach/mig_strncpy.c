/* Silly pointless function MiG needs.  */

#include <mach.h>

vm_size_t
__mig_strncpy (char *dest, char *src, vm_size_t len)
{
  size_t i;

  if (len == 0)
    return 0;

  for (i = 1; i < len; ++i)
    if ((*dest++ = *src++) == '\0')
      return i;

  *dest = '\0';
  return i;
}
weak_alias (__mig_strncpy, mig_strncpy)
