# Compiling and Running Demos
This container contains all the tools needed for creating an i370 Linux
kernel, creating a bootable root disk, and creating i370 executables
that run with this kernel. There are two options for actually running
these:
* Copy them out of this container, and run them on a VM session
  on actual System/390 hardware (should also work on z/Series.)
* Run the Hercules emulator.

Hercules is a System/390 and z/Series emulator. It can run binaries
created for the z/Architecture instruction set.  This README reviews
how to run Hercules, how to create bootable binaries, how to IPL them,
and some basic debugging hints.

## Run Docker
Start your Docker container, if you haven't yet.
```
   docker create --privileged=true --name my-mainframe -it bigfoot/i370-bigfoot
   docker start -i my-mainframe
```
The `--privileged=true` is required so that the `mount` command can be
used to create root-disks.

## Run byobu or tmux
You'll almost surely want to get multiple command lines in this
container, using `byobu` or `tmux`. Start `byobu` and then hit `PF2`
three or four times, to create new terminal windows. To rotate between
windows, use `PF3` and `PF4`. Rename windows with `PF8`.

To scroll up and see old window history, use `PF7`. After this, the
page-up and page-down keys will work.

To close windows, hit ctrl-D. Exit hercules with `quit`.

## Start Hercules
In one window, start the Hercules emulator:
```
   hercules -f hercules/hercules.cnf
```
In another window, attach to the console with telnet. (Use pf3/pf4 to
rotate to another window.) The console is where the Linux kernel will
type output and accept keyboard input.  Note the port number is 3270.
```
   telnet localhost 3270
```

The telnet menu cn be accessed at any time with ctrl-]. That's
ctrl-close-square-bracket.

## Build the elf-stripper tool
In a third window, build the elf-stripper tool. This is needed by all
demos. It converts i370 ELF binaries into binaries that can be IPL'ed.
```
   cd elf-stripper
   make
   cd ..
```

## (optional) Build and run the boot demo
The boot demo creates a very simple program, written in C, that can
be IPL'ed on Hercules. Since there is no operating system, it can't
actually read the keyboard or write to the console. However, you can
see that it actually ran, by examining memory.

In another window, compile and build the boot demo:
```
   cd 1-boot-demo
   less README.md
```
For more info, see the [boot-demo README](./1-boot-demo/README.md)

## Boot the Linux kernel
A demo of the Linux kernel is the main point of this project. So here it
is. The Docker container has a kernel, already built, in the
`i370-linux-2.2.1` directory. You can IPL it as follows:
```
   cd 2-linux-demo
   cp ../i370-linux-2.2.1/vmlinux .
   elf-stripper vmlinux > vmlinux.bin
   echo "* INS file to load a Linux OS" > vmlinux.ins
   echo "* Format: <file to load> [address where to load]" >> vmlinux.ins
   echo "* Multiple lines are allowed" >> vmlinux.ins
   echo "vmlinux.bin  0x00000000" >> vmlinux.ins
```
Then, in the Hercules emulator:
```
   ipl 2-linux-demo/vmlinux.ins
```
The above will boot, but then kernel panic, since no root file system
was provided. See the [2-linux-demo README](./2-linux-demo/README.md) for
details on creating a basic file system.

## (optional) Build and run the init demo
Even with a root file system, the Linux kernel won't do anything
interesting without some kind of `/sbin/init`. This is the very
first program that runs, after the Linux kernel is booted. This
demo provides a simple C program that writes to the system console.
Because there is no C library (yet), the system call interfaces
are minimalistic. In the demo, just enough to write to the screen.

For more info, see the [3-init-demo README](../3-init-demo/README.md)

## (optional) Build and run the PDPCLIB demo
The PDPCLIB is a Public Domain C Library. It provides a standard
but minimalist C90 library, just barely enough to be able to do
"real C programming". It offers just strict C90; it does not have
any POSIX support (and thus cannot be used to compile conventional
unix binaries.) The demo creates a bootable init binary that simply
reads input and echoes it to output, using `fgets` and `printf`.

For more info, see the [4-pdpclib-demo README](../4-pdpclib-demo/README.md)

## (optional) Build and run the uClibc demo
The uClibc-ng is an LGPL'ed C Library tailored for microcontrollers
running Linux. It's quite sophisticated, its very configurable, its easy
to port. It's derived from glibc, but omits some of the more opaque
and obscure corners (like C++ exception unwinding?? Perhaps symbol
versioning? I dunno, things you won't normally need, unless you are
going to run sophisticated server software stacks.).  The demo creates
a bootable init binary that simply reads input and echoes it to output,
using `fgets` and `printf`.

For more info, see the [5-uclibc-demo README](../5-uclibc-demo/README.md)

## (optional) Build and run the BusyBox demo
BusyBox is collection of basic OS tools, together with several shells.
Any one of the offered shells can be used in place of `/sbin/init`,
and thus offers an interactive command environment hosting many
conventional unix commands.

For more info, see the [6-busybox-demo README](../6-busybox-demo/README.md)

## (optional) Build and run the native demo
This is a root disk that contains the compiler and assembler, and can
be used to build additional tools natively, on the i370.

For more info, see the [7-native-demo README](../7-native-demo/README.md)

## Notes

### Latest Hercules
The currently installed version of Hercules is version 3.15, which is
the latest available in Debian. There is something newer, though:
Hercules Hyperion aka Hercules/390 aka hercules version 4.0
It supposedly fixes many issues.  Also, it has a better web page:

[Hercules 390 version 4](http://hercules-390.github.io/html/)

It's not available on Debian, so its not installed here.

There is also a version of Hercules from Paul Edwards, which includes a
character-mode variant of the 3215 device. The patches for this device
seem not to be included in either of the above.

### Documentation
* The [SA22-7201-08.pdf](SA22-7201-08.pdf) is a copy of the Enterprise
  Systems Architecture/390 Principles of Operation, Ninth Edition,
  June 2003

* The [System 370 Reference Summary](System_370_Reference_Summary.pdf)
  is a condensed short form of the above.

### Debug
Activate CCW tracing on device 001F (this is where the 3215 is)
```
t+1f
```

----------
