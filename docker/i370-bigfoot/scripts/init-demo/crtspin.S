
# Example demo of the _start entry point, which sets up argc, argv,
# envp and the stack, and then calls main(). Illustrates the basic
# i370 ELF ABI.
#
# Upon entry, most registers contain invalid data, except for
#
#    r13         zero
#    r11         pointer to start of stack
#    r2          Pointer to the arguments and environment:
#                0(r2)                   argc
#                4(r2)                   argv[0]
#                ...
#                (4*argc)(r2)            NULL
#                (4*(argc+1))(r2)        envp[0]
#                ...
#                ...                     NULL
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
	# We arrive here with r2 holding the stack pointer.
	# (Pointing to the top of stack; the args are there)
	# Store stack pointer at as the first entry in the frame.
	# The C code prolog will load r13 with 0(r11)
	ST      r2, 0(r11)

	L       r1,0(,r2)      # load r1 with argc
	ST      r1,88(,r11)    # Pass on stack.
	LA      r5,4(,r2)      # load r5 with argv
	ST      r5,92(,r11)    # Pass on stack

	LA      r14,12(,r11)
	BASR    r14,r15        # BASR will write PSW to 12(,r11)

_endit:
	NOPR 0
	NOPR 0
	NOPR 0
	.ltorg
