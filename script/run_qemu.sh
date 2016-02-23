#!/bin/sh

if ! command -v qemu-system-arm >/dev/null 2>&1;
then
	echo "could not find qemu-system-arm, please install"
	exit 1
fi

qemu-system-arm -nographic -cpu cortex-a9 -M versatilepb -kernel kernel/armadillo
