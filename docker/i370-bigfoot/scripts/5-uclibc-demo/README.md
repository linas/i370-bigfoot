Userspace with uClibc-ng Demo
-----------------------------
This illustrates how to create a bootable init program using the
uClibc C library.

* `spinecho.c` -- Demo application. Opens `/dev/console` for reading and
  writing, and then echoes what was typed as input.

Compile by saying `make`, then copy to your ramdisk. The demo
requires that the `/dev/console` file exists on the ramdisk, as 
explained in the [linux-demo README](../linux-demo/README.md).
