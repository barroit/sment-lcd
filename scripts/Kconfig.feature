# SPDX-License-Identifier: GPL-3.0-or-later

menu "Program features"

config UTF8_LOCALE
	string "Default LC_CTYPE"
	default "$(utf8-locale)"

endmenu # Program features
