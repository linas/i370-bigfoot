#
# Build an IPL'able linux image plus root disk.
#
# The root disk-image address specified in the INS file *must* match
# the address given to the Linux kernel in the `cmd_line`. Otherwise,
# the kernel can't find it.
#
# Both the gzipped and the non-gzipped root disks work. There does not
# seem to be any speed advantange from using the the gzipped version.

all: vmlinux.ins disk-image

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
	echo "" >> vmlinux.ins
	echo "* Load RAMDISK at the same address as given in command line" >> vmlinux.ins
	echo "disk-image  0x00800000" >> vmlinux.ins

#	echo "ram_image.gz  0x00800000" >> vmlinux.ins

disk-image: date-stamp
	dd if=/dev/zero of=disk-image bs=1k count=4096
	/sbin/mke2fs -vm0 -r0 disk-image 4096
	mkdir -p mnt
	-sudo umount -q mnt
	sudo mount -o loop disk-image mnt
	sudo cp -pr ../root-disk/* mnt
	sudo sh -c 'cd mnt; ./makedev.sh'
	ls -la mnt
	sudo umount mnt

ram_image.gz: disk-image
	gzip -c -v9 disk-image > ram_image.gz

clean:

realclean: clean
	rm -f vmlinux vmlinux.bin vmlinux.ins disk-image ram_image.gz
	rmdir mnt
