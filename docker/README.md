# Docker containers for i370 Bigfoot
So far, only one.

Docker is a quick and easy way of trying out the system, without all the
fuss and bother of actually having to read and follow instructions! Just
build the container, start it, and you're good to go!

Instructions:
* Install docker
Then:
```
cd .
docker build -t bigfoot/i370-bigfoot i370-bigfoot
docker create --name foo -it bigfoot/i370-bigfoot
docker start -i foo
```
Replace `foo` with your desired container name.

After the `docker start` above, you'll land in a running container.
The home directory is `/home/bigfoot`. Binaries can be found in
`/usr/local/bin`. For example, the assembler is named
`i370-ibm-linux-as`.

A short docker cheat sheet:
* `docker images`
* `docker rmi <image-hex>`
* `docker ps -a`
* `docker start -i <container-name>`
* `docker stop <container-name>`
* `docker rm <container-name>`
* `docker container cp <some-file> <container>:<path>
* `docker attach <container-name>`

## Notes
1. Both `tmux` and `byobu` are installed, so you can use either for
   multiple windows/panes.
