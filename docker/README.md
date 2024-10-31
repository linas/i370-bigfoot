# Docker containers for i370 Bigfoot
So far, only one.

Docker is a quick and easy way of trying out the system, without all the
fuss and bother of actually having to read and follow instructions! Just
build the container, start it, and you're good to go!

## HOWTO
Instructions.

### Create Docker Container
First, install docker. Typically, `apt-get install docker` or similar.

Next, build the container:
```
cd .
docker build -t bigfoot/i370-bigfoot i370-bigfoot
```
The above might take an hour, mostly because it performs multiple
git-clones of large github repos.

Next, create and run a container. The container name is `foo` in this
example.  Replace `foo` with your desired container name.
```
docker create --privileged=true --name foo -it bigfoot/i370-bigfoot
docker start -i foo
```
The `--privileged=true` flag allows `mount` to be used in the container.
This is needed for creating a bootable i370 root disk image.

After the `docker start` above, you'll land in a running container.
The home directory is `/home/bigfoot`. Binaries can be found in
`/usr/local/bin`. For example, the assembler is named
`i370-ibm-linux-as`.

The container has a working versions of:
* `binutils-2.43` which is the latest version
* `gcc-3.4.6` which is the last version to support i370
* `linux-2.2.1` ported to the i370
* `pdpclib`, the public domain C90 library
* `uclibc-ng`, the uClibc library, ported to the i370
* `busybox`, a collection of common unix tools, including two shells.

The container includes the Hercules System/390 emulator. An example
Hercules config file is in `/home/bigfoot/hercules`; it is copied
from `./i370-bigfoot/scripts/hercules` in ''this'' directory.

The [Demo README](./i370-bigfoot/scripts/README.md) file in the
`scripts` directory explains how to run the demos.

#### Status
Everything works, more or less, including busybox.

#### Docker QuickRef
A short docker cheat sheet:
* `docker images`
* `docker rmi <image-hex>`
* `docker ps -a`
* `docker start -i <container-name>`
* `docker stop <container-name>`
* `docker rm <container-name>`
* `docker container cp <some-file> <container>:<path>
* `docker attach <container-name>`

#### Notes
1. Both `tmux` and `byobu` are installed, so you can use either for
   multiple windows/panes.
