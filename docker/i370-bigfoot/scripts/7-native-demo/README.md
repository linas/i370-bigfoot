i370 Native Demo
----------------
The uClibc + busybox environment appears to be sufficiently stable to
contemplate a native host bringup. This is a root-disk with not only
busybox on it, but also the assembler and compiler. This directory
contains random stuff needed to assist in getting tha going.

Basically, copy what you need into `big-root-disk`, then `touch
date-stamp` then `make` then IPL.

Note that the disk image is huge: currently, 256 MBytes. This is
because there is no shared-library support, and each binary will
be 5 or 10 MBytes in size, on average. This chews through disk
space rapidly.
