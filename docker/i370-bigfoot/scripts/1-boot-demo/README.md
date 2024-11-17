# Example of a bootable i370 program

This directory contains an example showing how C code can be compiled
and booted on the Hercules emulator.  It consists of multiple parts:

* `ipl-to-c.S`: Some assembly glue to jump into C code. This installs
  an initial PSW, sets up registers r13 (the stack pointer), r11 (the
  frame pointer) and r14 (the link register). It then calls the C code,
  and, upon return, enters disabled wait.

* `boot-demo.c`: Example C source code. It cannot do anything fancy,
  because it is not linked to any C library. So all that it does is to
  create a stack (because `ipl-to-c.S` was too lazy to set this up)
  and then return a value to the caller. The returned value will be
  in GPR register 15, and will be visible using the Hercules `gpr`
  command.

* `boot-demo.lds`: Example ELF loader script. This places the `.text`
  segment at address zero, so that it will be first, upon creation of
  the bootable image.

* `Makefile`: A makefile to compile the above three into an i370 ELF
  executable.

Note that the program runs in ''real addressing mode'' (because no
page tables or TLB's are set up) and in supervistor mode (so all
privileged instructions are available.) There is no C library, and
so no `printf`s or anything else. No exception handlers are installed,
so it'll all crash if you get an interrupt.

## Running
Steps to running the demo:

* Build everything by saying `make`.
* (Optional) Take a look at the ELF binary:
  `i370-ibm-linux-readelf -a boot-demo`.  Make note of the loadable
  segments.
* (Optional) Disassemble the ELF binary:
  `i370-ibm-linux-objdump -D boot-demo`.  Make note of the various
  symbols and offsets.
* (Optional) Take a look at the raw binary: `xxd bootable.bin | less`
  Notice that the first eight bytes give a PSW that starts running at
  address 0x10 (i.e. 16 bytes in, where the very first instruction appears.)
* Start the Hercules emulator.
* Run the demo by saying `ipl /home/i370-bigfoot/examples/boot.ins`
  at the Hercules prompt. The `boot.ins` file contains the name of
  the actual bootable boot, which is `bootable.bin`.
* The instruction counter should run up to about 50 insns, and then enter
  the disabled wait state. Use `gpr` to view the registers. Note the
  presence of some eyecatchers in `r5` and `r7` (from `ipl-to-c.S`) and
  another in r15 (from `boot-demo.c`). This is the only evidence that
  the code actually ran (because we don't have a `printf` available.)
* Note that `r14` is the link register; it contains the location that
  the C code returns to, after exiting. Compare the value here to that
  visible in `i370-ibm-linux-objdump -D boot-demo`.
* Examine the system RAM. The `r 0.ff` command will show the initial
  PSW, and the text strings before the first executable insn. The first
  insn is `basr 15,0` and its at approx address 0xa4.  The `u a4`
  command will disassemble RAM starting at that address. Another
  interesting location is at 0x180; this is a scratch area used to
  construct the final halt PSW that goes into disabled wait; its the
  one that runs after returning from C. See `SCRATCH` and `HALT` in
  `ipl-to-c.S`. The stackframe can be examined with `r 1000.17f`.
  Note the values 0x33 and 0x44 at 0x1128: these are the arguments
  passed to the called subroutine.  Note assorted saved registers
  in the stackgrame.
* Use `sysclear` to reset the system (if desired). This will clear the
  PSW and the GPRs.

That's all, folks!
Hope you enjoyed the show!
(Cue the Looney Tunes theme music)
