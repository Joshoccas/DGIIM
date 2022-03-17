#!/bin/bash
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
# Helpinfo
HELPTEXT='# Script getProjectName.sh   \n
+ It analyzes the Makefile located in the ./nbproject/ folder seeking for the name of the project, which determines the name of the binary files stored in ./dist/'

# Finds the name of the binary
grep "OUTPUT_BASENAME=" ./nbproject/Package-Debug.bash | sed 's/^.*=//;s/$//' > ./.projectname

