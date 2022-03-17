#!/bin/bash
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
# Helpinfo
HELPTEXT='# Script runDocumentation.sh   \n
+ It runs *Doxygen* over the file ./doc/documentation.doxy and generates automatically all the HTML and LATEX documentation of source files in *.cpp and *.h files along the current directory    \n\n
+ It runs a specific function that parses test files in the ./tests/ folder and generates a Markdown [formatted output](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) which describes the set of Unit and Integration tests to be passed.\n \n
Both documents are stored in the ./doc/ folder for further reference \n \n'

# Load configuration & moves to the project root folder
if [ -d ../../Scripts ] 
then
    source ../../Scripts/doConfig.sh $*
    runDoxygen
    runTestsDocumentation
else
    printf "\n${RED}Unable to find Scripts library"
    printf "${WHITE}"
fi

