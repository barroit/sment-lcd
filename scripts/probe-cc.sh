#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

trap 'rm -f .tmp-$$' EXIT

$1 -E -P -x c - <<'EOF' | grep -v '^$' >.tmp-$$
#if defined(__clang__)
Clang	clang	__clang_major__	__clang_minor__	__clang_patchlevel__
#elif defined(__GNUC__)
GCC	gcc	__GNUC__	__GNUC_MINOR__	__GNUC_PATCHLEVEL__
#endif
EOF

test -s .tmp-$$ && \
test $(awk '{ print NF }' .tmp-$$) -eq 5 || \
exit 1

read name id major minor patch <.tmp-$$

test $name != GCC && \
test $name != Clang && \
exit 1

version=$(( $major * 1000 + $minor ))

test $name = GCC && test $version -lt 12000 && exit 1
test $name = Clang && test $version -lt 18000 && exit 1

printf '%s\t%s\t%s\t%s\n' $1 $id $version $name
