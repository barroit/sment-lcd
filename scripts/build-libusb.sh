#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

cd libusb
git clean -xdf

CFLAGS='-O3 -g0' ./autogen.sh --enable-static --disable-shared \
			      --disable-examples-build --disable-tests-build

make -j all
ln libusb/.libs/libusb-1.0.a
