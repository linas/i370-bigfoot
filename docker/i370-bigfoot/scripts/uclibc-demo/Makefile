
all: uspinecho

INCLUDES=/usr/local/i370-linux-uclibc/usr/include
LIBDIR=/usr/local/i370-linux-uclibc/usr/lib/

uspinecho: uspinecho.c
	i370-ibm-linux-gcc -I $(INCLUDES) -O2 -c uspinecho.c
	i370-ibm-linux-gcc -L $(LIBDIR) uspinecho.o -o uspinecho

clean:
	rm -f *.o uspinecho
