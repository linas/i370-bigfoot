#
# Build and boot a simple uClibc I/O demo
#
all: boot-uspinecho

INCLUDES=/usr/local/i370-linux-uclibc/usr/include
LIBDIR=/usr/local/i370-linux-uclibc/usr/lib/

uspinecho: uspinecho.c
	i370-ibm-linux-gcc -I $(INCLUDES) -O2 -c uspinecho.c
	i370-ibm-linux-gcc -B $(LIBDIR) -L $(LIBDIR) uspinecho.o -o uspinecho

KERN=../2-linux-demo

boot-uspinecho: uspinecho
	cp uspinecho ../root-disk
	echo 'root=/dev/ram init=/uspinecho i370_initrd=0x800000,4096' > $(KERN)/cmd_line
	touch $(KERN)/date-stamp
	cd $(KERN); make

clean:
	rm -f *.o uspinecho
