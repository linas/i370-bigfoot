#
# Makefile for i370 IPL examples

all: elf-stripper kernel-demo

# Build the stripper tool. This is built using the host compiler,
# because this runs on the host.
elf-stripper: elf-stripper.c
	cc $^ -o $@

# Build the bootable kernel demo. This is built using the target
# compiler, because it will run on the Hercules emulator.
# The name of the stripped binary is placed in a file, since
# that is how Hercules wants to find the bootable image.
kernel-demo: ipl-to-c.S kernel-demo.c kernel-demo.lds elf-stripper
	i370-ibm-linux-gcc -c ipl-to-c.S
	i370-ibm-linux-gcc -c kernel-demo.c
	i370-ibm-linux-ld -T kernel-demo.lds ipl-to-c.o kernel-demo.o -o kernel-demo
	./elf-stripper kernel-demo > kernel.bin
	echo "* INS file to load demo" > kernel.ins
	echo "kernel.bin  0x00000000" >> kernel.ins

clean:
	rm -f *.o

realclean: clean
	rm -f elf-stripper
	rm -f kernel-demo kernel.bin kernel.ins
