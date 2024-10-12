/*
 * Simple i370 uClibc Console I/O Demo
 *
 * After the Linux kernel boots, the first program it runs is /sbin/init
 * or any other program specifiec by the `init=` argument on the boot
 * command line. This demo can be used as that init.
 *
 * This demos linking to uClibc, the LGPL'ed microcontroller C Library.
 */

// #include <errno.h>
#include <fcntl.h>
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

/* Since we are not being called from a shell, the stdio endpoints
 * don't exist. Create them now. We will do I/O to the console, for
 * this particular demo. The system calls are those supplied by
 * PDPCLIB.
 */
void setup_stdio(void)
{
	int confd = open("/dev/console", O_WRONLY, 0);
}

int main(int argc, char** argv, char** envp)
{
	int i;
	size_t rlen;

	/* Keyboard input data */
#define BUFSZ 120
	char inbuf[BUFSZ];

	/* Only we know where we want to write. So set yp out own stdout */
	setup_stdio();

	printf("Hello, world!\n");
	printf("argc = %d\n", argc);
	for (i=0; i<argc; i++)
		printf("argv[%d] = \"%s\"\n", i, argv[i]);

	i = 0;
	while (envp[i]) {
		printf("envp[%d] = \"%s\"\n", i, envp[i]);
		i++;
	}

	/* Enter echo loop */
	printf("Type something>\n");
	while (1) {

		char * rv = fgets(inbuf, BUFSZ, stdin);

		if (NULL == rv) {
			printf("Got EOF, Goodbye!\n");
			break;
		}
		else if (0 == inbuf[0]) {
			/* Currently, fgets() in PDPCLIB is non-blocking;
			   it just returns an empty buffer. Do nothing,
			   just ignore this case. */
		}
		else {
			printf("You did type: %s\n", inbuf);
			printf("Type something>\n");
		}

		delay(2);
	}
	exit (3);
}
