
all: uspinecho

INCLUDES=
LIBDIR=

uspinecho: uspinecho.c
	i370-ibm-linux-gcc -I $(INCLUDES) -O2 -c uspinecho.c
	i370-ibm-linux-gcc -L $(LIBDIR) uspinecho.o -o uspinecho

clean:
	rm -f *.o uspinecho
