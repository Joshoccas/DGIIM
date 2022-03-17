#!  /bin/bash
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
# Load configuration & moves to the project root folder
if [ -d scripts ]
then
    source scripts/doConfig.sh
else
    source doConfig.sh
fi

# Pass test file $1
function doTest  {
    if [ ! -f $1 ]
    then
        return 1
    fi
    # Parse the codes for the call
    if grep --quiet $CALL_MARK $1; # Cond1
    then 
        printf "\n${YELLOW}Testing $1 ..."
        MYCALL=$(grep $CALL_MARK $1 | sed s/$CALL_MARK//)
        # Parse the expected output from the test
        DUE_OUTPUT=$(sed -n /$OUTPUT_MARK/,\$p $1)
        # Parse possible  Valgrind request
        if  grep --quiet $VALGRIND_MARK $1; 
        then
            FORCE_VALGRIND=YES
        else
            FORCE_VALGRIND=NO
        fi
        # Compose the call and execute it
        if [ $USE_VALGRIND == "YES" ] || [ $FORCE_VALGRIND == "YES" ]
        then 
            VALGRIND="valgrind --leak-check=full "
        else
            VALGRIND=" "
        fi
        FULL_BINARY=$VALGRIND$PROJECT_FOLDER/$BINARY
        echo "Test #$k [$1] $VALGRIND $BINARY $MYCALL" > $TESTS_FOLDER/.call$k
        # Auto-compose a shell for the purpose of trying the binary
        # uses the .timeout file as a lock to detect that the program has ended
        echo "touch $TESTS_FOLDER/.timeout">$TESTS_FOLDER/.run.sh
        echo "CMD=\"$VALGRIND $FULL_BINARY $MYCALL 1> $TESTS_FOLDER/.out$k 2>&1\"">> $TESTS_FOLDER/.run.sh
        echo "eval \$CMD">>$TESTS_FOLDER/.run.sh
        echo "rm $TESTS_FOLDER/.timeout">>$TESTS_FOLDER/.run.sh
        chmod u+x $TESTS_FOLDER/.run.sh
        # Runs the shell with a timeout to prevent hanging
        timeout --preserve-status -k $SECS_WAIT $SECS_WAIT sh $TESTS_FOLDER/.run.sh
        #rm $TESTS_FOLDER/.run.sh
        # Check the output both the program and Valgrind
        if [ $USE_VALGRIND == "YES" ] || [ $FORCE_VALGRIND == "YES" ]
        then 
            VALGRIND_OUTPUT="\n        "$(grep -a "ERROR SUMMARY" $TESTS_FOLDER/.out$k | sed s/==[0-9]*==//)
            if grep -a "ERROR SUMMARY" $TESTS_FOLDER/.out$k | grep --quiet " 0 errors";
            then 
                VALGRIND_LEAKS=FALSE
            else
                VALGRIND_LEAKS=TRUE
            fi
        else
            VALGRIND_OUTPUT=""
            VALGRIND_LEAKS=FALSE
        fi
        # If the real output of the program cotains %%%OUTPUT marks, then only those marks
        # are compared for validity. Otherwise, the full output is compared
        if  grep -a --quiet $OUTPUT_MARK $TESTS_FOLDER/.out$k; 
        then
            REAL_OUTPUT=$(grep -a -v == $TESTS_FOLDER/.out$k | sed -n /$OUTPUT_MARK/,\$p )
        else
            if  grep --quiet $OUTPUTFILE_MARK $1; 
            then
                FILE_OUTPUT=$(grep $OUTPUTFILE_MARK $1 | sed s/$OUTPUTFILE_MARK//)
                REAL_OUTPUT=$(echo $OUTPUT_MARK;cat $FILE_OUTPUT )
            else
                REAL_OUTPUT=$(echo  $OUTPUT_MARK; grep -v == $TESTS_FOLDER/.out$k)
            fi
        fi
        # Save due and real outputs in disk for further use
        echo "$DUE_OUTPUT" > $TESTS_FOLDER/.due$k
        echo "$REAL_OUTPUT" > $TESTS_FOLDER/.real$k
        # When both outputs (expected and real) differ or valgrind detects leaks of memory
        # the test FAILS
        if [ -f $TESTS_FOLDER/.timeout ]
        then
            rm $TESTS_FOLDER/.timeout
            printf  "\r${RED}[ HANG ] Test #$k [$1] ($VALGRIND $BINARY $MYCALL) $VALGRIND_OUTPUT"
            cp $TESTS_FOLDER/.out$k $TESTS_FOLDER/.fail$k
            FAILED_TESTS=YES
        elif [ ! "$DUE_OUTPUT" == "$REAL_OUTPUT" ] || [ "$VALGRIND_LEAKS" == "TRUE" ]
        then
            printf  "\r${RED}[FAILED] Test #$k [$1] ($VALGRIND $BINARY $MYCALL) $VALGRIND_OUTPUT"
            cp $TESTS_FOLDER/.out$k $TESTS_FOLDER/.fail$k
            FAILED_TESTS=YES
        else
            printf  "\r${GREEN}[  OK  ] Test #$k [$1] ($VALGRIND $BINARY $MYCALL) $VALGRIND_OUTPUT"
        fi
    else # Cond1
        printf "${RED}[ SKIP ] Test #$k [$1] CALL MARK not found in $1 . ${GRAY}\n"
    fi # Cond 1
}
if [ -z "$(ls -A $TESTS_FOLDER/*.test)" ]
then
    echo "NO TESTS AVAILABLE"
    exit
fi
if [ "$DO_INTERACTIVE" == "YES" ]
then
    clear
    printf "${WHITE}Generating fresh binaries\n${GRAY}"
    make clean
    make build | tee make.out
else
    make clean > make.out
    make build > make.out
fi
printf "${WHITE}\n"

# Marks to parse .test files
CALL_MARK="%%%CALL"
OUTPUT_MARK="%%%OUTPUT"
OUTPUTFILE_MARK="%%%FROMFILE"
VALGRIND_MARK="%%%VALGRIND"
# Prebuild the command line for the call 
BINARY=$(grep "g++[^ ]*[ \t]*-o" make.out | sed "s/^.*-o //;s/ build.*$//")
# Auxiliary files
# .out* Raw output of the run
# .due* Expected predefined output
# .real* Real predefined output
# .fail* Output of every failed test
# .call* Description of the call
# .report Full report of failed tests when bacth mode
rm -f $TESTS_FOLDER/.out* $TESTS_FOLDER/.due* $TESTS_FOLDER/.real* $TESTS_FOLDER/.fail* $TESTS_FOLDER/.call*
# Flag to detect FAILED tests
FAILED_TESTS=NO
k=1
# First sorted tests
for test in $TESTS_FOLDER/*.test
do
    if [ -f $test ]
    then  
        doTest $test
        k=$[k + 1]
    fi
done 
# Second unit tests
for utest in $TESTS_FOLDER/*.utest
do  
    if [ -f $utest ]
    then
        cp $PROJECT_FOLDER/src/main.cpp $TESTS_FOLDER/
        cp $utest.cpp $PROJECT_FOLDER/src/main.cpp
        make > make.out
        doTest $utest
        cp $TESTS_FOLDER/main.cpp $PROJECT_FOLDER/src/main.cpp
        k=$[k + 1]
    fi
done 
# Analyzes the results
printf "${WHITE}\n"
if [ "$FAILED_TESTS" == "YES" ] 
then 
    if [ "$DO_INTERACTIVE" == "YES" ]
    then
        echo "Press [y] for SHORT REPORTS, [f] for LONG REPORTS, other to skip"
        read REVIEW
    fi
    if [ "$REVIEW" == "y" ] || [ "$REVIEW" == "f" ]
    then
        if [ "$DO_INTERACTIVE" == "YES" ]
        then
            clear
        fi
        printf "\n${WHITE}SHORT REPORT"
        for test in $TESTS_FOLDER/.fail*
        do
            NUMBER=$(echo $test | sed s/^.*fail//)
            printf "\n${RED} FAILED ${WHITE}$(head -1 $TESTS_FOLDER/.call$NUMBER)${GRAY}"
            printf "\n${GRAY}Differences found between ${GREEN}DUE${GRAY} and ${RED}REAL${GRAY} outputs:\n${GRAY}"
            DIFF=$(diff $TESTS_FOLDER/.due$NUMBER $TESTS_FOLDER/.real$NUMBER | sed s/^\>/'\\033[0;31m'\>/ | sed s/^\</'\\033[0;32m'\</ | sed s/$/'\\033[1;30m'/)
#            DIFF=$(diff $TESTS_FOLDER/.due$NUMBER $TESTS_FOLDER/.real$NUMBER)
            printf "$DIFF"
            printf "\n"
        done 
    fi
    if [ "$REVIEW" == "f" ]
    then
        for test in $TESTS_FOLDER/.fail*
        do
            NUMBER=$(echo $test | sed s/^.*fail//)
            printf "\n${RED} FAILED ${WHITE}$(head -1 $TESTS_FOLDER/.call$NUMBER)${GRAY}"
            cat $test
            printf "\n"
        done 
    fi
    if [ "$DO_INTERACTIVE" == "NO" ]
    then
        printf "" > $TESTS_FOLDER/.report
        for test in $TESTS_FOLDER/.fail*
        do
            NUMBER=$(echo $test | sed s/^.*fail//)
            printf "\n${RED} FAILED ${WHITE}$(head -1 $TESTS_FOLDER/.call$NUMBER)${GRAY}" >> $TESTS_FOLDER/.report
            printf "\n${GRAY}Differences found between ${GREEN}DUE${GRAY} and ${RED}REAL${GRAY} outputs:\n${GRAY}" >> $TESTS_FOLDER/.report
            DIFF=$(diff $TESTS_FOLDER/.due$NUMBER $TESTS_FOLDER/.real$NUMBER | sed s/^\>/'\\033[0;31m'\>/ | sed s/^\</'\\033[0;32m'\</ | sed s/$/'\\033[1;30m'/)
#            DIFF=$(diff $TESTS_FOLDER/.due$NUMBER $TESTS_FOLDER/.real$NUMBER)
            printf "\n$DIFF\n" >> $TESTS_FOLDER/.report
            cat $test >> $TESTS_FOLDER/.report
            printf "\n" >> $TESTS_FOLDER/.report
        done 
    fi
fi
# Remove auxiliary files
rm -f $TESTS_FOLDER/.out* $TESTS_FOLDER/.due* $TESTS_FOLDER/.real* $TESTS_FOLDER/.fail* $TESTS_FOLDER/.call*
printf "${WHITE}"
if [ "$FAILED_TESTS" == "YES" ]
then
    exit 1
fi