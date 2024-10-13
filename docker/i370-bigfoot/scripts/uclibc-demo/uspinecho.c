/*
 * Simple i370 uClibc Console I/O Demo
 *
 * After the Linux kernel boots, the first program it runs is /sbin/init
 * or any other program specifiec by the `init=` argument on the boot
 * command line. This demo can be used as that init.
 *
 * This demos linking to uClibc, the LGPL'ed microcontroller C Library.
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv, char** envp)
{
	int i;
	size_t rlen;

	/* Keyboard input data */
#define BUFSZ 120
	char inbuf[BUFSZ];

	/* uClibc opens /dev/console for stdin, stdout, stderrr */
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
			printf("well hell Got EOF, Goodbye!\n");
			break;
		}
		else if (0 == inbuf[0]) {
			/* Currently, fgets() is non-blocking (3215 driver bug);
			   it just returns an empty buffer. Do nothing,
			   just ignore this case. */
		}
		else {
			printf("You did type: %s\n", inbuf);
			printf("Type something>\n");
		}

		/* Tenth of a second. */
		usleep(100000);
	}
	sleep(3);
	exit (3);
}
