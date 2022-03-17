#!/bin/bash
VERSION=1.0
# Helpinfo
HELPTEXT='# Script doCheckMemoryLeaks.sh   \n\n
doCheckMemoryLeaks -valgrind | -drmemory - binaryfile \n \n
+ it runs either *VALGRIND* or *DRMEMORY* to check for potential memory leaks. Dump the output into a special file and parses that file lokking for error messages fro either platform'

# Load configuration & moves to the project root folder
if [ -d ../Scripts ] 
then
    source ../Scripts/doConfig.sh $*
    if [ "$1" == "-valgrind" ]
    then
    	doValgrind $*
    elif [ "$1" == "-drmemory" ]
    then
    	doDrMemory $*
    else
    	echo "Unknown memory leak detector "$1
    	exit 1
   fi
else
    printf "\n${RED}Unable to find Scripts library"
    printf "${WHITE}"
fi

