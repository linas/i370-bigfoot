/*
 * Shim to create an i370 binary that can be IPL'ed.
 * Copyright (c) 1999 Linas Vepstas (linas@linas.org)
 */

/* Stop the machine. Handy for debugging purposes, but also
 * used in a few "it can't possibly happen" situations.
 */
#define HALT(sav)							\
	SPKA    0(0);			/* Ensure we can use lo core */ \
	L	r1,=X'000A0000';	/* disabled wait             */	\
	ST	r1,sav(,0);						\
	L	r1,=A(1f);		/* goto label 1 forward.     */	\
	O	r1,=X'80000000'; 	/* Set AMODE 31-bit          */	\
	ST	r1,sav+4(,0);						\
	LPSW	sav(0);			/* oops halt the machine     */ \
1:	NOPR	r0;

/* Absolute address of some unused RAM. Used to assemble the PSW above. */
#define SCRATCH 384

/* First instruction executed is here */
/*
 * We set up just enough to let a C lang call to be made.
 * Basically, this means just reserving some space for a stack
 * and making r13 point at it. That's all, and we can call.
 *
 * The current i370 compiler is configured to make the stack
 * grow upwards (to larger addresses).
 *
 * Register naming convention:
 * lr == r14 == link reg
 * r13 == frame & arg pointer (bottom of stack)
 * r11 == stack pointer (top of stack)
 */

/* start of text section */
	.text

	/* Short-format PSW, since bit-12 = 1.
	 * AMODE = 31 (bits 31, 32 of PSW are 01)
	 * (_start - _psw) computes the distance to _start,
	 * and 0x80000000 | or's in the high bit.
	 */
	.globl  _psw
_psw:
	.long  0x00080000, 0x80000000 | (_start - _psw)

	/* Jump over this text. It's visible with r.0ff */
	.long  0x00000000,0x00000000
	.long  0x00000000,0x00000000
	.ebcdic "This is some EBCDIC text near the start of the file"
	.balign 4
	.long  0x00000000,0x00000000
	.long  0x00000000,0x00000000
	.long  0x0EBCD1C0,0x00A5C110
	.long  0x00000000,0x00000000
	.long  0x00000000,0x00000000
	.ascii "And now for ASCII text, Yayy!"
	.long  0x00000000,0x00000000
	.long  0x00000000,0x00000000

	.balign 4
	.globl	_start
_start:

	/* Perform initialization to call C routines                      */
	BASR	r15,0			/* load r15 with PSW              */
	.using	.,r15			/* use r15 as base register       */

	L	r13,=A(kstack)		/* load address of frame into r13 */
	L	r5,=XL4'f00fdaad'	/* load eyecatcher into r5        */
	L	r6,=A(kstack)		/* Verify stack address           */
	L	r7,=XL4'1337c0de'	/* load another eyecatcher        */
	LA	r11,128(,r13);		/* start stack a bit up higher    */
	SLR	r3,r3
	ST	r3,8(,r13)		/* terminate stack backchain      */
	ST	r3,8(,r11)		/* terminate stack backchain      */
	ST	r3,64(,r13)		/* terminate stack backchain      */
	ST	r3,64(,r11)		/* terminate stack backchain      */
	L	r15,=A(start_kernel)	/* load address of C routine      */
	BASR	lr,r15			/* jump to C routine              */
	.drop	r15
	.using	.,lr			/* re-establish addressing.       */
	HALT (SCRATCH)			/* Halt on return.                */

	.balign	4			/* align literal pool             */
	.ltorg				/* dump literal pool              */

/* ======================== end of file ============================ */
