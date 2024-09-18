#
# Makefile for i370 IPL examples

all: elf-stripper kernel-demo kernel-alt

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
	echo "kernel.bin" > kernel.ipl

# Same as above, but works without the linker spec `kernel-demo.lds`
kernel-alt: ipl-to-c.S kernel-demo.c kernel-demo.lds elf-stripper
	i370-ibm-linux-gcc -c ipl-to-c.S
	i370-ibm-linux-gcc -c kernel-demo.c
	i370-ibm-linux-ld ipl-to-c.o kernel-demo.o -o kalt-demo
	./elf-stripper kalt-demo > kalt.bin
	echo "kalt.bin" > kalt.ipl

clean:
	rm -f *.o

realclean: clean
	rm -f elf-stripper
	rm -f kernel-demo
