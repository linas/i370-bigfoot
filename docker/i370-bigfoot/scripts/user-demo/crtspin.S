
	.file    "crtspin.s"

	.section .text
	.global _start
	.type   _start,@function
	.align 4
_start:
	BASR r6,0
	.using .,r6
	L r15,=A(main)
	.drop r6

	# We arrive here with R11 the frame pointer
	# We arrive here with r2 holding the stack pointer.
	# Store it at as the first entry in the frame.
	# Very soon, r13 will be loaded from here.
	ST r2, 0(r11)

	# TODO: argv and envp are sitting low in the frame.
	# Set up the arguments to main giving argc and argv.

	# BASR will write PSW to 12(,r11)
	LA r14,12(,r11)
	BASR r14,r15

_endit:
	NOPR 0
	NOPR 0
	NOPR 0
	.ltorg
