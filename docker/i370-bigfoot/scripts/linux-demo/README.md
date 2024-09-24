Booting Linux kernels
---------------------
This directory provides some convenience tools for booting Linux
kernels.

Linux kernels and ramdisks can be loaded into Hercules in a relatively
straightforward way. This is done by IPL'ing an INS file. A typical
INS file will look something like this:
```
* INS file to load Linux kernel
* Format: <file to load> [address where to load]
* The elf-stripped kernel
vmlinux.bin  0x00000000

* Boot command line
cmd_line  0x000a0000

* Load RAMDISK at the same address as given in command line
ram_image.gz  0x00200000
```

In the above example, `vmlinux.bin` is a stripped kernel, created with
the `elf-stripper` tool.

The `cmd_line` is a plain-text (ASCII) file, specifying the boot
command line. It must be shorter than 512 bytes. A typical example
is
```
root=/dev/ram init=/sbin/my-foo-init
```
which indicates that the root file system will be in RAM, and that the
name of the initial process is `/sbin/my-foo-init`


### Notes
Some useful command params:
```
init=/sbin/my-foo-init
```

### Create a ramdisk
Ramdisks can be ext2fs, MSDOS fs or VFAT (Windows 95) disk images.

Example of creating an ext2fs disk image. Running as root, perform
the following:
```
dd if=/dev/zero of=/dev/ram bs=1k count=2048
mke2fs -vm0 -I 128 /dev/ram 2048
mount /dev/ram /mnt
mkdir /mnt/sbin/
cp my_init /mnt/sbin/init
cp otherstuff /mnt/
umount /mnt
dd if=/dev/ram bs=1k count=2048 | gzip -v9 > /tmp/ram_image.gz
```

To create an MSDOS image:

```
dd if=/dev/zero of=/dev/ram bs=1k count=2048
mke2fs -vm0 -I 128 /dev/ram 2048
mount /dev/ram /mnt
mkdir /mnt/sbin/
cp my_init /mnt/sbin/init
cp otherstuff /mnt/
umount /mnt
dd if=/dev/ram bs=1k count=2048 | gzip -v9 > /tmp/ram_image.gz
```
