# i370 IPL elf-stripper tool

Hercules cannot natively IPL ELF executables. The `elf-stripper` is a
(very primitive) tool that creates a "raw" bootable binary from an ELF
executable, by stripping out the ELF headers. As a result, the binary
starts at the beginning of the `.text` section. As long as the first
8 bytes of the binary contain a (short-format) PSW, the binary will be
bootable by Hercules.

Build this tool by saying `make`. Note this tool runs on the host
system, and is built with the host compiler; it is NOT an i370 program!

Sample usage:
```
   ./elf-stripper vmlinux > vmlinux.bin
   echo "* INS file to load a Linux OS" > vmlinux.ins
   echo "* Format: <file to load> [address where to load]" >> vmlinux.ins
   echo "* Multiple lines are allowed" >> vmlinux.ins
   echo "vmlinux.bin  0x00000000" >> vmlinux.ins
```
