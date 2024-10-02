
# Example demo of the _start entry point, which sets up argc, argv,
# envp and the stack, and then calls main(). Illustrates the basic
# i370 ELF ABI.
#
# Upon entry, most registers contain invalid data, except for
#
#    r13         zero
#    r11         Pointer to frame bottom
#    r1          Pointer to frame top
#    r2          Pointer to argc
#    r3          Value of argv
#    r4          Value of envp
#
# These need to be copied to set up the callees stack.
#
# The i370 ELF stackframe looks like this:
#
#    0          Page table
#    4          unused
#    8          Caller frame pointer
#    12         Caller r14 (backchain aka link register)
#    16         Caller r15
#    20         Caller r0
#    24         Caller r1
#    ...
#    60         Caller r10
#    64         Callee frame pointer
#    68         Caller r12
#    72         Unused
#    76         Unused
#    80         Scratch
#    84         Scratch
#    88         Arg 0
#    92         Arg 1
#    ...
#

	.file    "crtspin.s"

	.section .text
	.global _start
	.type   _start,@function
	.align 4
_start:
	BASR r6,0              # Figure out where we are.
	.using .,r6            # Establish addressing
	L       r15,=A(main)   # Get address of main()
	.drop r6

	# We arrive here with R11 the frame pointer.
	# (Pointing to bottom of stack; stack grows up)
	# We arrive here with r1 holding the stack pointer.
	# (Pointing to the top of stack; the args are there)
	# Store stack pointer at as the first entry in the frame.
	# The C code prolog will load r13 with 0(r11)
	ST      r1, 0(r11)

	L       r2,0(r2)       # Get value of argc
	ST      r2,88(,r11)    # Pass argc on stack.
	ST      r3,92(,r11)    # Pass argv on stack
	ST      r4,96(,r11)    # Pass envp on stack

	LA      r14,12(,r11)   # Set up link register
	BASR    r14,r15        # BASR will write PSW to 12(,r11)

_endit:
	# TODO: should make exit() syscall here.
	NOPR 0
	NOPR 0
	NOPR 0
	.ltorg
