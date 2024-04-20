FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install --no-install-recommends -y \
    less \
    gosu \
    sudo \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*


RUN apt-get update && apt-get install --no-install-recommends -y \
    build-essential \
    cmake \
    gcc-11 \
    g++-11 \
    git \
    make \
    ninja-build \
    python3 \
    python3-pip \
    screen \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*


RUN pip3 install \
  conan \
  cmake_format

COPY ./entrypoint.sh  /

ENTRYPOINT ["/entrypoint.sh"]
