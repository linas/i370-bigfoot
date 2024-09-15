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
docker create --name foo -it bigfoot/i370-bigfoot
docker start -i foo
```
After the `docker start` above, you'll land in a running container.
The home directory is `/home/bigfoot`. Binaries can be found in
`/usr/local/bin`. For example, the assembler is named
`i370-ibm-linux-as`.

The container has a working versions of:
* `binutils-2.43` which is the latest version
* `gcc-3.4.6` which is the last version to support i370

The container includes the Hercules System/390 emulator. An example
Hercules config file is in `/home/bigfoot/hercules`; it is copied
from `./i370-bigfoot/scripts/hercules` in ''this'' directory.

The [README](./i370-bigfoot/scripts/hercules/README.md) file in the
`./i370-bigfoot/scripts/hercules` explains how to compile and IPL
programs.

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
