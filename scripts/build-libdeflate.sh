#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

cd libdeflate
git clean -xdf

cmake -B build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_FLAGS_RELEASE='-O3 -g0 -DNDEBUG' \
      -DLIBDEFLATE_BUILD_SHARED_LIB=OFF \
      -DLIBDEFLATE_ZLIB_SUPPORT=OFF \
      -DLIBDEFLATE_GZIP_SUPPORT=OFF \
      -DLIBDEFLATE_BUILD_GZIP=OFF

cmake --build build --parallel
