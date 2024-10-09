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

	printf("Hello, world!\n");

	/* Enter echo loop */
	printf("Type something>\n");
	while (1) {

		char * rv = fgets(inbuf, BUFSZ, stdin);

		if (NULL == rv) {
			printf("Geto EOF, Goodbye!\n");
			break;
		}
		else {
			printf("You did type: %s\n", inbuf);
			printf("Type something>\n");
		}

		delay(2);
	}
	exit (3);
}
