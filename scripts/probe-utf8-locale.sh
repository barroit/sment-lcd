#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

trap 'rm -f .tmp-$$' EXIT

locale | grep -iE 'LC_CTYPE=.*UTF-?8' >.tmp-$$ || exit 0

eval $(cat .tmp-$$)
printf '%s\n' $LC_CTYPE
