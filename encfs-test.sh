#!/bin/bash

set -eu

DIR=/tmp/mmapwrite-encfs.$$

make

trap "fusermount -u $DIR/mnt && rm -R $DIR" EXIT

mkdir -p $DIR/mnt
cp -a encfs-test-fs $DIR
encfs --extpass "echo test" $DIR/encfs-test-fs $DIR/mnt
sleep 1
./mmapwrite $DIR/mnt/file

