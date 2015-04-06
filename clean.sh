#!/bin/bash
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Copyright (C) 2015 Álvaro Fernández Rojas <noltari@gmail.com>
#
CMAKE_FILES="CMakeCache.txt CMakeFiles Makefile cmake_install.cmake install_manifest.txt version.h"

if [ -f "Makefile" ]; then
	make clean
fi

rm -rf $CMAKE_FILES

exit 0
