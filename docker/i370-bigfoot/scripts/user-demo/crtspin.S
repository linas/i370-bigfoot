
	.section .text
	.p2align 2
	.global _start
	.type   _start,@function
_start:
	BASR r2,0
	.using .,r2
	L r15,=A(main)
	.drop r2

	BASR r15,r14
	NOPR 0
	NOPR 0
	NOPR 0
	.ltorg
