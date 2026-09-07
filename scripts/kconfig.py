# SPDX-License-Identifier: GPL-3.0-or-later

def read_features(filename):
	file = open(filename)
	lines = file.read().splitlines()
	features = map(lambda line: line.split('=')[0], lines)

	file.close()
	return set(features)

def first_line(filename):
	file = open(filename, 'r')
	line = file.readline().rstrip()

	file.close()
	return line

cc_features = read_features('build/probe/cc/features')
ld_features = read_features('build/probe/ld/features')

def warn_off(kconf, name):
	kconf.warn = False
	return ''

def host_id(kconf, name):
	return first_line('build/probe/host/id')

def host_arch(kconf, name):
	return first_line('build/probe/host/arch')

def host_name(kconf, name):
	return first_line('build/probe/host/name')

def repo_name(kconf, name):
	return first_line('build/probe/repo/name')

def repo_version(kconf, name):
	return first_line('build/probe/repo/version')

def utf8_locale(kconf, name):
	return first_line('build/probe/utf8/locale')

def cc_has_feature(kconf, name, feature):
	return 'y' if f"CC_HAS_{feature}" in cc_features else 'n'

def ld_has_feature(kconf, name, feature):
	return 'y' if f"LD_HAS_{feature}" in ld_features else 'n'

functions = {
	'warn-off': (warn_off, 0, 0),

	'host-id': (host_id, 0, 0),
	'host-arch': (host_arch, 0, 0),
	'host-name': (host_name, 0, 0),

	'repo-name': (repo_name, 0, 0),
	'repo-version': (repo_version, 0, 0),

	'utf8-locale': (utf8_locale, 0, 0),

	'cc-has-feature': (cc_has_feature, 1, 1),
	'ld-has-feature': (ld_has_feature, 1, 1),
}
