# Compiling and Running under Hercules

Hercules is a System/390 and z/Series emulator. It can run binaries
created for the z/Architecture instruction set.  This README reviews
how to run Hercules, how to create bootable binaries, how to IPL them,
and some basic debugging hints.

## Run Docker
Start your Docker container, if you haven't yet.
```
docker create --name my-mainframe -it bigfoot/i370-bigfoot
docker start -i my-mainframe
```
You'll almost surely want to get multiple command lines in this
container, using `byobu` or `tmux`. Start `byobu` and then hit `PF2`
a couple of times, to create new terminal windows. To rotated between
windows, use `PF3` and `PF4`. Rename windows with `PF8`.

## Start Hercules
In one window, start the Hercules emulator:
```
cd hercules
hercules
```
Attach to the console with telnet. This is where the Linux kernel
will provide a console.  Note the port number is 3270.
```
telnet localhost 3270
```

## Build the elf-stripper tool
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
cd boot-demo
less README.md
```
For more info, see the [boot-demo README](./boot-demo/README.md)

## Boot the Linux kernel
A demo of the Linux kernel is the main point of this project. So here it
is. The Docker container has a kernel, already built, in the
`i370-linux-2.2.1` directory. You can IPL it as follows:
```
   elf-stripper vmlinux > vmlinux.bin
   echo "* INS file to load a Linux OS" > vmlinux.ins
   echo "* Format: <file to load> [address where to load]" >> vmlinux.ins
   echo "* Multiple lines are allowed" >> vmlinux.ins
   echo "vmlinux.bin  0x00000000" >> vmlinux.ins
```
Then, in the Hercules emulator:
```
ipl vmlinux.ins
```
The above will boot, but then kernel panic, since no root file system
was provided. See the [linux-demo README](./linux-demo/README.md) for
details on creating a basic file system.

## (optional) Build and run the init demo
Even with a root file system, the Linux kernel won't do anything
interesting without some kind of `/sbin/init`. This is the very
first program that runs, after the Linux kernel is booted. This
demo provides a simple C program that write to the system console.
Because there is no C library (yet), the system call interfaces
are minimalistic. In the demo, just enough to write to the screen.

For more info, see the [init-demo README](../init-demo/README.md)

## (optional) Build and run the PDPCLIB demo
The PDPCLIB is a Public Domain C Library. It provides enough to be able
to do "real C programming". The demo creates a bootable init binary
that simply reads input and echoes it to output, using `fread` and
`fprintf`.

For more info, see the [pdpclib-demo README](../pdpclib-demo/README.md)

## Notes

### Latest Hercules
The currently installed version of Hercules is version 3.15, which is
the latest available in Debian. There is something newer, though:
Hercules Hyperion aka Hercules/390 aka hercules version 4.0
It supposedly fixes many issues.  Also, it has a better web page:

[Hercules 390 version 4](http://hercules-390.github.io/html/)

### Debug
Activate CCW tracing on device 001F (this is where the 3215 is)
```
t+1f
```

----------
