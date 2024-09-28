/*
 * Simple i370 Linux Userspace Console I/O Demo
 *
 * After the Linux kernel boots, the first program it runs is /sbin/init
 * or any other program specifiec by the `init=` argument on the boot
 * command line. This demo can be used as that init.
 *
 * This is a very simple demo, because it assumes that there isn't
 * any C library, and so none of the usual C library routines are
 * available. However, system calls can be made, by including the
 * `demo-unistd.h` include file. It defines just enough for a handful
 * of system calls, including the read() and write() subroutines. This
 * demo makes use of that, to spin in a loop for a while, attempt to
 * read from the tty, and then echo that back out.
 *
 * See the `spin.c` demo for a simpler version, that only writes.
 */
#include "demo-unistd.h"

int main(int argc, char* argv)
{
	int rc;
	int i, j;

	/* Keyboard input data */
#define BUFSZ 120
	char inbuf[BUFSZ];

	/* Don't forget to mknod and create this device! */
	int ttyfd = open("/dev/3270/tty0", O_RDWR|O_NONBLOCK, 0);
	write(ttyfd, "Hello there\n", 13);

	int data[1000];
	for (i=0; i<1000; i++) data[i] = i;

	while (1) {
		/* Waste some CPU cycles */
		for (j=0; j<1000; j++) {
			for (i=0; i<1000; i++)
				data[i] += data [(i+1)%1000];
		}

		rc = read(ttyfd, inbuf, BUFSZ);

		// if (-EAGAIN == rc)
		// 	write(ttyfd, "No input\n", 10);
		if (rc < 0 && -EAGAIN != rc)
			write(ttyfd, "Input error\n", 13);

		write(ttyfd, "Type something\n", 16);
	}
	return 3;
}
