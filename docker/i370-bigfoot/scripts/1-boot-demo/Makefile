#
# Makefile for an i370 IPL boot demo.

all: boot-demo

# Build the bootable boot demo. This is built using the target
# compiler, because it will run on the Hercules emulator.
# The name of the stripped binary is placed in a file, since
# that is how Hercules wants to find the bootable image.
boot-demo: ipl-to-c.S boot-demo.c boot-demo.lds
	i370-ibm-linux-gcc -c ipl-to-c.S
	i370-ibm-linux-gcc -c boot-demo.c
	i370-ibm-linux-ld -T boot-demo.lds ipl-to-c.o boot-demo.o -o boot-demo
	../elf-stripper/elf-stripper boot-demo > bootable.bin
	echo "* INS file to load demo" > boot.ins
	echo "* Format: <file to load> [address where to load]" >> boot.ins
	echo "* Multiple lines are allowed" >> boot.ins
	echo "bootable.bin  0x00000000" >> boot.ins

clean:
	rm -f *.o

realclean: clean
	rm -f boot-demo bootable.bin boot.ins
