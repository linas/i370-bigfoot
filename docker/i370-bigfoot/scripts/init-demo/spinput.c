/*
 * Simple i370 Linux Userspace Console I/O Demo
 *
 * After the Linux kernel boots, the first program it runs is /sbin/init
 * or any other program specifiec by the `init=` argument on the boot
 * command line. This demo can be used as that init.
 *
 * This is a cluttered demo, because it assumes that there isn't
 * any C library, and so none of the usual C library routines are
 * available. However, system calls can be made, by including the
 * `demo-unistd.h` header file. It defines just enough for a handful
 * of system calls, including the read() and write() subroutines. This
 * demo makes use of that, to attempt to read from a device, and then
 * echo what ir read.
 *
 * Keep in mind that the 3215 console is line-oriented, not character
 * oriented. There is no input, until carriage return is pressed!
 *
 * See the `spin.c` demo for a simpler version, that only writes.
 */
#include "demo-unistd.h"

/* Poor man's strlen */
int strlen(char *str) {
	int i=0;
	while (0 != str[i]) i++;
	return i;
}

/* Print a single number. Useful for debugging */
void prtnum(int ttyfd, int x)
{
	int i;
	char nstr[10];
	for(i=0; i<8; i++) {
		char b = (x & 0xf);
		nstr[7-i] = b + (b>9 ? 'a'-10 : '0');
		x = (x >> 4);
	}
	nstr[8] = '\n';
	nstr[9] = 0;
	write(ttyfd, nstr, 10);
}

/* Busy-wait loop */
void delay(int n)
{
	int i, j;
	int data[1000];
	for (i=0; i<1000; i++) data[i] = i;

	/* Waste some CPU cycles */
	for (j=0; j< n*1000; j++) {
		for (i=0; i<1000; i++)
			data[i] += data [(i+1)%1000];
	}
}

int main(int argc, char** argv, char** envp)
{
	int rc;

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
	write(ttyfd, "Hello there!\n", 14);

	/* Print argc */
	write(ttyfd, "argc=", 6);
	char nstr[3];
	nstr[0] = '0' + argc;
	nstr[1] = '\n';
	nstr[2] = 0;
	write(ttyfd, nstr, 3);
	write(ttyfd, "\n", 2);

	/* Print argv */
	write(ttyfd, "argv=\n", 7);
	while (*argv)
	{
		char *ep = *argv;
		int slen = strlen(ep);
		write(ttyfd, ep, slen+1);

		nstr[0] = '\n';
		nstr[1] = 0;
		write(ttyfd, nstr, 2);

		argv++;
	}
	write(ttyfd, "\n", 2);

	/* Print envp */
	write(ttyfd, "envp=\n", 7);
	while (*envp)
	{
		char *ep = *envp;
		int slen = strlen(ep);
		write(ttyfd, ep, slen+1);

		nstr[0] = '\n';
		nstr[1] = 0;
		write(ttyfd, nstr, 2);

		envp++;
	}
	write(ttyfd, "\n", 2);

	/* Enter echo loop */
	write(ttyfd, "Type something>\n", 17);
	while (1) {

		rc = read(ttyfd, inbuf, BUFSZ);

		// if (-EAGAIN == rc)
		// 	write(ttyfd, "No input\n", 10);
		if (rc < 0 && -EAGAIN != rc) {
			write(ttyfd, "Input error; rc=", 15);
			prtnum(ttyfd, rc);
			write(ttyfd, "Type something>\n", 17);
		}
		else if (0 < rc) {
			write(ttyfd, "You typed: ", 12);
			write(ttyfd, inbuf, rc);
			write(ttyfd, "\n", 2);
			write(ttyfd, "Type something>\n", 17);
		}

		delay(2);
	}
	return 3;
}
