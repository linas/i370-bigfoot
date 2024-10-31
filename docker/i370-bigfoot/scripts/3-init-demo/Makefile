#
# Build and boot the simple raw I/O demo
#
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

KERN=../2-linux-demo

boot-spin: spin
	cp spin ../root-disk
	echo 'root=/dev/ram init=/spin i370_initrd=0x800000,4096' > $(KERN)/cmd_line
	touch $(KERN)/date-stamp
	cd $(KERN); make

boot-spinput: spinput
	cp spinput ../root-disk
	echo 'root=/dev/ram init=/spinput i370_initrd=0x800000,4096' > $(KERN)/cmd_line
	touch $(KERN)/date-stamp
	cd $(KERN); make


clean:
	rm -f *.o libc.a spin spinput
