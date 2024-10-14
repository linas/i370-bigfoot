/*
 * Simple i370 Linux Userspace Demo
 *
 * After the Linux kernel boots, the first program it runs is /sbin/init
 * or any other program specifiec by the `init=` argument on the boot
 * command line. This demo can be used as that init.
 *
 * This is a very simple demo, because it assumes that there isn't
 * any C library, and so none of the usual C library routines are
 * available. However, system calls can be made, by including the
 * `demo-unistd.h` include file. It defines just enough for a handful
 * of system calls, including the write() subroutine. This demo
 * makes use of that, to spin in a loop for a while, and then print
 * to the console. This only does output; see the `spinput.c` demo
 * for a version of this that also reads.
 */
#include "demo-unistd.h"

int main(int argc, char* argv[], char* envp[])
{
	int i, j;

	/* Don't forget to mknod and create this device! */
	int ttyfd = open("/dev/console", O_WRONLY, 0);
	write(ttyfd, "Hello\n", 6);

	int buf[1000];
	for (i=0; i<1000; i++) buf[i] = i;

	while (1) {
		for (j=0; j<1000; j++) {
			for (i=0; i<1000; i++)
				buf[i] += buf [(i+1)%1000];
		}
		write(ttyfd, "whirl\n", 6);
	}
	return 3;
}
