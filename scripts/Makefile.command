# SPDX-License-Identifier: GPL-3.0-or-later

build/daemon/%/entry: $(lib-obj-y) \
		      build/libusb/libusb-1.0.a \
		      libusb/libusb-1.0.pc
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) $(filter %.o,$^) \
	      $(filter %.a,$^) \
	      $(filter-out $(shell pkg-config --libs $(filter %.pc,$^)),\
			   $(shell pkg-config --static --libs \
					      $(filter %.pc,$^))) \
	      -o $@

build/libusb/libusb-1.0.a: libusb/libusb-1.0.a
	mkdir -p $(@D)
	ln -f $< $@

libusb/libusb-1.0.a libusb/libusb-1.0.pc:
	$(error No $@ found. \
		Run 'scripts/build-$(firstword $(subst /, ,$@)).sh' first)

build/ctl/%/entry: $(lib-obj-y)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) $(filter %.o,$^) \
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
