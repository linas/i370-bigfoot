#! /bin/sh
#
# Create the devices that the i370 linux kernel needs, in order to
# provide a basic command line. These are /dev/console and four
# raw 3215 teminals.
#
mkdir dev/
mknod dev/console c 227 1
mkdir dev/3270
mknod dev/3270/raw0 c 227 128
mknod dev/3270/raw1 c 227 129
mknod dev/3270/raw2 c 227 130
mknod dev/3270/raw3 c 227 131
