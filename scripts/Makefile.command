# SPDX-License-Identifier: GPL-3.0-or-later

build/command/%/entry: $(lib-obj-y) $(link-y)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) $(filter %.o %.a,$^) \
	      -o $@

include/command/%/d.h:
	mkdir -p $(@D)
	printf '%s\n' $| | sort | ./scripts/gen-d_h.sh $*/ >$@

build/cmdtree: build/.commands scripts/build-cmdtree.py
	./scripts/build-cmdtree.py command/main.c >$@

build/.commands: .force
	@mkdir -p $(@D)
	@trap 'rm -f .tmp-$$$$' EXIT && \
	find command -type f | sort >.tmp-$$$$ && \
	$(call mv_stale,.tmp-$$$$,$(@),)
