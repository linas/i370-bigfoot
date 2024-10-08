
all: spinecho

PDPCLIBDIR=/home/bigfoot/pdos-gitcode/pdpclib
PDPCLIBDIR=/home/linas/src/bigfoot-2024/pdos-gitcode/pdpclib

INCLUDES=$(PDPCLIBDIR)
LIBDIR=$(PDPCLIBDIR)

spinecho: spinecho.c
	i370-ibm-linux-gcc -I $(INCLUDES) -O2 -c spinecho.c
	i370-ibm-linux-gcc -L $(LIBDIR) spinecho.o $(LIBDIR)/pdpclib.a -o spinecho -nostdlib --entry __crt0

clean:
	rm -f *.o spinecho
