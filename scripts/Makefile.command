# SPDX-License-Identifier: GPL-3.0-or-later

build/%/entry: $(lib-obj-y)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) \
	      $(filter %.o,$^) \
	      $(filter %.a,$^) \
	      -o $@

include/%/d.h:
	mkdir -p $(@D)
	printf '%s\n' $| | sort | ./scripts/gen-d_h.sh $@ >$@

build/ctl/cmdtree build/daemon/cmdtree:

build/%/cmdtree: build/%/.commands scripts/build-cmdtree.py
	./scripts/build-cmdtree.py $*/main.c >$@

build/ctl/.commands build/daemon/.commands:

build/%/.commands: .force
	@mkdir -p $(@D)
	@trap 'rm -f .tmp-$$$$' EXIT && \
	find ctl -type f -not -name '*_entry.c' | sort >.tmp-$$$$ && \
	$(call mv_stale,.tmp-$$$$,$(@),)
