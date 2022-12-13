#
# tiny static builder
#

FROM ubuntu:20.04

RUN apt-get update && apt-get install -y libjson-c-dev build-essential

WORKDIR /host

CMD make build
