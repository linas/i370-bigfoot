# Example i370 program

This directory contains an example showing how C code can be compiled
and booted on the Hercules emulator.  It consists of multiple parts:

* `ipl-to-c.S`: Some assembly glue to jump into C code. This installs
  an initial PSW, sets up registers r13 (the stack pointer), r11 (the
  frame pointer) and r14 (the link register). It then calls the C code,
  and, upon return, enters disabled wait.

* `kernel.c`: Example C source code. It cannot do anything fancy,
  because it is not linked to any C library. So all that it does is to
  create a stack (because `ipl-to-c.S` was too lazy to set this up)
  and then return a value to the caller. The returned value will be
  in GPR register 15, and will be visible using the Hercules `gpr`
  command.

* `Makefile`: A makefile to compiler the above two into an i370 ELF
  executable.

* `elf-stripper.c`: Hercules cannot natively IPL ELF code. This is a
  tool that create a "raw" bootable binary from an ELF executable.
  It strips of the ELF headers, so that the binary starts at the
  begining of the `.text` segment. As long as the first 8 bytes of the
  binary contain a (short-format) PSW, the binary will be bootable by
  Hercules.

## Running

Build everything by saying `make`.


So do this ...
