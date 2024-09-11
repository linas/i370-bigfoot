# Docker containers for i370 Bigfoot
So far, only one.

Docker is a quick and easy way of trying out the system, without all the
fuss and bother of actually having to read and follow instructions! Just
build the container, start it, and you're good to go!

Instructions:
* Install docker
Then:
```
docker build --no-cache -t bigfoot/i370-bigfoot
docker run --rm -it bigfoot/i370-bigfoot
```
