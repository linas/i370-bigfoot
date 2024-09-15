# Compiling and Running under Hercules

Hercules is a System/390 and z/Series emulator. It can run binaries
created for the z/Architecture instruction set.  This README explains
how to create such binaries, and IPL them.

Start your Docker container, if you haven't yet.
```
docker create --name my-mainframe -it bigfoot/i370-bigfoot
docker start -i my-mainframe
```
You'll almost surely want to get multiple command lines in this
container, using `byobu` or `tmux`. Start `byobu` and then hit `PF2`
a couple of times, to create new terminal windows. To rotated between
windows, use `PF3` and `PF4`. Rename windows with `PF8`.

In one window, start the Hercules emulator:
```
cd hercules
hercules
```

In another window, compile and build one of the examples:
```
cd examples
less README.md
```

Go back to the hercules window, and IPL the example:
```
IPL ../examples/foo
```

For more info, see the [examples README](../examples/README.md)
---
