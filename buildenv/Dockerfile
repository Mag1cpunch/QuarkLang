FROM debian:bookworm

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y llvm-dev
RUN apt-get install -y clang

VOLUME /root/env
WORKDIR /root/env