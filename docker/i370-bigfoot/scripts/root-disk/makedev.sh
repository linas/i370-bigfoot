#! /bin/sh
#
# Create the devices that the i370 linux kernel needs, in order to
# provide a basic command line. These are /dev/console and four
# raw 3215 teminals.
#
mkdir dev/
mknod dev/console c 227 1
chmod ugo+rw dev/console

mkdir dev/3270
mknod dev/3270/raw0 c 227 128
mknod dev/3270/raw1 c 227 129
mknod dev/3270/raw2 c 227 130
mknod dev/3270/raw3 c 227 131
chmod ugo+rw dev/3270/raw*

# Seems that /dev/null and /dev/zero are useful, too
mknod dev/mem c 1 1
mknod dev/null c 1 3
mknod dev/port c 1 4
mknod dev/zero c 1 5
mknod dev/full c 1 7
mknod dev/random c 1 8
mknod dev/urandom c 1 9
mknod dev/kmsg c 1 11

chmod ugo+rw dev/null
chmod ugo+rw dev/zero
chmod ugo+rw dev/full
chmod ugo+rw dev/random
chmod ugo+rw dev/urandom
