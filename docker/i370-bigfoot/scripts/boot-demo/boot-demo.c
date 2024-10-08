/*
 * kernel-demo.c
 *
 * Demo of a bootable kernel, written in C. Since this demo will run
 * in supervisor mode, in real memory and not virtual memory, so that
 * no page tables or TLB are in use, the name "kernel" is appropriate.
 *
 * This does almost nothing, except to allocate some space for a stack,
 * (which is never actually used), and return an eyecatcher ir GPR 15.
 */

/* Define some stack space */
char kstack[4096];

/* So something. Demonstrate a function call. */
int do_stuff(int a, int b)
{
	return a+b;
}

int start_kernel()
{
	kstack[0] = 0xBA;
	kstack[1] = 0xD1;
	kstack[2] = 0xDE;
	kstack[3] = 0xA5;

	do_stuff(0x33, 0x44);

	/* Eyecatcher */
	int y=0xdeadbeef;

	/* Return the eyecatcher in r15 */
	return y;
}
