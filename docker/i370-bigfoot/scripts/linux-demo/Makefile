#
# Build an IPL'able linux image.

all: vmlinux.ins

vmlinux.ins: vmlinux
	../elf-stripper/elf-stripper vmlinux > vmlinux.bin
	echo "* INS file to load Linux kernel" > vmlinux.ins
	echo "* Format: <file to load> [address where to load]" >> vmlinux.ins
	echo "* Multiple lines are allowed" >> vmlinux.ins
	echo "vmlinux.bin  0x00000000" >> vmlinux.ins

clean:

realclean: clean
	rm -f vmlinux vmlinux.bin vmlinux.ins
