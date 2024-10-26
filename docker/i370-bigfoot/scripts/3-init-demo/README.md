Simple Userspace Demo
---------------------
This requires no C library to run; it illustrates how to make system
calls without a C library. This demo consists of three parts:

* `spin.c` -- Demo application. Opens the console for writing, and
  then prints some messages.

* `spinput.c` -- Demo application. Opens `/dev/console` for reading and
  writing, and then echoes what was typed as input.

* `demo-unistd.h` -- System call interface definition. Caution:
  risk of electrical shock. Do not open. No user-servicable parts
  inside.

Compile by saying `make`, then copy to your ramdisk. This demo
assumes that the Linux kernel has been built, as described in
the [linux-demo README](../2-linux-demo/README.md), and is bootable.

The creation of the ramdisk  is automated with `make boot-spin` or
`make boot-spinput`. This will copy one or the other binaries to the
root disk, and create a new bootable image. That image can be IPL'ed
with `ipl vmlinux.ins` (from the ins file in the Linux demo directory).
