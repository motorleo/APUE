#!/bin/bash

set -x

mkdir -p build \
	&& cd build \
	&& cmake .. \
	&& make $*
