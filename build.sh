#!/bin/bash
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Copyright (C) 2015 Álvaro Fernández Rojas <noltari@gmail.com>
#
if [ -f "CMakeLists.txt" ]; then
	cmake CMakeLists.txt
	make
fi

exit 0
