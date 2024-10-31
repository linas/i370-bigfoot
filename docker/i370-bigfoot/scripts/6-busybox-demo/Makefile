#
# Boot the BusyBox ash shell.
#
all: boot-busybox

KERN=../2-linux-demo

boot-busybox:
	cp ../busybox/busybox  ../root-disk
	echo 'root=/dev/ram init=/busybox ash -i i370_initrd=0x800000,4096' > $(KERN)/cmd_line
	touch $(KERN)/date-stamp
	cd $(KERN); make

clean:

realclean:
