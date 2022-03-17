#!/bin/sh
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
# Helpinfo
HELPTEXT='# Script runTests.sh   \n
+ It is used to build the tests and execute them in a terminal\n\n'

	make -f nbproject/Makefile-Debug.mk SUBPROJECTS= .build-tests-conf
	gnome-terminal --quiet -command="make -f nbproject/Makefile-Debug.mk SUBPROJECTS= .test-conf"

