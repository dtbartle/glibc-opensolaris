/*
 *
 * Assembly version of the standard strcat() function.  
 *
 * Contributed by Dan Pop <Dan.Pop@cern.ch>
 *
 * Return: dest
 *
 * Inputs:
 *      in0:    dest
 *      in1:    src
 *
 * A straightforword implementation: strcpy(dest + strlen(dest), src).
 *
 * Could be marginally optimised by inlining the code of strcpy() and
 * strlen(), to avoid the two function calls.  OTOH, by not doing that,
 * we avoid L1I cache pollution (code using strcat() is likely to also
 * use strcpy() and strlen(), so we already have a copy of these functions
 * in the cache).
 *
 */

#include <sysdep.h>
#undef ret

#define src	in1
#define dest	in0
#define save_pfs loc0
#define save_b0	loc1
#define tmp	loc2
#define rc	ret0

ENTRY(strcat)
	alloc 	save_pfs = ar.pfs, 2, 3, 2, 0
	mov	save_b0 = b0
	mov	out0 = dest
	mov	tmp = gp ;;
	br.call.sptk.many b0 = strlen# ;; // rc = strlen(dest);
        mov	gp = tmp
	add	out0 = dest, rc
	mov	out1 = src
	br.call.sptk.many b0 = strcpy# ;; // strcpy(dest + strlen(dest), src)
	mov     gp = tmp
	mov	rc = dest
	mov	b0 = save_b0
	mov	ar.pfs = save_pfs
	br.ret.sptk.many b0
END(strcat)
