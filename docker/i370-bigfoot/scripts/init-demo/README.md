Simple Userspace Demo
---------------------
This requires no C library to run; it illustrates how to make system
calls without a C library. This demo consists of three parts:

* `crtspin.S` -- Provides the code that appears first in the
  `.text` section of the ELF file. It accepts the frame and stack
  pointers provided by the kernel, and converts them into a normal
  C language stack. It also sets up `argc` and `argv`.

* `spin.c` -- Demo application. Opens the console for writing, and
  then prints some messages.

* `spinput.c` -- Demo application. Opens `/dev/tty0` for reading and
  writing, and then echoes what was typed as input.

* `demo-unistd.h` -- System call interface definition. Caution:
  risk of electrical shock. Do not open. No user-servicable parts
  inside.

Compile by saying `make`, then copy to your ramdisk. The demo
requires creating a special file, a character device in the file
system. It can be done like so:

```
cd <root of your ramdisk>
mkdir dev ; cd dev
mknod tty0 4 0
chmod g+w tty0
```
This creates a device `/dev/tty0` which can be written to.
