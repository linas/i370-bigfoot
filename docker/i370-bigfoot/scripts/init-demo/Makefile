
all: spin spinput

spin: spin.c crtspin.o demo-unistd.h
	i370-ibm-linux-gcc -c spin.c
	i370-ibm-linux-gcc crtspin.o spin.o -o spin -nostdlib

spinput: spinput.c crtspin.o demo-unistd.h
	i370-ibm-linux-gcc -c spinput.c
	i370-ibm-linux-gcc crtspin.o spinput.o -o spinput -nostdlib

crtspin.o: crtspin.S
	i370-ibm-linux-gcc -c crtspin.S

clean:
	rm -f *.o spin
