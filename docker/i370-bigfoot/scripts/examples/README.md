# Example i370 program

This directory contains an example showing how C code can be compiled
and booted on the Hercules emulator.  It consists of multiple parts:

* `ipl-to-c.S`: Some assembly glue to jump into C code. This installs
  an initial PSW, sets up registers r13 (the stack pointer), r11 (the
  frame pointer) and r14 (the link register). It then calls the C code,
  and, upon return, enters disabled wait.

* `kernel-demo.c`: Example C source code. It cannot do anything fancy,
  because it is not linked to any C library. So all that it does is to
  create a stack (because `ipl-to-c.S` was too lazy to set this up)
  and then return a value to the caller. The returned value will be
  in GPR register 15, and will be visible using the Hercules `gpr`
  command.

* `kernel-demo.lds`: Example ELF loader script. This places the `.text`
  segment at address zero, so that it will be first, upon creation of
  the bootable image.

* `Makefile`: A makefile to compiler the above two into an i370 ELF
  executable.

* `elf-stripper.c`: Hercules cannot natively IPL ELF code. This is a
  tool that create a "raw" bootable binary from an ELF executable.
  It strips of the ELF headers, so that the binary starts at the
  begining of the `.text` segment. As long as the first 8 bytes of the
  binary contain a (short-format) PSW, the binary will be bootable by
  Hercules.

## Running
Steps to running the demo:

* Build everything by saying `make`.
* (Optional) Take a look at the ELF binary:
  `i370-ibm-linux-readelf -a kernel-demo`.  Make note of the loadable
  segmenets.
* (Optional) Disassemble the ELF binary:
  `i370-ibm-linux-objdump -D kernel-demo`.  Make note of the various
  symbols and offsets.
* (Optional) Take a look at the raw binary: `xxd kernel.bin | less`
  Notice that the first eight bytes give a PSW that starts running at
  adress 0x10 (i.e. 16 bytes in, where the very first instruction appears.)
* Start the Hercules emulator.
* Run the demo by saying `ipl /home/i370-bigfoot/examples/kernel.ipl`
  at the Hercules prompt. The `kernel.ipl` file contains the name of
  the actual bootable kernel, which is `kernel.bin`.
* The instruction counter should run up to about 27 insns, and then enter
  the disabled wait state. Use `gpr` to view the registers. Note the
  presence of some eyecatchers in `r5` and `r7` (from `ipl-to-c.S`) and
  another in r15 (from `kernel-demo.c`). This is the only evidence that
  the code actually ran (because we don't have a `printf` available.)
* Note that `r14` is the link register; it contains the location that
  the C code returns to, after exiting. Comare the value here to that
  visible in `i370-ibm-linux-objdump -D kernel-demo`.
* Examine the system RAM. The `u 10` command will disassemble RAM starting
  at hex address 0x10. The `r 180` will show RAM at location 0x180; this
  particular location was used to assemble the PSW after returning from C.
  Look at `SCRATCH` and `HALT` in `ipl-to-c.S`. View the stackframe with
  `r 1000.17f`.  Note the values 0x33 and 0x44 at 0x1128: these are the
  arguments passed to the called subroutine.  Note assorted saved registers
  in the stackgrame.
* Use `sysclear` to reset the system (if desired). This will clear the
  PSW and the GPRs.

That's all, folks!
Hope you enjoyed the show!
(Cue the Looney Tunes theme music)
