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

/* Defines some stack space */
char kstack[4096];

int start_kernel()
{
	kstack[0] = 0xBA;
	kstack[1] = 0xD1;
	kstack[2] = 0xDE;
	kstack[3] = 0xA0;

	/* Eyecatcher */
	int y=0xdeadbeef;

	/* Return the eyecatcher in r15 */
	return y;
}
