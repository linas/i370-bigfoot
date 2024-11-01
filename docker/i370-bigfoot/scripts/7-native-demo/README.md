i370 Native Demo
----------------
The uClibc + busybox environment appears to be sufficiently stable to
contemplate a native host bringup. This is a root-disk with not only
busybox on it, but also the assembler and compiler. This directory
contains random stuff needed to assist in getting that going.

Basically, copy what you need into `big-root-disk`, then `touch
date-stamp` then `make` then IPL.

Note that the disk image is huge: currently, 256 MBytes. This is
because there is no shared-library support, and each binary will
be 5 or 10 MBytes in size, on average. This chews through disk
space rapidly.

Be sure to edit `hercules.cnf` and provide enough RAM to hold the
entire disk image. For example:
```
  MAINSIZE  512                 # Main storage size in megabytes
```

### Issues
Sound easy, right? Hah.
* The Linux kernel croaks in memory management if a 256 MByte root disk
  is specified. An 80 MByte root disk seems to work.

* The line-mode 3215 interface is unpleasant. There are two ways to get
  a character-mode interface.
  -- One is to use Paul Edwards characer-mode Hercules device: its like
     3215, but does characters. However, a Linux kernel tty driver
     would need to be written for that.
  -- Provide networking interfaces for the Linux kernel. Easy, in
     principle. In practice, the required copy-in/copy-out with
     checksumming routines are stubs in the Linux kernel. These are
     just like regular copy-in/copy-out (which work fine) but also
     do checksumming; these are used by the tcp/ip stack. In addition,
     a System/390 CTCA driver would need to be written, to get the
     network interfaces. Can't be that hard, right?
* The ramdisk is OK for a demo. Anything more serious requires having
  an actual disk. For this, a System/390 CKD or ECKD device driver
  needs to be written (for 3880/3990 access). The stubs are there.
  They need to be filled in.
