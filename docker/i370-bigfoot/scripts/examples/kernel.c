
/* Defines some stack space */
char stack[4096];

char *init_ksp = stack;

int start_kernel()
{
	int y=0xdeadbeef;

	return y;
}
