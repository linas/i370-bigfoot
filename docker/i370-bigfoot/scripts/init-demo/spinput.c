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

int strlen(char *str) {
	int i=0;
	while (0 != str[i]) i++;
	return i;
}

int main(int argc, char* argv[], char* envp[])
{
	int rc;
	int i, j;

	/* Keyboard input data */
#define BUFSZ 120
	char inbuf[BUFSZ];

	/* Don't forget to mknod and create this device! */
	/* Several choices here. The first non-console 3215 is
	 * mapped to /dev/3270/raw0. The console itself maps
	 * to /dev/console. To use it with Hercules, you must
	 * change the Hercules config to telnet into this.
	 */
	// int ttyfd = open("/dev/3270/raw0", O_RDWR|O_NONBLOCK, 0);
	int ttyfd = open("/dev/console", O_RDWR|O_NONBLOCK, 0);
	write(ttyfd, "Hello there\n", 13);

	write(ttyfd, "argc=", 6);
	char nstr[3];
	nstr[0] = '0' + argc;
	nstr[1] = '\n';
	nstr[2] = 0;
	write(ttyfd, nstr, 3);

	int data[1000];
	for (i=0; i<1000; i++) data[i] = i;

	while (1) {
		/* Waste some CPU cycles */
		for (j=0; j<3000; j++) {
			for (i=0; i<1000; i++)
				data[i] += data [(i+1)%1000];
		}

		rc = read(ttyfd, inbuf, BUFSZ);

		// if (-EAGAIN == rc)
		// 	write(ttyfd, "No input\n", 10);
		if (rc < 0 && -EAGAIN != rc)
			write(ttyfd, "Input error\n", 13);
		else if (0 < rc) {
			write(ttyfd, "You typed: ", 12);
			write(ttyfd, inbuf, rc);
			write(ttyfd, "\n", 2);
		}

		write(ttyfd, "Type something\n", 16);
	}
	return 3;
}
