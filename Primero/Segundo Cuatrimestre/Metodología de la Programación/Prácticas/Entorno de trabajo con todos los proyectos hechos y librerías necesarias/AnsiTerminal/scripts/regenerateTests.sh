#!/bin/bash
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
# Load configuration & moves to the project root folder
if [ -d scripts ]
then
    source scripts/doConfig.sh
else
    source doConfig.sh
fi
clear
if [ -z "$(ls -A $TESTS_FOLDER/*.test)" ]
then
    echo "NO TESTS AVAILABLE"
    exit
fi
printf "${WHITE}Backing up current tests\n${GRAY}"
zip tests.zip $TESTS_FOLDER/*
printf "${WHITE}Generating fresh binaries\n${GRAY}"
make build
printf "${WHITE}\n"
# Marks to parse .test files
CALL_MARK="%%%CALL"
OUTPUT_MARK="%%%OUTPUT"
OUTPUTFILE_MARK="%%%FROMFILE"
VALGRIND_MARK="%%%VALGRIND"
# Prebuild the command line for the call 
DIST=dist/Debug/GNU-Linux/
BINARY=$(ls $DIST)
k=1
for test in $TESTS_FOLDER/*.test
do
    echo "Regenerating $test"
    # Parse the codes for the call
    if grep --quiet $CALL_MARK $test; # Cond1
    then 
        # Parse the header of the test
        TEST_HEADER=$(sed -e /$OUTPUT_MARK/,\$d $test)
        # Parse the call line
        MYCALL=$(grep $CALL_MARK $test | sed s/$CALL_MARK//)
        FULL_BINARY=$PROJECT_FOLDER/$DIST/$BINARY
        echo "Test #$k [$test] $VALGRIND $BINARY $MYCALL" > $TESTS_FOLDER/.call$k
        eval "$FULL_BINARY $MYCALL &> $TESTS_FOLDER/.out$k"
        if  grep -a --quiet $OUTPUT_MARK $TESTS_FOLDER/.out$k; 
        then
            REAL_OUTPUT=$(grep -a -v == $TESTS_FOLDER/.out$k | sed -n /$OUTPUT_MARK/,\$p )
        else
            if  grep --quiet $OUTPUTFILE_MARK $test; 
            then
                FILE_OUTPUT=$(grep $OUTPUTFILE_MARK $test | sed s/$OUTPUTFILE_MARK//)
                REAL_OUTPUT=$(echo $OUTPUT_MARK;cat $FILE_OUTPUT )
            else
                REAL_OUTPUT=$(echo  $OUTPUT_MARK; grep -v == $TESTS_FOLDER/.out$k)
            fi
        fi
        echo "$TEST_HEADER" > $TESTS_FOLDER/.test$k
        echo "$REAL_OUTPUT" >> $TESTS_FOLDER/.test$k
        echo "----------------------------------------"
        cat $TESTS_FOLDER/.test$k
        exit
    else # Cond1
        printf "${RED}[ SKIP ] Test #$k [$test] CALL MARK not found in $test . ${GRAY}\n"
    fi # Cond 1
    k=$[k + 1]
done 

# Remove auxiliary files
#rm -f $TESTS_FOLDER/.out* $TESTS_FOLDER/.due* $TESTS_FOLDER/.real* $TESTS_FOLDER/.fail* $TESTS_FOLDER/.call*
printf "\n${WHITE}"
