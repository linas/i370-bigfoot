#
# Image with everything installed
#
# Steps to build & run:
# 1. docker build --no-cache -t bigfoot/i370-bigfoot
# 2. docker run --rm -it bigfoot/i370-bigfoot

# Debian Stable (Bookworm)
ARG VERSION=bookworm
FROM debian:${VERSION}

ENV DEBIAN_FRONTEND=noninteractive

# Bump this date, in order to force the apt-update to run again.
# Otherwise, it will use the cached Docker container, which might
# be stale or be missing security updates.
ENV LAST_OS_UPDATE 2024-09-11
RUN apt-get update && apt-get -y upgrade

# Install apt utilities
RUN apt-get -y install apt-transport-https software-properties-common \
      sudo wget tzdata apt-utils

# Install build tools
RUN apt-get -y install git gcc g++ ccache make
# General user convenience tools
RUN apt-get -y install tmux byobu vim
# Binutils needs gmp, mpfr, texinfo, bison, flex
RUN apt-get -y install libmpfr-dev libgmp-dev texinfo bison flex

# System/370, ESA/390 and z/Architecture Emulator
RUN apt-get -y install hercules

## Use ccache to minimize build times.
ENV PATH /usr/lib/ccache:$PATH

# Create and switch user. The user is privileged, with no password required.
RUN adduser --disabled-password --gecos "Bigfoot Developer" bigfoot
RUN adduser bigfoot sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER bigfoot
WORKDIR /home/bigfoot

# Setup config files
COPY /scripts/ /home/bigfoot
RUN sudo chown -R bigfoot:bigfoot .gdbinit

# Perform git clone. These are large and time consuming.
# Do them once, and only once; to update, do a git pull,
# farther below.
ENV LAST_GIT_CLONE 2024-09-11
RUN git clone https://github.com/linas/i370-binutils
RUN git clone https://github.com/linas/i370-gcc

# Grab latest binutils
ENV LAST_BINUTILS_UPDATE 2024-09-11
RUN cd i370-binutils; git pull
RUN cd i370-binutils; mkdir build; cd build; \
    ../configure --target=i370-ibm-linux; make -j12
# Again, for good luck (and readable error messages)
RUN cd i370-binutils/build; make
RUN cd i370-binutils/build; sudo make install

# Grab latest gcc
ENV LAST_GCC_UPDATE 2024-09-11
RUN cd i370-gcc; git pull

# For images built on this
ONBUILD USER root
