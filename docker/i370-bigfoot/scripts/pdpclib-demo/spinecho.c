/*
 * Simple i370 PDPCLIB Console I/O Demo
 *
 * After the Linux kernel boots, the first program it runs is /sbin/init
 * or any other program specifiec by the `init=` argument on the boot
 * command line. This demo can be used as that init.
 *
 * This demos linking to PDPCLIB, the Public Domain C Library.
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

// PDPCLIB currently does not define this ...
#define O_WRONLY 2

/* Since we are not being called from a shell, the stdio endpoints
 * don't exist. Create them now. We will do I/O to the console, for
 * this particular demo. The system calls are those supplied by
 * PDPCLIB.
 */
void setup_stdio(void)
{
	int confd = __open("/dev/console", O_WRONLY, 0);
	__dup2(confd, 0); /* stdin */
	__dup2(confd, 1); /* stdout */
	__dup2(confd, 2); /* stderr */
}

int main(int argc, char** argv, char** envp)
{
	size_t rlen;

	/* Keyboard input data */
#define BUFSZ 120
	char inbuf[BUFSZ];

	/* Only we know where we want to write. So set yp out own stdout */
	setup_stdio();

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
