
all: spin spinput

spin: spin.c demo-unistd.h libc.a
	i370-ibm-linux-gcc -O2 -c spin.c
	i370-ibm-linux-gcc -L . spin.o -o spin

spinput: spinput.c demo-unistd.h libc.a
	i370-ibm-linux-gcc -O2 -c spinput.c
	i370-ibm-linux-gcc -L . spinput.o -o spinput

libc.a:
	i370-ibm-linux-gcc -O2 -c mylibc.c
	i370-ibm-linux-ar r libc.a mylibc.o

clean:
	rm -f *.o libc.a spin spinput
