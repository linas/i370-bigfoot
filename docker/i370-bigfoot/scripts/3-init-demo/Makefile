
all: spin spinput

spin: spin.c demo-unistd.h libc.a
	i370-ibm-linux-gcc -O2 -c spin.c
	i370-ibm-linux-gcc -L . spin.o -o spin

spinput: spinput.c demo-unistd.h libc.a
	i370-ibm-linux-gcc -O2 -c spinput.c
	i370-ibm-linux-gcc -L . spinput.o -o spinput

libc.a: demo-unistd.h
	i370-ibm-linux-gcc -O2 -c mylibc.c
	i370-ibm-linux-ar r libc.a mylibc.o

boot-spin: spin
	cp spin ../root-disk
	echo 'root=/dev/ram i370_initrd=0x200000,4096 init=/spin' > ../2-linux-demo/cmd_line
	cd ../2-linux-demo; make

boot-spinput: spinput
	cp spinput ../root-disk
	echo 'root=/dev/ram i370_initrd=0x200000,4096 init=/spinput' > ../2-linux-demo/cmd_line
	cd ../2-linux-demo; make



clean:
	rm -f *.o libc.a spin spinput
