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

## Build examples
In another window, compile and build one of the examples:
```
cd examples
less README.md
```
## IPL examples
Go back to the hercules window, and IPL the example:
```
IPL ../examples/demo.ins
```

For more info, see the [examples README](../examples/README.md)

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
