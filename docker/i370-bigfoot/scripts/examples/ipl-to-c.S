/*
 * Shim to create an i370 binary that can be IPL'ed.
 * Copyright (c) 1999 Linas Vepstas (linas@linas.org)
 *
 */

/* Stop the machine. Handy for debugging purposes, but also
 * used in a few "it can't possibly happen" situations.
 */
#define HALT(sav)							\
	SPKA    sav(0);			/* Ensure we can use lo core */ \
	L	r1,=X'000A0000';	/* disabled wait             */	\
	ST	r1,sav(,0);						\
	L	r1,=A(1f);		/* goto label 1 forward.     */	\
	O	r1,=X'80000000'; 	/* Set AMODE 31-bit          */	\
	ST	r1,sav+4(,0);						\
	LPSW	sav(0);			/* oops halt the machine     */ \
1:	NOPR	r0;

/* First instruction executed is here */
/*
 * We set up just enough to let a C lang call to be made.
 * Basically, this means just reserving some space for
 * a stack and making r13 point at it. That's all, and we can call.
 *
 * Note that we will be using this stack not just for startup,
 * but also for the exception handlers below ...
 *
 * Note that this stack is kind of bogus, and should be replaced by
 * something that has a guard page at the end of it.
 *
 * Register naming convention:
 * lr == r14 == link reg
 * r13 == frame & arg pointer (bottom of stack)
 * r11 == stack pointer (top of stack)
 */

/* start of text section */
	.text

	/* Short-format PSW, since bit-12 = 1. */
	/* AMODE = 31 (bits 31, 32 of PSW are 01) */
	.globl  _psw
_psw:
	.long  0x00080000,0x80000010
	.long  0x00000000,0x00000000

	.globl	_start
_start:

	/* Perform initialization to call C routines                      */
	BASR	r15,0			/* load r15 with PSW              */
	.using	.,r15			/* use r15 as base register       */

	L	r13,=A(init_ksp)	/* load address of stack into r13 */
	L	r5,=XL4'f00fdaad'	/* load eyecatcher into r5        */
	L	r6,=A(init_ksp)		/* Verify stack address           */
	L	r7,=XL4'3137c0de'	/* load another eyecatcher        */
	LA	r11,2048(,r13);		/* go half-way up the stack       */
	LA	r11,2048(,r13);		/* load r11 with top of stack     */
	SLR	r3,r3
	ST	r3,8(,r13)		/* terminate stack backchain      */
	ST	r3,8(,r11)		/* terminate stack backchain      */
	ST	r3,64(,r13)		/* terminate stack backchain      */
	ST	r3,64(,r11)		/* terminate stack backchain      */
	L	r15,=A(start_kernel)	/* load address of C routine      */
	BASR	lr,r15			/* jump to C routine              */
	.drop	r15
	.using	.,lr			/* re-establish addressing.       */
	HALT (384)			/* Halt on return.                */

	.balign	4			/* align literal pool             */
	.ltorg				/* dump literal pool              */

/* ======================== end of file ============================ */
