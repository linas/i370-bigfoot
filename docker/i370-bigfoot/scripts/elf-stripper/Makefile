#
# Makefile for the i370 IPL elf-stripper tool.
#
# This tool strips out the ELF header from an ELF executable,
# thus creating a binary that can be IPL'ed on Hercules.

all: elf-stripper

# Build the stripper tool. This is built using the host compiler,
# because this runs on the host.
elf-stripper: elf-stripper.c
	cc $^ -o $@

clean:
	rm -f *.o

realclean: clean
	rm -f elf-stripper
