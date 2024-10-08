/*
 * Simple i370 Linux Userspace Console I/O Demo
 *
 * After the Linux kernel boots, the first program it runs is /sbin/init
 * or any other program specifiec by the `init=` argument on the boot
 * command line. This demo can be used as that init.
 *
 * Keep in mind that the 3215 console is line-oriented, not character
 * oriented. There is no input, until carriage return is pressed!
 */

// #include <errno.h>
#include <stdio.h>

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
	size_t rlen;

	/* Keyboard input data */
#define BUFSZ 120
	char inbuf[BUFSZ];

	/* Don't forget to mknod and create this device! */
	/* Several choices here. The first non-console 3215 is
	 * mapped to /dev/3270/raw0. The console itself maps
	 * to /dev/console. To use it with Hercules, you must
	 * change the Hercules config to telnet into this.
	 */
	// FILE *fh = fopen("/dev/3270/raw0", "rw");
	FILE *fh = fopen("/dev/console", "rw");

	fprintf(fh, "Hello, world!\n");

	/* Enter echo loop */
	fprintf(fh, "Type something>\n");
	while (1) {

		rlen = fread(inbuf, BUFSZ, 1, fh);

		if (rlen <= 0) {
			fprintf(fh, "Input error\n");
		}
		else {
			fprintf(fh, "You did type: %s\n", inbuf);
			fprintf(fh, "Type something>\n");
		}

		delay(2);
	}
	exit (3);
}
