/*
 *
 * Optimized version of the standard strncmp() function
 *
 * Contributed by Dan Pop <Dan.Pop@cern.ch>
 *
 * Return: the result of the comparison
 *
 * Inputs:
 *      in0:    s1
 *      in1:    s2
 *	in2:	n
 *
 * Unlike memcmp(), this function is optimized for mismatches within the
 * first few characters.
 *
 */

#include <sysdep.h>
#undef ret

#define s1		in0
#define s2		in1
#define n		in2

#define saved_pfs	r14
#define val1		r15
#define val2		r16


ENTRY(strncmp)
	alloc	saved_pfs = ar.pfs, 3, 0, 0, 0
	mov	ret0 = r0
	cmp.eq  p6, p0 = r0, r0		// set p6
	cmp.eq	p7, p0 = n, r0		// return immediately if n == 0
(p7)	br.cond.spnt .restore_and_exit ;;
.loop:
	ld1	val1 = [s1], 1
	ld1	val2 = [s2], 1
	adds	n = -1, n		// n--
	;;
	cmp.ne.and p6, p0 = val1, r0
	cmp.ne.and p6, p0 = val2, r0
	cmp.ne.and p6, p0 = n, r0
	cmp.eq.and p6, p0 = val1, val2
(p6)	br.cond.sptk .loop
	sub	ret0 = val1, val2
.restore_and_exit:
	mov	ar.pfs = saved_pfs
	br.ret.sptk.many b0
END(strncmp)	
