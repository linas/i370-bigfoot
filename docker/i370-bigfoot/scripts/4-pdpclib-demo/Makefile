
all: boot-spinecho

PDPCLIBDIR=/home/bigfoot/pdos-gitcode/pdpclib
PDPCLIBDIR=/home/linas/src/bigfoot-2024/pdos-gitcode/pdpclib

INCLUDES=$(PDPCLIBDIR)
LIBDIR=$(PDPCLIBDIR)

spinecho: spinecho.c
	i370-ibm-linux-gcc -I $(INCLUDES) -O2 -c spinecho.c
	i370-ibm-linux-gcc -L $(LIBDIR) spinecho.o -o spinecho

KERN=../2-linux-demo

boot-spinecho: spinecho
	cp spinecho ../root-disk
	echo 'root=/dev/ram init=/spinecho i370_initrd=0x200000,4096' > $(KERN)/cmd_line
	touch $(KERN)/date-stamp
	cd $(KERN); make

clean:
	rm -f *.o spinecho
