
int x=42;

int main(int argc, char* argv)
{
	int i;
	int c = argc;
	x = argv[1];
	int buf[1000];
	for (i=0; i<1000; i++) buf[i] = i;

	while (1) {
		for (i=0; i<1000; i++)
			buf[i] += buf [(i+1)%1000];
	}
	return 3;
}
