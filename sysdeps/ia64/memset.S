/*
 * Optimized version of the standard memset() function
 *
 * Contributed by Dan Pop <Dan.Pop@cern.ch>
 *
 * Return: dest
 *
 * Inputs:
 *      in0:    dest
 *      in1:    value
 *      in2:    count
 *
 * The algorithm is fairly straightforward: set byte by byte until we
 * we get to a word aligned address, then set word by word as much as
 * possible; the remaining few bytes are set one by one.
 *
 */

#include <sysdep.h>
#undef ret

#define dest		in0
#define byteval		in1
#define	cnt		in2

#define save_pfs 	loc0
#define ptr1		loc1
#define ptr2		loc2
#define tmp		loc3
#define	loopcnt		loc4
#define save_lc		loc5
#define wordval		loc6

ENTRY(memset)
	alloc	save_pfs = ar.pfs, 3, 7, 0, 0	
	mov	save_lc = ar.lc
	mov	ret0 = dest
	and	tmp = 7, dest
	cmp.eq	p6, p0 = cnt, r0
(p6)	br.cond.spnt restore_and_exit ;;
	mov	ptr1 = dest
	sub	loopcnt = 8, tmp
	cmp.gt	p6, p0 = 16, cnt
(p6)	br.cond.spnt set_few;;
	cmp.eq	p6, p0 = tmp, r0
(p6)	br.cond.sptk dest_aligned
	sub	cnt = cnt, loopcnt
	adds	loopcnt = -1, loopcnt;;
	mov	ar.lc = loopcnt;;	
l1:
	st1	[ptr1] = byteval, 1
	br.cloop.dptk	l1 ;;
dest_aligned:
	adds	ptr2 = 8, ptr1
	mux1	wordval = byteval, @brcst
	shr.u	loopcnt = cnt, 4 ;;	// loopcnt = cnt / 16
	cmp.eq	p6, p0 = loopcnt, r0
(p6)	br.cond.spnt	one_more
	and	cnt = 0xf, cnt		// compute the remaining cnt
	adds	loopcnt = -1, loopcnt;;
	mov     ar.lc = loopcnt;;	
l2:
	st8	[ptr1] = wordval, 16
	st8	[ptr2] = wordval, 16
	br.cloop.dptk l2
	cmp.le	p6, p0 = 8, cnt	;;
one_more:
(p6)	st8     [ptr1] = wordval, 8
(p6)	adds	cnt = -8, cnt ;;
	cmp.eq	p6, p0 = cnt, r0
(p6)	br.cond.spnt	restore_and_exit
set_few:
	adds	loopcnt = -1, cnt;;
	mov	ar.lc = loopcnt;;
l3:	
	st1     [ptr1] = byteval, 1
	br.cloop.dptk   l3 ;;	
restore_and_exit:
	mov	ar.lc = save_lc
	mov	ar.pfs = save_pfs
	br.ret.sptk.many b0					
END(memset)
