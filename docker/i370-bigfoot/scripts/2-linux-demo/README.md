Booting Linux kernels
---------------------
This directory provides some convenience tools for booting Linux
kernels.

## Booting Overview
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
root=/dev/ram init=/sbin/my-foo-init i370_initrd=0x00200000,2048
```
which indicates that the root file system will be in RAM, and that the
name of the initial process is `/sbin/my-foo-init`. The `i370_initrd`
argument specifies where the ramdisk was loaded; it should match the
value in the INS file, else things will break. The number after the
comma is the size of the ramdisk, in KBytes. Note that this is the
*uncompressed* size!

### Automation
The above steps are automated by the provided Makefile. Just say `make`
and the appropriate INS file will be created.


## Notes
Caution: When configuring the Linux kernel, do **not** select
`CONFIG_VT_CONSOLE`. Doing so will prevent boot messages from going
to the Hercules console.

### Command lines
`init=/busybox ash -i`

`init=/busybox hush`

## Create a disk image
The only bootable disk images are ext2fs and minix. Neither MS-DOS FAT
nor Windows95 VFAT are bootable, because neither of these file systems
support file attributes, needed for special files (character devices,
block devices). Without special files, there is no way for user-land
processes to access devices; this includes accessing the console for
printing and the keyboard for getting typed input.

The example below creates a file named 'my-disk` holding a disk image
that is (exactly) 2 MBytes in size. The `-r0` specifies ext2fs version
zero; this is mandatory for the 2.2.1 kernel.

Don't forget the `mknod` for the character devices: you'll need these,
so that `/sbin/init` can open the keyboard+console for text I/O.
```
dd if=/dev/zero of=my-disk bs=1k count=2048
mke2fs -vm0 -r0 my-disk 2048
mount my-disk mnt
mkdir mnt/sbin/
cp my_init mnt/sbin/init
cp otherstuff mnt/
mkdir mnt/dev/
mknod mnt/dev/console c 227 1
mkdir mnt/dev/3270
mknod mnt/dev/3270/raw0 c 227 128
mknod mnt/dev/3270/raw1 c 227 129
mknod mnt/dev/3270/raw2 c 227 130
mknod mnt/dev/3270/raw3 c 227 131
umount mnt
gzip -v9 my-disk
```

Once an image has been created, the easiest way to update it is to mount
it with the loopback device:
```
sudo mount -o loop disk_image mnt
```
