# SPDX-License-Identifier: GPL-3.0-or-later

build/ctl/%/entry: $(lib-obj-y)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) $(filter %.o,$^) \
	      -o $@

build/ctl/cmdtree:

build/ctl/.commands:
