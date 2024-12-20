#
# Build an IPL'able linux image w/ non-trivial root disk.
#

all: vmlinux.ins ramdisk

BASE=/home/bigfoot

vmlinux: date-stamp
	cp ${BASE}/i370-linux-2.2.1/vmlinux .

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

ramdisk: vmlinux.ins ram_image
	echo "" >> vmlinux.ins
	echo "* Load RAMDISK at the same address as given in command line" >> vmlinux.ins
	echo "ram_image  0x00800000" >> vmlinux.ins

ram_image: date-stamp
	dd if=/dev/zero of=disk-image bs=1k count=81920
	/sbin/mke2fs -vm0 -r0 disk-image 81920
	mkdir -p mnt
	-sudo umount -q mnt
	sudo mount -o loop disk-image mnt
	sudo cp -pr big-root-disk/* mnt
	sudo cp -pr /usr/local/i370-linux-uclibc/* mnt
	mkdir -p mnt/sbin
	cp ${BASE}/busybox/busybox mnt/sbin/
	sudo sh -c 'cd mnt; ./makedev.sh'
	ls -la mnt
	sudo umount mnt
	mv disk-image ram_image

clean:

realclean: clean
	rm -f vmlinux vmlinux.bin vmlinux.ins disk-image ram_image
	rmdir mnt
