
#include "demo-unistd.h"

int main(int argc, char* argv)
{
	int i, j;
	int c = argc;
	// char * x = argv[0]; Not today!

	write(1, "Hello\n", 7);

	int buf[1000];
	for (i=0; i<1000; i++) buf[i] = i;

	while (1) {
		for (j=0; j<1000; j++) {
			for (i=0; i<1000; i++)
				buf[i] += buf [(i+1)%1000];
		}
		write(1, "whirl\n", 7);
	}
	return 3;
}
