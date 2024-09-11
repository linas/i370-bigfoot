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

## For using ccache
ENV PATH /usr/lib/ccache:$PATH

# TODO: Remove this user and replace with usage of `-u` flag during runtime.
# Create and switch user. The user is privileged with no password required
RUN adduser --disabled-password --gecos "Bigfoot Developer" bigfoot
RUN adduser bigfoot sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER bigfoot
WORKDIR /home/bigfoot

# Setup config files
COPY /scripts/ /home/bigfoot
# RUN sudo chown -R bigfoot:bigfoot .gdbinit

# For images built on this
ONBUILD USER root
