/*
 *
 * Optimized version of the standard strcmp() function
 *
 * Contributed by Dan Pop <Dan.Pop@cern.ch>
 *
 * Return: the result of the comparison
 *
 * Inputs:
 *      in0:    s1
 *      in1:    s2
 *
 * Unlike memcmp(), this function is optimized for mismatches within the
 * first few characters.
 *
 */

#include <sysdep.h>
#undef ret

#define s1		in0
#define s2		in1

#define saved_pfs	r14
#define val1		r15
#define val2		r16


ENTRY(strcmp)
	alloc	saved_pfs = ar.pfs, 2, 0, 0, 0
.loop:
	ld1	val1 = [s1], 1
	ld1	val2 = [s2], 1
	cmp.eq	p6, p0 = r0, r0		// set p6
	;;
	cmp.ne.and p6, p0 = val1, r0
	cmp.ne.and p6, p0 = val2, r0
	cmp.eq.and p6, p0 = val1, val2
(p6)	br.cond.sptk .loop
	sub	ret0 = val1, val2
	mov	ar.pfs = saved_pfs
	br.ret.sptk.many b0
END(strcmp)
