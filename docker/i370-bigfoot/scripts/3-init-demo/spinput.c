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
void prtnum(int confd, int x)
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
	write(confd, nstr, 10);
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
	 *
	 * When opened in non-blocking mode, we can poll for input,
	 * the 3215 driver behaves kind of strangely for this case.
	 */
	// int confd = open("/dev/3270/raw0", O_RDWR|O_NONBLOCK, 0);
	// int confd = open("/dev/console", O_RDWR|O_NONBLOCK, 0);
	int confd = open("/dev/console", O_RDWR, 0);
	write(confd, "Hello there!\n", 13);

	/* Print argc */
	write(confd, "argc=", 5);
	char nstr[3];
	nstr[0] = '0' + argc;
	nstr[1] = '\n';
	nstr[2] = 0;
	write(confd, nstr, 2);
	write(confd, "\n", 1);

	/* Print argv */
	write(confd, "argv=\n", 6);
	while (*argv)
	{
		char *ep = *argv;
		int slen = strlen(ep);
		write(confd, ep, slen);

		nstr[0] = '\n';
		nstr[1] = 0;
		write(confd, nstr, 1);

		argv++;
	}
	write(confd, "\n", 1);

	/* Print envp */
	write(confd, "envp=\n", 6);
	while (*envp)
	{
		char *ep = *envp;
		int slen = strlen(ep);
		write(confd, ep, slen);
		write(confd, "\n", 1);
		envp++;
	}
	write(confd, "\n", 1);

	/* Enter echo loop */
	write(confd, "Type something>\n", 16);
	while (1) {

		rc = read(confd, inbuf, BUFSZ);

		if (-EAGAIN == rc) {
			write(confd, "Polling for input, type something>\n", 35);
		}
		else if (rc < 0 ) {
			write(confd, "Input error; rc=", 16);
			prtnum(confd, -rc);
			write(confd, "Type something>\n", 16);
		}
		else if (0 < rc) {
			write(confd, "You typed: ", 11);
			write(confd, inbuf, rc);
			write(confd, "\n", 1);
			write(confd, "Type something>\n", 16);
		}

		delay(2);
	}
	return 3;
}
