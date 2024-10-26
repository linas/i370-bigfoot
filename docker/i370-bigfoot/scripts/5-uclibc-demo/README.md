Userspace with uClibc-ng Demo
-----------------------------
This illustrates how to create a bootable init program using the
uClibc C library.

* `spinecho.c` -- Demo application. Opens `/dev/console` for reading and
  writing, and then echoes what was typed as input.

Compile and create a boot-image by saying `make`. This demo assumes
that the Linux kernel has been built, as described in the
[linux-demo README](../2-linux-demo/README.md), and is bootable.
