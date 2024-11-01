#
# Image for Bigfoot/370 with everything installed.
#
# Steps to build & run:
# 1. docker build -t bigfoot/i370-bigfoot .
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
RUN apt-get -y install git gcc g++ ccache make gdb automake
# General user convenience tools
RUN apt-get -y install tmux byobu vim bzip2
# Binutils needs gmp, mpfr, texinfo, bison, flex
RUN apt-get -y install libmpfr-dev libgmp-dev texinfo bison flex

# System/370, ESA/390 and z/Architecture Emulator
RUN apt-get -y install hercules herculesstudio inetutils-telnet x3270

## Use ccache to minimize rebuild times.
ENV PATH /usr/lib/ccache:$PATH

# Create and switch user. The user is privileged, with no password required.
RUN adduser --disabled-password --gecos "Bigfoot Developer" bigfoot
RUN adduser bigfoot sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER bigfoot
WORKDIR /home/bigfoot

# Perform git clone. These are large and time consuming.
# Do them once, and only once; to update, do a git pull,
# farther below.
ENV LAST_GIT_CLONE 2024-09-23
RUN git clone https://github.com/linas/i370-binutils
RUN git clone -b i370-gcc-3.4.6 --single-branch https://github.com/linas/i370-gcc
RUN git clone https://github.com/linas/i370-linux-2.2.1
RUN git clone https://git.code.sf.net/p/pdos/gitcode pdos-gitcode
RUN git clone https://github.com/linas/i370-uclibc-ng
RUN git clone https://git.busybox.net/busybox/

# dash doesn't work as /sbin/init and is flakey to compile
# RUN git clone https://git.kernel.org/pub/scm/utils/dash/dash.git

# Grab latest binutils
ENV LAST_BINUTILS_UPDATE 2024-10-28
RUN cd i370-binutils; git pull
RUN cd i370-binutils; mkdir build; cd build; \
    ../configure --target=i370-ibm-linux; make -j12
# Again, for good luck (and readable error messages)
RUN cd i370-binutils/build; make
RUN cd i370-binutils/build; sudo make install

# Grab latest gcc
ENV LAST_GCC_UPDATE 2024-10-31
RUN cd i370-gcc; git pull
RUN cd i370-gcc; git checkout i370-gcc-3.4.6
RUN cd i370-gcc; mkdir build; cd build; \
    ../configure --target=i370-ibm-linux -enable-languages="c" \
       --disable-threads; make -j12
# Again, for good luck (and readable error messages)
RUN cd i370-gcc/build; make
RUN cd i370-gcc/build; sudo make install

# Grab latest i370 linux-2.2.1 kernel
ENV LAST_KERNEL_UPDATE 2024-10-20
RUN cd i370-linux-2.2.1; git pull
RUN cd i370-linux-2.2.1; make oldconfig; make; make;
RUN cd i370-linux-2.2.1; sudo make headers_install

# Grab latest PDOS C library
ENV LAST_PDOS_UPDATE 2024-10-08
RUN cd pdos-gitcode; git pull
RUN cd pdos-gitcode/pdpclib; cat makefile.big | sed -e "s/        /\t/" > makefile.bog
RUN cd pdos-gitcode/pdpclib; make -f makefile.bog CC=i370-ibm-linux-gcc \
      AS=i370-ibm-linux-as AR=i370-ibm-linux-ar \
      CPP="cpp -DBIGFOOT" \
      LD="i370-ibm-linux-ld --entry __crt0"
RUN cd pdos-gitcode/pdpclib; ln -s pdpclib.a libc.a

# Well, Seems PDOS is not ready for prime-time. So grab uclibc.
ENV LAST_UCLIBC_UPDATE 2024-10-12
RUN cd i370-uclibc-ng; git pull
RUN cd i370-uclibc-ng; cp ./extra/Configs/defconfigs/i370/defconfig .config
RUN cd i370-uclibc-ng; make
RUN cd i370-uclibc-ng; sudo make install

# Grab latest busybox source
ENV LAST_BUSYBOX_UPDATE 2024-10-16
RUN cd busybox; git pull
COPY /scripts/6-busybox-demo/defconfig busybox/.config
COPY /scripts/6-busybox-demo/busybox.patch busybox
RUN cd busybox; patch -p1 < busybox.patch
RUN cd busybox; make

# Create the host-cross assembler
RUN cd i370-binutils; mkdir build-uclibc; cd build-uclibc; \
    export SYSROOT=/usr/local/i370-linux-uclibc; \
    ../configure --target=i370-ibm-linux --host=i370-ibm-linux \
         --disable-gdb --disable-sim \
         --prefix=${SYSROOT}/usr \
         CFLAGS="-I${SYSROOT}/usr/include -B${SYSROOT}/usr/lib -L${SYSROOT}/usr/lib -DHAVE_FCNTL_H -DTLS=\"\""

RUN cd i370-binutils/build-uclibc; make
RUN cd i370-binutils/build-uclibc; sudo make install

# Create the host-cross compiler. Almost works but not quite.
RUN sudo cp -pr /usr/local/i370-linux-uclibc/usr/include /usr/local/i370-ibm-linux
RUN sudo cp -pr /usr/local/i370-linux-uclibc/usr/lib/* /usr/local/i370-ibm-linux/lib
RUN cd i370-gcc; mkdir build-uclibc; cd build-uclibc; \
   CC="i370-ibm-linux-gcc -B$SYSROOT/usr/lib -L$SYSROOT/usr/lib" \
   CC_FOR_BUILD="gcc -I/usr/include -I/usr/include/x86_64-linux-gnu/ -D__x86_64__ -U__ILP32__" \
   ../configure --target=i370-ibm-linux --host=i370-ibm-linux \
           --build=x86_64-unknown-linux-gnu \
           --prefix=$SYSROOT/usr \
           --enable-languages="c" --disable-threads
RUN cd i370-gcc/build-uclibc; make
RUN cd i370-gcc/build-uclibc; make
RUN cd i370-gcc/build-uclibc; sudo make install

# Setup config files. Do this after above, so that changes here do not
# result in a rebuild of the image. In particular, we want to avoid
# redoing the git clone above, as those are time consuming.
COPY /scripts/ /home/bigfoot
RUN sudo chown bigfoot:bigfoot .byobu .gdbinit
RUN sudo chown -R bigfoot:bigfoot .

RUN cd 2-linux-demo; cp ../i370-linux-2.2.1/vmlinux .; make

# For images built on this
ONBUILD USER root
