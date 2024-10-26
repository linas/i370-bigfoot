#
# Build an IPL'able linux image.
#


all: vmlinux.ins ramdisk

vmlinux.ins: vmlinux
	../elf-stripper/elf-stripper vmlinux > vmlinux.bin
	echo "* INS file to load Linux kernel" > vmlinux.ins
	echo "* Format: <file to load> [address where to load]" >> vmlinux.ins
	echo "* The elf-stripped Linux kernel" >> vmlinux.ins
	echo "vmlinux.bin  0x00000000" >> vmlinux.ins
	echo "" >> vmlinux.ins
	echo "* Boot command line" >> vmlinux.ins
	echo -n "cmd_line  0x" >> vmlinux.ins
	i370-ibm-linux-readelf -a vmlinux \
		|grep cmd_line |grep GLOBA | cut -b 9-17 >> vmlinux.ins

ramdisk: vmlinux.ins ram_image.gz
	echo "" >> vmlinux.ins
	echo "* Load RAMDISK at the same address as given in command line" >> vmlinux.ins
	echo "ram_image.gz  0x00200000" >> vmlinux.ins

ram_image.gz:
	dd if=/dev/zero of=disk-image bs=1k count=4096
	/sbin/mke2fs -vm0 -r0 disk-image 4096
	sudo umount -q mnt
	mkdir -p mnt
	sudo mount disk-image mnt
	sudo cp -pr ../root-disk/* mnt
	sudo sh -c 'cd mnt; ./makedev.sh'
	ls -la mnt
	sudo umount mnt
	gzip -c -v9 disk-image > ram_image.gz

clean:

realclean: clean
	rm -f vmlinux vmlinux.bin vmlinux.ins disk-image ram_image.gz
