#
# tiny static builder
#

FROM ubuntu:20.04

RUN apt-get update && apt-get install -y libjson-c-dev build-essential

WORKDIR /host

CMD gcc -static -o jsonsubst jsonsubst.c -ljson-c
