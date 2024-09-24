

ramdisk notes

As root:
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
