#!/bin/bash
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
# Moves to the project' root folder
function CDRootFolder() {   
    DOMOVE=false
    while [ ! -d nbproject ]
    do
        cd ..
        DOMOVE=true
        DIR=$(pwd)
        if [ $DIR == '/' ] 
        then
            echo "Ups! Something went wrong...sorry!"
            exit 1
        fi
    done 
    if [ "$DOMOVE" == true ]
    then
        echo "Moving down to project root folder "$(pwd)
    fi
}

# Check if folder exists, otherwise creates it or set it to default
# param $1 The folder to check
# param $2 The variable used to store $1 (reference)
function CheckFolder() {
    if [ ! $1 ] || [ ! $2 ]
    then
       echo "ERROR: Missing parameters to CheckFolder() "; echo
       exit 1
    fi
    FOLDER=/dev/null
    if [ ! -d $1 ]
    then
        if [ $CREATE_FOLDERS = "YES" ]
        then 
            echo "Creating folder "$1
            mkdir $1
            FOLDER=$1
        else
            echo "Folder $1 does not exist"
        fi
    else
        FOLDER=$1
    fi
    eval "$2=$FOLDER"
}


# Main
# Moves to root folder
CDRootFolder
# Reads root folder and its name
PROJECT_FOLDER=$(pwd)
PROJECT_NAME=$(basename $PROJECT_FOLDER)
# Create unexisting folders when required or not
CREATE_FOLDERS=YES
# Folder to store .cpp
CheckFolder src/ SRC_FOLDER
# Folder to store .h
CheckFolder include/ INCLUDE_FOLDER
# Folder to store .data
CheckFolder data/ DATA_FOLDER
# Folder to store the zip
CheckFolder zip/ ZIP_FOLDER
# Folder to store Doxygen' data
CheckFolder doc/ DOC_FOLDER
# Folder to store test data
CheckFolder tests/ TESTS_FOLDER
# Folder to store local libreries
CheckFolder ../local/ LOCAL_FOLDER
CheckFolder ../local/include LOCAL_H_FOLDER
CheckFolder ../local/lib LOCAL_LIB_FOLDER
# Colors to be used in output of tests
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
GRAY='\033[1;30m'
WHITE='\033[1;37m'
# Use of memory leak detector
USE_VALGRIND=NO
# Seconds to wait before killing a (possibly) hang program
SECS_WAIT=5
# Prints explanations of failed tests?
DO_REPORT=YES
# Executes the script in interactive or batch mode
DO_INTERACTIVE=YES
# Forces the name of the ZIP. If left empty, the zip uses the name of the root foder
ZIP_NAME=$PROJECT_NAME
#ZIP_NAME="MPPractica"
