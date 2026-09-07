#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

trap 'rm -f .tmp-$$' EXIT

exec 3>&1 >.tmp-$$

cat <<'EOF'
$0 == "include/generated/config.h:" {
	next
}

{
	sub("include/generated/config.h", "")
}

$0 !~ /\\$/ && ! done {
	done = 1

	print $0 " \\"
EOF

grep -Eho CONFIG_[_0-9A-Z]+ $@ | tr [:upper:]_ [:lower:]/ | sort | uniq |
sed -e '$!s|.*|\tprint " $(wildcard include/&.h) \\\\"|' \
    -e '$s|.*|\tprint " $(wildcard include/&.h)"|'

cat <<'EOF'
	print ""
	next
}

{
	print
}
EOF

awk -f .tmp-$$ >&3
