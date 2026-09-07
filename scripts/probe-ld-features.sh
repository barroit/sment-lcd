#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

ld=$1
cc=$2
id=$3

trap 'rm -f .tmp-$$*' EXIT

$cc -x c -c -o .tmp-$$.o - <<EOF
int main() { return 0; }
EOF

probe_feature()
{
	read name
	read flags

	$cc --ld-path=$ld -fuse-ld=$id -Wl,-v $flags \
	    -o .tmp-$$.bin .tmp-$$.o >.tmp-$$.out >/dev/null 2>&1 ||
	$cc -B$(dirname $ld) -fuse-ld=$id -Wl,-v $flags \
	    -o .tmp-$$.bin .tmp-$$.o >.tmp-$$.out >/dev/null 2>&1 &&
	printf '%s=y\n' $name || true
}

probe_feature <<'EOF' &
LD_HAS_COMPRESS_DEBUG_SECTIONS_ZLIB
-Wl,--compress-debug-sections=zlib
EOF

probe_feature <<'EOF' &
LD_HAS_COMPRESS_DEBUG_SECTIONS_ZSTD
-Wl,--compress-debug-sections=zstd
EOF

wait
