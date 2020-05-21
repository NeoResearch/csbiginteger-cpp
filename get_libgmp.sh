#!/bin/bash

echo "Trying to find 'libgmp.so' (GNU BigNum)"
#if(ldconfig -p | grep libgmp); then
if(whereis libgmp | grep libgmp.so); then
	echo "Found GNU BigNum!"
else
	echo "Didn't find... please install it with: 'sudo apt-get install libgmp-dev'"
	exit 1
fi
