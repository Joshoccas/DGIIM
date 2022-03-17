#!/bin/bash
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
TOKEN="~~Dr.M~~"
# Constrain the information passed back to GTest
MAXROWS=15
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

#
# Generates Doxygen documentation and lauch firefox to read it
function runDoxygen() {
    # Runs doxygen
    doxygen $DOC_FOLDER/*.doxy
    # Display documentation
    firefox $DOC_FOLDER/html/index.html &
}

#
# Zip the project wihtout binaries, precompiled or any documentation
# Folders not to be included in the zip. Otherwise left empty
function runZipProject() {
    cdRootFolder
    # Some folders are not included into the ZIP
    EXCLUDED_FOLDERS="$PROJECT_NAME/nbproject/private/**\*  $PROJECT_NAME/dist/**\* $PROJECT_NAME/build/**\* $PROJECT_NAME/doc/html/**\* $PROJECT_NAME/doc/latex/**\*  $PROJECT_NAME/doc/markdown/**\*"
    # Remove older copies
    rm -f $ZIP_FOLDER/*.zip
    # Zips the project. It either zips the whole NetBeans folder, or just the folders inside it	
    echo "Zipping project"
    cd ..
    eval "zip -r $PROJECT_NAME/$ZIP_FOLDER/$ZIP_NAME.zip $PROJECT_NAME/* -x $EXCLUDED_FOLDERS"
}

#
# Autodocument the tests
function runTestsDocumentationEnumerate {
    CDRootFolder
    CheckFolder $DOC_FOLDER/markdown TEST_DOCUMENTATION
    OUTPUTBASE=$PROJECT_FOLDER/$DOC_FOLDER/markdown/
    rm -if $OUTPUTBASE/*.md
    OUTPUTTO=$OUTPUTBASE/ReadmeTests.md
    OUTPUTSUITE=""
    echo "# TESTS DOCUMENTATION FOR PROJECT "$PROJECT_NAME > $OUTPUTTO
    echo >> $OUTPUTTO
    echo "TESTS DOCUMENTATION FOR PROJECT "$PROJECT_NAME 
    cd $TESTS_FOLDER
    printf "Detecting suites: "
    for ftest in *.cpp 
    do        
        grep -v -e "//" -e "/\*" -e "\*/" $ftest | while read -r line; do 
             if echo $line | grep --quiet "TEST(";
            then 
                SUITE=$(echo $line | sed 's/^TEST(//;s/,.*$//')
                OUTPUTSUITE=$OUTPUTBASE/SUITE_$SUITE.md
                if [ ! -f $OUTPUTSUITE ]
                then
                    printf " "$SUITE
                    #echo "    > " >> $OUTPUTSUITE
                    #echo "    > ## **$SUITE** " >> $OUTPUTSUITE
                    #echo ">"  >> $OUTPUTSUITE
                fi
            fi
        done
    done
    printf "\n"
    printf "Processing tests files "
    for ftest in *.cpp 
    do
        printf "\n"$ftest"\n"
        grep -v -e "//" -e "/\*" -e "\*/" $ftest | while read -r line; do 
             if echo $line | grep --quiet "TEST(";
            then 
                SUITE=$(echo $line | sed 's/^TEST(//;s/,.*$//')
                OUTPUTSUITE=$OUTPUTBASE/SUITE_$SUITE.md
                TEST=$(echo $line | sed 's/^.*,//;s/).*$//')
                printf "\t$TEST\n"
                echo "1. [[$SUITE]] **$TEST** " >> $OUTPUTSUITE
                
            fi
            if echo $line | grep --quiet -e "ASSERT_" -e "EXPECT_" -e "CALL";
            then 
                 INVARIANT=$(echo $line | sed 's/^.*<<[ ]*\"//;s/\"[ ]*<<.*$//')
                 echo "      - $INVARIANT" >> $OUTPUTSUITE
            fi
        done
        printf "\n "
    done
    printf "\n"
    for tcase in $OUTPUTBASE/SUITE_*
    do
        cat $tcase >> $OUTPUTTO
    done
    okular $OUTPUTTO    &
}

function runTestsDocumentationSection {
    CDRootFolder
    CheckFolder $DOC_FOLDER/markdown TEST_DOCUMENTATION
    OUTPUTBASE=$PROJECT_FOLDER/$DOC_FOLDER/markdown/
    rm -if $OUTPUTBASE/*.md
    OUTPUTTO=$OUTPUTBASE/ReadmeTests.md
    OUTPUTSUITE=""
    echo "# TESTS DOCUMENTATION FOR PROJECT "$PROJECT_NAME > $OUTPUTTO
    echo >> $OUTPUTTO
    echo "TESTS DOCUMENTATION FOR PROJECT "$PROJECT_NAME 
    cd $TESTS_FOLDER
    printf "Detecting suites: "
    for ftest in *.cpp 
    do        
        grep -v -e "//" -e "/\*" -e "\*/" $ftest | while read -r line; do 
             if echo $line | grep --quiet "TEST(";
            then 
                SUITE=$(echo $line | sed 's/^TEST(//;s/,.*$//')
                OUTPUTSUITE=$OUTPUTBASE/SUITE_$SUITE.md
                if [ ! -f $OUTPUTSUITE ]
                then
                    printf " "$SUITE
                    echo "    " >> $OUTPUTSUITE
                    echo "## $SUITE " >> $OUTPUTSUITE
                    #echo ">"  >> $OUTPUTSUITE
                fi
            fi
        done
    done
    printf "\n"
    printf "Processing tests files "
    for ftest in *.cpp 
    do
        printf "\n"$ftest"\n"
        grep -v -e "//" -e "/\*" -e "\*/" $ftest | while read -r line; do 
             if echo $line | grep --quiet "TEST(";
            then 
                SUITE=$(echo $line | sed 's/^TEST(//;s/,.*$//')
                OUTPUTSUITE=$OUTPUTBASE/SUITE_$SUITE.md
                TEST=$(echo $line | sed 's/^.*,//;s/).*$//')
                printf "\t$TEST\n"
                echo "    " >> $OUTPUTSUITE
                echo "### $TEST " >> $OUTPUTSUITE                
            fi
            if echo $line | grep --quiet -e "ASSERT_" -e "EXPECT_" -e "CALL";
            then 
                 INVARIANT=$(echo $line | sed 's/^.*<<[ ]*\"//;s/\"[ ]*<<.*$//')
                 echo "1. $INVARIANT" >> $OUTPUTSUITE
            fi
        done
        printf "\n "
    done
    printf "\n"
    for tcase in $OUTPUTBASE/SUITE_*
    do
        cat $tcase >> $OUTPUTTO
    done
        for ftest in *.cpp 
    do
        grep "//INV" $ftest | sed 's://INV::' >> $OUTPUTTO
    done
    #okular $OUTPUTTO    &
}


function runTestsDocumentationTable {
    CDRootFolder
    CheckFolder $DOC_FOLDER/markdown TEST_DOCUMENTATION
    OUTPUTBASE=$PROJECT_FOLDER/$DOC_FOLDER/markdown/
    rm -if $OUTPUTBASE/*.md
    OUTPUTTO=$OUTPUTBASE/ReadmeTests.md
    OUTPUTSUITE=""
    echo "# TESTS DOCUMENTATION FOR PROJECT "$PROJECT_NAME > $OUTPUTTO
    echo "| **SUITE** | **TEST** | **DESCRIPTION** |" >> $OUTPUTTO    
    echo "| :---- | :---- | :---- |" >> $OUTPUTTO    
    echo "TESTS DOCUMENTATION FOR PROJECT "$PROJECT_NAME 
    cd $TESTS_FOLDER
    printf "Detecting suites: "
    for ftest in *.cpp 
    do        
        grep -v -e "//" -e "/\*" -e "\*/" $ftest | while read -r line; do 
             if echo $line | grep --quiet "TEST(";
            then 
                SUITE=$(echo $line | sed 's/^TEST(//;s/,.*$//')
                OUTPUTSUITE=$OUTPUTBASE/SUITE_$SUITE.md
                if [ ! -f $OUTPUTSUITE ]
                then
                    printf " "$SUITE
                    echo "| **$SUITE** | | |" >> $OUTPUTSUITE
                fi
            fi
        done
    done
    printf "\n"
    printf "Processing tests files "
    for ftest in *.cpp 
    do
        printf "\n"$ftest"\n"
        grep -v -e "//" -e "/\*" -e "\*/" $ftest | while read -r line; do 
             if echo $line | grep --quiet "TEST(";
            then 
                SUITE=$(echo $line | sed 's/^TEST(//;s/,.*$//')
                OUTPUTSUITE=$OUTPUTBASE/SUITE_$SUITE.md
                TEST=$(echo $line | sed 's/^.*,//;s/).*$//')
                printf "\t$TEST\n"
                echo "|  | $TEST |   |" >> $OUTPUTSUITE
#                    echo "   TEST" $TEST
            fi
            if echo $line | grep --quiet -e "ASSERT_" -e "EXPECT_" -e "CALL";
            then 
                 INVARIANT=$(echo $line | sed 's/^.*<<[ ]*\"//;s/\"[ ]*<<.*$//')
                 echo "|  |  | $INVARIANT |" >> $OUTPUTSUITE
            fi
        done
        printf "\n "
    done
    printf "\n"
    for tcase in $OUTPUTBASE/SUITE_*
    do
        cat $tcase >> $OUTPUTTO
    done
    okular $OUTPUTTO    &
}

function runTestsDocumentation {
	runTestsDocumentationSection
}
#function runTestsDocumentation {
#    CDRootFolder
#    CheckFolder $DOC_FOLDER/markdown TEST_DOCUMENTATION
#    echo "# TESTS DOCUMENTATION FOR PROJECT "$PROJECT_NAME > $PROJECT_FOLDER/$DOC_FOLDER/markdown/ReadmeTests.md
#    OUTPUTTO=$PROJECT_FOLDER/$DOC_FOLDER/markdown/ReadmeTests.md
#    cd $TESTS_FOLDER
#    for ftest in *.cpp 
#    do
#        grep -v -e "//" -e "/\*" -e "\*/" $ftest | while read -r line; do 
#             if echo $line | grep --quiet "TEST(";
#                then 
#                    SUITE=$(echo $line | sed 's/^TEST(//;s/,.*$//')
#                    if ! grep --quiet $SUITE $OUTPUTTO;
#                    then
#                        echo "1. ## Suite " $SUITE >> $OUTPUTTO
#                        echo >> $OUTPUTTO
#                        echo "Processing SUITE " $SUITE
#                    fi
#                    TEST=$(echo $line | sed 's/^.*,//;s/).*$//')
#                    if ! grep --quiet $TEST $OUTPUTTO;
#                    then
#                        echo "   A. ## Test " $TEST >> $OUTPUTTO
#                        echo >> $OUTPUTTO
#                        echo "   TEST" $TEST
#                    fi
#                fi
#		      if echo $line | grep --quiet -e "ASSERT_" -e "EXPECT_" -e "CALL";
#            then 
#	             INVARIANT=$(echo $line | sed 's/^.*<<[ ]*\"//;s/\"[ ]*<<.*$//')
#	             echo "      1. "$INVARIANT >> $OUTPUTTO
#	             echo >> $OUTPUTTO
#            fi
#        done
#    done
#    okular $OUTPUTTO    &
#}

function viewHelp() {
	echo -e $1 | cat | mdless
}

function doDrMemory() {
	# path to mem leak checker
	PATHLEAKCHEK=/usr/local/drmemory/bin/
	OUTPUT=./tests/output/$2
	INPUT=./tests/validation/$2
	# output patterns
	CHARS="[a-zA-Z0-9\_\-]"
	TOKEN="~~Dr\.M~~"
	NO_INIT="UNINITIALIZED READ: reading "
	BAD_READ="UNADDRESSABLE ACCESS beyond heap bounds: reading"
	BAD_WRITE="UNADDRESSABLE ACCESS beyond heap bounds: writing"
	MEM_LEAK="[0-9]* LEAK [0-9]* "
	BAD_FREE="INVALID HEAP ARGUMENT:"
	SOURCE="$CHARS$CHARS*\.cpp"
	touch $INPUT.keyboard 
		echo "" 	> $OUTPUT.mleaks.full
		echo "" 	> $OUTPUT.mleaks.simplified
    	echo "" 	> $OUTPUT.mleaks.compact		
	# Execute binary
	echo -e "MEMORY LEAK REPORT BY Dr Memory \n\n$(date)\n\n" >$OUTPUT.mleaks.full	
	BINARY=${@:3}

	$PATHLEAKCHEK/drmemory -light -check_leaks -- $BINARY < $INPUT.keyboard 1> /dev/null 2>> $OUTPUT.mleaks.full
	# Preapare three reports full (complete) simplified (only remarkable) or compact(only errors miniverbosa)

	echo  -e "# SIMPLIFIED MEMORY LEAK REPORT BY Dr Memory \n\n$(date)\n\n" > $OUTPUT.mleaks.simplified.md	

	if ! grep --quiet -i "NO ERRORS FOUND" $OUTPUT.mleaks.full;
	then

		cat   $OUTPUT.mleaks.full | grep -i -e "$SOURCE" -e "$NO_INIT"  -e "$BAD_READ" -e "$BAD_WRITE" -e "$MEM_LEAK" -e "$BAD_FREE"  | sed "s/^.*\/\($SOURCE\:[0-9]*\).*$/    a. \1/;s/^.* Error #[0-9]*: \(.*\).*$/1. \*\*\1\*\*/" >> $OUTPUT.mleaks.simplified.md
		cat   $OUTPUT.mleaks.full | grep -i -e "$SOURCE" -e "$NO_INIT"  -e "$BAD_READ" -e "$BAD_WRITE" -e "$MEM_LEAK" -e "$BAD_FREE" | sed "s/^.*$NO_INIT.*$/#[---${!NO_INIT*}]/;s/^.*$BAD_READ.*$/#[---${!BAD_READ*}]/;s/^.*$BAD_WRITE.*/#[ ${!BAD_WRITE*}]/;s/^.*$MEM_LEAK.*$/#[--${!MEM_LEAK*}]/;s/^.*$BAD_FREE.*$/#[--${!BAD_FREE*}]/;s/^.*\/\(.*$SOURCE\:[0-9]*\).*$/(\1)/;" | head -n $MAXROWS >> $OUTPUT.mleaks.compact		
	fi

}

function doValgrind() {
	# path to mem leak checker
	PATHLEAKCHEK=/usr/bin/
	OUTPUT=./tests/output/$2
	INPUT=./tests/validation/$2
	# output patterns
	CHARS="[a-zA-Z0-9\_\-]"
	TOKEN="==[0-9]*=="
	NO_INIT="uninitialised value(s)"
	BAD_READ="Invalid read of size [0-9]*"
	BAD_WRITE="Invalid write of size [0-9]*"
	MEM_LEAK="[0-9]* bytes in [0-9]* blocks are definitely lost"
	BAD_FREE="Mismatched free"
	INV_FREE="Invalid free"
	CORE_DUMP="Process terminating"
	SOURCE="$CHARS$CHARS*\.cpp"
	touch $INPUT.keyboard 
	echo "" 	> $OUTPUT.mleaks.full
	echo "" 	> $OUTPUT.mleaks.simplified
  	echo "" 	> $OUTPUT.mleaks.compact
	# Execute binary
	echo -e "MEMORY LEAK REPORT BY Valgrind \n\n$(date)\n\n" >$OUTPUT.mleaks.full	
	BINARY=${@:3}

	echo "#!/bin/bash" > $OUTPUT.mleaks.sh
	echo "$PATHLEAKCHEK/valgrind --leak-check=full $BINARY < $INPUT.keyboard 1> /dev/null 2>> $OUTPUT.mleaks.full" >> $OUTPUT.mleaks.sh
	#chmod u+x $OUTPUT.mleaks.sh
	source $OUTPUT.mleaks.sh

#	$PATHLEAKCHEK/valgrind --leak-check=full $BINARY < $INPUT.keyboard 1> /dev/null 2>> $OUTPUT.mleaks.full
	# Preapare three reports full (complete) simplified (only remarkable) or compact(only errors miniverbosa)

	echo  -e "# SIMPLIFIED MEMORY LEAK REPORT BY Valgrind \n\n$(date)\n\n" > $OUTPUT.mleaks.simplified.md	

	if ! grep --quiet -i "ERROR SUMMARY: 0" $OUTPUT.mleaks.full;
	then

		cat   $OUTPUT.mleaks.full | grep -i -e "$SOURCE" -e "$NO_INIT"  -e "$BAD_READ" -e "$BAD_WRITE" -e "$MEM_LEAK" -e "$BAD_FREE" -e "$INV_FREE" -e "$CORE_DUMP" | sed "s/^.*\(($SOURCE\:[0-9]*)\).*$/    a. \1/;s/^.*$TOKEN \(.*\)$/1. \*\*\1\*\*/;" >> $OUTPUT.mleaks.simplified.md
		cat   $OUTPUT.mleaks.full | grep -i -e "$SOURCE" -e "$NO_INIT"  -e "$BAD_READ" -e "$BAD_WRITE" -e "$MEM_LEAK" -e "$BAD_FREE" -e "$CORE_DUMP"| sed "s/^.*$NO_INIT.*$/#[---${!NO_INIT*}]/;s/^.*$BAD_READ.*$/#[--${!BAD_READ*}]/;s/^.*$BAD_WRITE.*/#[-${!BAD_WRITE*}]/;s/^.*$MEM_LEAK.*$/#[--${!MEM_LEAK*}]/;s/^.*$BAD_FREE.*$/#[--${!BAD_FREE*}]/;s/^.*$INV_FREE.*$/#[--${!INV_FREE*}]/;s/^.*$CORE_DUMP.*$/#[-${!CORE_DUMP*}]/;s/^.*\(($SOURCE\:[0-9]*)\).*$/\1/;" | head -n $MAXROWS >> $OUTPUT.mleaks.compact		
	fi

}

function doDrMemoryExtended() {
	PATHLEAKCHEK=/usr/local/drmemory/bin/
	TOKEN="~~Dr.M~~ "
	if [ "$2" == "-" ]
	then
		OUTPUT=./memleak
	else
		OUTPUT=./tests/output/$2
	fi
	touch $INPUT.keyboard 
	BINARY=${@:3}
	$PATHLEAKCHEK/drmemory -light -check_leaks -- $BINARY < $INPUT.keyboard 1> /dev/null 2> $OUTPUT.output

	echo "" 	> $OUTPUT.mleaks
	if ! grep --quiet -i "NO ERRORS FOUND" $OUTPUT.output;
	then
		echo "MEMORY LEAK REPORT BY DRMemory" >> $OUTPUT.mleaks
		cat $OUTPUT.output | grep -i -e "ERRORS FOUND" | sed "s/$TOKEN//" > $OUTPUT.mlaux
#		cat $OUTPUT.output | grep -i -e "ERROR #" | sed "s/$TOKEN//"  >> $OUTPUT.mleaks
	cat $OUTPUT.output | grep -i -e "ERROR #" -e "# [0-9].*\.cpp"| sed "s/$TOKEN//"  >> $OUTPUT.mlaux
		head -10 $OUTPUT.mlaux > $OUTPUT.mleaks
	fi
#	cat $OUTPUT.mleaks
}

function doValgrindExtended() {
	PATHLEAKCHEK=/usr/bin/
	TOKEN="==[0-9]*=="
	if [ "$2" == "-" ]
	then
		OUTPUT=./memleak
	else
		OUTPUT=./tests/output/$2
	fi
	touch $INPUT.keyboard 
	BINARY=${@:3}
	$PATHLEAKCHEK/valgrind --leak-check=full $BINARY < $INPUT.keyboard 1> /dev/null 2> $OUTPUT.output
	echo "" 	> $OUTPUT.mleaks
	if ! grep --quiet -i "ERROR SUMMARY: 0" $OUTPUT.output;
	then
		echo "MEMORY LEAK REPORT BY Valgrind" >> $OUTPUT.mleaks
		cat $OUTPUT.output | grep -i -e "INVALID READ" -e "main\.cpp" -e "uninitialised value(s)" -e "lost in loss" -e "invalid write" -e "Mismatched"| sed "s/$TOKEN//" > $OUTPUT.mlaux		
		head -10 $OUTPUT.mlaux > $OUTPUT.mleaks
		#cat tests/output/TestSylvia.mleaks | sed "N;s/^.*uninitialised value(s)\n.*(/UNINIT /;s/)//" |  sed "N;s/^.*Invalid read\n.*(/UNINIT /;s/)//"
		#cat $OUTPUT.output | grep -i -e "INVALID READ" -e "main\.cpp" -e "uninitialised value(s)" -e "lost in loss" -e "invalid write" -e "Mismatched"| sed "s/$TOKEN//" >> $OUTPUT.mleaks
		#cat $OUTPUT.output | grep -i -e "INVALID READ" -e "uninitialised value(s)" -e "lost in loss" -e "invalid write" -e "Mismatched"| sed "s/$TOKEN//" >> $OUTPUT.mleaks
			fi
#	cat $OUTPUT.mleaks

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
# Folder to store tests
CheckFolder tests/ TESTS_FOLDER
# Folder to store tests-data
CheckFolder $TESTS_FOLDER/validation TESTS_VALIDATION_FOLDER 
# Folder to store tests-output
CheckFolder $TESTS_FOLDER/output TESTS_OUTPUT_FOLDER

# Colors to be used in output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
GRAY='\033[1;30m'
WHITE='\033[1;37m'
# Use of memory leak detector
USE_VALGRIND=NO
# Seconds to wait before killing a (possibly) hang program
SECS_WAIT=15
# Executes the script in interactive or batch mode
DO_INTERACTIVE=YES
# Forces the name of the ZIP. If left empty, the zip uses the name of the root foder
ZIP_NAME=$PROJECT_NAME

if [ "$1" == "-help" ] || [ "$1" == "-h" ]
then
	viewHelp "$HELPTEXT"
	exit 0	
fi


