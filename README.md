# IBM i370 port of GNU/Linux

By popular demand, this repo contains a 25th anniversary resurrection
of the old
[i370-bigfoot project](https://linas.org/linux/i370-bigfoot.html).

As of this moment, the following are provided:
* Script for a Docker container that includes the i370 assembler
  (current GNU binutils with i370 patches applied), compiler
  (gcc version 3.4.6 with i370 patches applied), the Linux kernel
  (linux version 2.2.1 with i370 patches applied), uClibc (with i370
  patches applied), PDPCLIB (comes with some i370 support), BusyBox
  (with a `defconfig` that works for i370), and the Hercules
  System/390 mainframe emulator.
* Multiple demos showing how to compile and IPL code, how to boot
  the kernel, how to create `/sbin/init`, how to run busybox, and more.
  See the [demo README](docker/i370-bigfoot/scripts/README.md) for more.

## What is this?
IBM created the [IBM System/360 ](https://en.wikipedia.org/wiki/IBM_System/360)
series of mainframes in the 1960s. In later decades, these evolved into
System/370, the 3090 and eventually, the
[z/Architecture](https://en.wikipedia.org/wiki/Z/Architecture).
Many of the very earliest open source projects were created on S/360,
shepharded by [SHARE](https://en.wikipedia.org/wiki/SHARE_(computing)),
a volunteer-run user group for IBM mainframes.

In the 1990's, David Pitts ported the GNU GCC compiler to the System/370
instruction set, targeting the IBM HLASM assembler. This created the
possibility of porting a vast collection of open source projects to the
mainframe.

In 1998, [Linas Vepstas](https://linas.org), bored out of his mind,
decided that porting Linux to the mainframe might be fun. After all,
Linux is written in C, so how hard can this be? Heh. Multiple steps
were required:
* Creating an assembler, after it became clear that HLASM would not be
  suitable for a Linux port. Thus, the GNU gas assembler, part of GNU
  binutils, was ported. It accepts the System/370 instruction set, and
  generates ELF binaries.
* The ELF format goes hand-in-hand with the conventional BSD/SVR4-style
  pseudo-ops to define objects. Thus, a further work on GCC was needed
  to generate SVR4/BSD-style markup (as opposed to HLASM style). This
  target was given the name of "i370".
* Porting the Linux kernel. Work was done on Linux version 2.2.1, which
  was the most recent kernel when the project was started. Porting
  was easy, mostly because IBM mainframes come with VM, a virtual
  machine operating system, after which all other VM's are patterned.
  What made VM magic was that it had a built-in debugger; this debugger
  made it extremely easy to debug crashes and thus progress the port.
* Porting the user-space. This means porting the GNU loader, the
  GNU GLibC, and a shell.  A port of glibc was begun, as well as
  of a very basic shell.
* Help from lots of people. The following folks made significant
  contributions to the project: Dan Lepore, who taught me VM and
  System/390 principles of operation, and, more generally, how to debug;
  Neale Ferguson, who contributed multiple files, and Peter
  Schulte-Stracke, who contributed the PSA definition and string inlines.
  Later, at Princeton, Melinda Varian granted access to online VM systems
  to continue development.

The bundle of all of the above was given the project name of
[Bigfoot](https://linas.org/linux/i370-bigfoot.html) alluding to the
idea of a large mythical creature. Because mainframes are, well, large.

Work was progressing nicely: by the summer of 1999, the kernel booted,
ran, context-switched and was able to branch into user-space, and run
the shell. The shell ran, tried its first call to printf, when two
disasters struck at the same time.

First, around September/October 1999, Linas realized that glibc required
support for weak symbols, and this required a major redesign of the
subroutine calling conventions, including thunks and trampolines. Argh!
Getting this just right, while being clever and efficient, was technically
hard.

Second, IBM announced that it, too, had a port of Linux to the
mainframe! The history of this is a bit curious and unusual, and worth a
quick review. IBM Germany created the port in 1998/1999 as a skunkworks
project: an IBM Confidential project, kept secret. The reason for the
secrecy was fear. The IBM business model for mainframes was to give away
the hardware at cost, and generate profit from software sales. This was
a ten or twenty billion dollar business. The fear was that a "free"
operating system, such as Linux, might tank a third of IBM's revenues:
a veritable disaster! Of course, this is absurd, and cooler heads came
to previal, but not before IBM's CEO, Lou Gerstner, heard of Linas'
work. He then heard about the IBM Germany skunkworks project, and the
decision was clear: if there was to be Linux on the mainframe, IBM would
control it.

For Linas to continue after this was pointless; the last version of
Bigfoot was from November 1999. And that was that for the next 25 years.
Mostly. The i370 compiler and assembler continued to receive patches
from Paul Edwards, Dave Pitts and others: the compiler and assembler
were also used in other projects, mostly relating to MVS.

Recently, I was contacted by Paul Edwards, and asked if I could revive
the project.  I don't know that I want to: its not as if I don't have
enough to do, and enough interests to indulge. But what the heck, how
hard can this be? Just a little bit more work, and bingo, we're back.

For a related project, somewhat overlapping this, see
[PDOS, the Public Domain Operating System](https://pdos.org).

## Status
Version 1.0.0 - October 2024

At this time, [binutils](https://github.com/linas/i370-binutils)
(the assembler), [gcc](https://github.com/linas/i370-gcc) (the compiler)
and the [Linux kernel](https://github.com/linas/i370-linux-2.2.1) have
been revived. A port of
[uClibc-ng](https://github.com/linas/i370-uclibc-ng) has been created, and
BusyBox compiles and runs. Everything is stable, more or less: you can
boot one of the busybox shells (`ash`, `hush`) and everything runs,
nothing crashes.  You can even double-cross-compile the assembler and
the compiler and run them on i370-linux, and create working, runnable
programs.

Statically linked programs work great. Position-independent
(PIC) binaries seem to work.  The dynamic loader implementation is
unfinished, and the shared library linker is probably incomplete
and probably buggy because its untested.

## Why is this interesting?
This is a home hobbyist project that gives an opportunity to reflect upon
computer system design issues as they stood at the end of the 1990's. These
are both fundamentally and deeply important, altering the history of
computing, while also entirely obscure, as they disappear into the general
background of the common-place and taken-for-granted. Thus, important,
forgotten and mis-understood.

* ***The Shell.*** Unix can with the concept of a shell: bash, csh, sh.
This is a fundamental breakthrough that the makers of DOS never quite
wrapped their heads around: whether MS-DOS or mainframe DOS. The shell
virtualized access to operating system. It would not have been possible
without multi-tasking, which, of course, came to be understood as
important, but the further refinement into the concept of a shell seemed
to be lost (or misunderstood) in both the Microsoft and the mainframe world.

* Why was the shell underappreciated in some quarters? In the Microsoft
world, this was perhaps due to the small size of early Intel x86 PC's. We had
to wait for Linux to see a practical demonstration. In the mainframe world,
this was due to a focus on transaction processing and batch processing. No
mainframe customer needed, wanted or used shells; the few developers who
might have benefited had other ways of doing things.

* ***Multi-tasking*** is a very clever little knot tied deep in the OS kernel:
all CPU registers and process state are saved to RAM, and then a cute little
jump that restores everything. It feels like you never left: you are executing
instructions, but the process id, the memory mapping, the stack are suddenly
just ... different. Its really quite impressive, and perhaps a bit
mind-warping to track the dance, the jig, that morphs the one into the other.

* ***Virtual Machines.*** VM's. At the end of the 1990's, only the mainframes
had this, and no one else. The fact that they are now widespread, pervasive and
common-place attests to thier fundamental importance. I won't explain what a
VM is: this is deep, technical and interesting. But I do want to point out
the fundamental magic of the IBM mainframe VM: it had a built-in debugger.
You could single-step, run, set breakpoints and dis-assemble. This was a
fundamentally important capability.  Somehow it remains often overlooked.

* ***Line mode.*** This is more of a sad story, than anything else. In the
1960's, even the most powerful computers had fractions of a megabyte of RAM,
and processing input one line at a time made sense. Read all 80 characters,
and a tight loop in the OS figured out what to do. This made sense.
Unfortunately, this design decision was never amended on the mainframe.
Unix, and shells made it clear that, from the user perspective, you wanted
to be able to responed to each and every character typed at the keyboard.
But this was impossible with the mainframe channel architecture: the STARTIO
instruction is a single CPU instruction that generated a cascade of disk
access, running in the devices, outside of the CPU itself. The CPU was free
to do something else entirely: this is what made mainframes powerful. Like a
brontosaur, a dinosaur, the CPU was a small brain, but the muscles, the
disk-drives, the devices, these were huge, just massive processing subsystems
interconnected with channels. This made sense for batch processing and
transaction processing. But IBM never invented, manufactured or sold a device
that could respond, character-at-a-time, to user typing. How this could have
even been possible, without interrupting the CPU for each and every
keystroke, is unknown to me. Maybe that is why it was never invented.

* *** Storage keys.*** Turning our gaze towards the future, the mainframes
had a curious bit of technology: the storage keys. These are 4-bit hardware
ID's associated with RAM, and if the (hardware) ID of your running process
did not match (in hardware) the ID of the RAM you are trying to access, you
have nothing. This is similar to the distinction between user-mode and
kernel-mode in x86 PC's, but instead of one bit (user or kernel) its four
bits. Now, why is this interesting? Well, in the bad old days, before
multi-tasking, before client-server, if you ran an app, and the app had some
bug, you would not only crash, but corrupt your entire dataset in the
process. To shelter the data from the bad app, client-server was invented.
The server, robust and debugged, could be trusted. Wild-west apps, they did
whatever, but the server kept them at arms length. The price you paid for
this was multi-tasking, and the copying/movement of data. Wouldn't it have
just been more efficient to just toggle the storage key? Shared libraries
could run in one storage key, the app in another. Shared libraries that each
did not trust the other could have their own storage keys. Mandatory access
control (MAC), but in the user-space, not the kernel.  Easier said than
done, I suppose: storage keys continue to exist, but never became a
fundamental part of unix. May that change someday? I suppose.

* ***Containers.*** BSD gaols, Docker, LXC. This is a truly revolutionary
technology. These provide virtualization, but at the application level,
not the hardware level.  These had not yet been invented in the 1990's.
Contemplating the details of how containers differ from VM's, and what the
security profiles look like, and how that containerization is acheived is
worthy of attention. Containers are what allowed the cloud to bloom, and
failure to appreciate this means missing the modern revolution. But look
also at the other end: hypervisors, and low-level hardware+software advances
like VPNs, MPLS, SAN fabrics and the like. The fabric of communications, both
at the level of "bare metal", and at levels of high abstraction, continue to
evolve at a prodigious pace. The end of the 1990's provides a good way-point,
a place to stop and look around: compare what was known, what was imagined,
and what actually came to be.

* ***SystemD.*** I have changed my mind. For much of the 2010's, I
experienced a Linux that refused to boot, and required brain surgery to
fix. This was absolutely infuriating, mind-boggling, brain-shmashingly
difficult, and an endless sink of wasted time. I blamed SystemD. I have
now turned around 180 degrees. A uniformized, consolidated, standardized
framework for system services is the only rational path forward. At the end
of the 1990's, the roll-your-own bag of daemons, servers and services was
just plain normal, ordinary and unexceptional. One did not imagine that there
might be another way. But frankly, there's no good reason for a hodge-podge
of quirks: there's nothing wrong with smoothing out the lumpy bits, the
pokey-sharp bits.

* ***Ceph.*** In the 1990's, we had NFS. We also had RAID. And we had
filesystems: ext2fs, and XFS and JFS and all the others. And its still much
like this today (in 2026) But Ceph is another conceptual breakthrough: your
data files can now live in a cluster, with RAID-like duplication and
protections, but now spread across multiple machines, and not just one.
Network access like NFS, but ithout a single point of failure. Self-healing,
self-repairing, automated scrubbing and migration. The Ceph cluster is a bit
of an organism: it "lives" on multiple machines, migrates and moves as
needed, but always looking at avoiding data loss.  Again, this is an utterly
revolutionary idea.

* Unfortunately, its still early, and Unix is not year ready for Ceph. I have
different users, with different logons and different user ID's on different
systems. viz. UID's and GID's. These are 16-bit numbers, they are hard-coded
into the linux kernel, into `/etc/passwd`, into services and systemd. UID's
are not network transparant.  Yuck. There's no network logon; security is
hard. Access control is hard. Then there's RBD's the Rados block device. It's
great to have a network block device, but ext4fs means only one machine at a
time can access the block device. I cannot have two different ext4fs's
running on the same block device. So this idea of network migration and
network transparency remains a dream. Oh. And performance. The 1GbE is still
slower than 6Gbps SATA, and 10GbE pales compared to NVMe. Ceph is not yet
smart enough to migrate data to the machine that access it the most often.
Ceph is not yet a performance monster.  It needs to become one.

* ***AI and LLM's.*** Of course, this is an ongoing story. With many
opinions. I look forward to the day when I can ask my computer to do
something, and it will do it. Instead of fighting to configure some
foobar subsystem to work the way I want it to. Instead of fighting with
my internet service provider, who seems to not understand the service
they provide (looking at you, Grande/Astound Broadband. Why are y'all so
incompetent?). Instead of fighting with google, or my android phone,
or whatever stupid sh1t Samsung wants to strong-arm me into doing.
But the ills of corporate capitalism, that's for another project.


## Issues
Know what you are getting into! This is a revival of old work from 1999.
It remains in that era, more or less. This is a version of Linux for the
System/390 of that era; this is ***NOT*** a port to the z/Architecture.
That one is well-supported by IBM and runs on all modern metal. This
version targets old systems that predate the z/Architecture. This is an
explicit design decision.

Some issues:
* The current system is quasi-stable. It seems to run. Things seem to
  work. Parts of the kernel remain unfinished or untested. These are
  listed further, below.

* The glibc C library presents issues. Patches for a circa-1999-era
  glibc-2.1 are available on the original bigfoot site. However, modern
  compilers (needed for cross-compilation) cannot compile the old
  glibc. Conversely, the old compiler in use here (gcc-3.4.6) cannot
  compile modern glibc (currently glibc-2.43). Perhaps some middle
  version between 2.1 and 2.43 is possible?

* Dynamic library loading (needed for shared libraries) was never
  completed when the original project was abandoned. Most of the
  needed support is in the assembler, but might be buggy. The
  GOT/PLT design never got fully underway, the glibc `ld.so` compiled
  but certainly wouldn't have worked. There's some basic groundwork
  to create `ld.so` for uClibc, but the hard parts haven't been done.

* SMP support in the kernel was started, but never finished.

* The current uClibc/i370 version does not support either posix threads,
  nor LinuxThreads of the era.

* The kernel does not have any 3880/3990 CKD/ECKD drivers, which means
  that there is no disk storage. The demos all run from a ramdisk, but
  the overall system is unusable without working disks. All of the
  basic support for subchannels and schibs is in place; see the 3215
  driver for a working example. There are even stubs for both ckd and
  eckd; they are empty.

* The 3215 terminal driver works. However, line mode terminal access to
  unix is annoying: normal unix shells expect character-mode access.
  There are two ways to get character-mode ttys/ptys:

  -- Get a tty interface by using Paul Edwards characer-mode Hercules
     device: its like the 3215, but does characters. A Linux kernel tty
     driver would need to to be written for that. The current raw-3215
     driver does not use the kernel tty subsystem.

  -- Get a pty interface by logging in over the net. This requires
     network interfaces.  Providing networking for the Linux kernel is
     easy, in principle. In practice, this needs copy-in/copy-out with
     checksumming, and these are currently stubs in the Linux kernel.
     They are just like regular copy-in/copy-out (which work fine) but
     also do checksumming; these are used by the TCP/IP stack. In
     addition, a System/390 CTCA driver would need to be written, to
     get the network interfaces. Hercules uses the CTCA (Channel to
     Channel Attach) to provide TCP/IP through the host, so that works.
     What's missing is the kernel CTCA driver. Can't be that hard, right?

## HOWTO
The easiest way to try the system is to install Docker, build the Docker
container provided in the `docker` directory, and then run the
container.

The README in the docker directory explains more. It also points to
multiple examples, of increasing complexity.

If you wish to do everything by hand, then just emulate what you find in
`docker/i370-bigfoot/Dockerfile`. Note that Dockerfiles are kind of like
shell scripts: they should be easy to understand and run manually, as
needed.

## Demos
Files in the [docker/i370-bigfoot/scripts/](docker/i370-bigfoot/scripts/)
directory will be copied to `/home/bigfoot/` in the Docker container.
This allows the demos to be run in the container.

The [demo README](docker/i370-bigfoot/scripts/README.md) describes
multiple demos, from the most basic IPL to C code, to booting the
Linux kernel and running the initial process.

## Documentation
The CPU Architecture, including the instruction set, is documented in the
[ESA/390 Principles of Operation, Ninth Edition (June 2003)](https://publibfp.dhe.ibm.com/epubs/pdf/dz9ar008.pdf)
This is IBM document number SA22-7201-08. Has 1028 pages.

The assembler, compiler and kernel are compatible with this 32-bit
System/390 instruction set, and intentionally avoid using the modern
z/Architecture instructions. This is an explicit design decision.

The z/Architecture takes the 32-bit instruction set of the ESA/390 and
extends it with 64-bit instructions. The size of the documentation
doubles, and many important details seem to be subtly different. The
Bigfoot project targets the 32-bit CPU's ONLY. Thus, the ESA/390
documentation is recommended.

Additional references:
* [IBM System/370 Principles of Operation, Fourth Edition (September 1974)](http://bitsavers.informatik.uni-stuttgart.de/pdf/ibm/370/princOps/GA22-7000-4_370_Principles_Of_Operation_Sep75.pdf)
IBM Document number GA22-7000-4. Has 329 pages.

* [IBM System/370 Principles of Operation, Eleventh Edition (September 1987)](https://bitsavers.trailing-edge.com/pdf/ibm/370/princOps/GA22-7000-10_370_Principles_of_Operation_Sep87.pdf)
IBM Document number GA22-7000-10. Has 558 pages.

* [z/Architecture Principles of Operation, Fourteenth Edition (May,
2022)](https://www.ibm.com/docs/en/module_1678991624569/pdf/SA22-7832-13.pdf)
IBM document number SA22-7832-13. Has 2124 pages.

For your convenience (and in case thigs on the net get lost),
[a copy of the ESA/390 POC is here](docker/i370-bigfoot/scripts/SA22-7201-08.pdf)
and a short
[reference summary is here](docker/i370-bigfoot/scripts/System_370_Reference_Summary.pdf).
