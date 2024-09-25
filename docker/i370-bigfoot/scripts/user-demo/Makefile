

spin: spin.c crtspin.S
	i370-ibm-linux-gcc -c spin.c
	i370-ibm-linux-gcc -c crtspin.S
	i370-ibm-linux-gcc crtspin.o spin.o -o spin -nostdlib

clean:
	rm -f *.o spin
