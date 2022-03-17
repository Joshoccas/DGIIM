#!/bin/bash
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
# Original file location, without header
SOURCEFILENAME=./data/dataset-ecommerceFULL.csv
# Helpinfo
HELPTEXT='# Script runSampleEcommerce.sh   \n
runSampleEcommerce [<year> | all] [Q1|Q2|Q3|Q4|S1|S2|all] [<size>|all]
\n\n
+ It extracts <size> tuples of $SOURCEFILENAME sorted chronologgically froom the period specified, year and portion of the year\n
+ `runSampleEcommerce.sh all all all` extracts all tuples \n
+ `runSampleEcommerce.sh 2020 Q2 100` extracts the first 100 tuples of the first quarter of 2020 \n
'

# Load configuration & moves to the project root folder
if [ -d ../Scripts ]
then
    source ../Scripts/doConfig.sh $*
    # Process parameters
	 DESTFILENAME=./tests/validation/ECommerce_$1_$2_$3.input
	 TMPFILENAME=./data/.tmp.csv
    if [ "$1" == "all" ]
    then
    		YEAR="20[0-9][0-9]"
    else
    		YEAR="$1"
    fi
    case "$2" in
    	"Q1")
    		PERIOD="0[123]"
    		;;
    	"Q2")
    		PERIOD="0[456]"
    		;;
    	"Q3")
    		PERIOD="0[789]"
    		;;
    	"Q4")
    		PERIOD="1[012]"
    		;;
    	"S1")
    		PERIOD="0[123456]"
    		;;
    	"S2")
    		PERIOD="[01][789012]"
    		;;
    	*)
    		PERIOD="[01][0-9]"
 	 esac
	 echo "^$YEAR-$PERIOD-"  $SOURCEFILENAME
	 grep -e "^$YEAR-$PERIOD-"  $SOURCEFILENAME | sort -R > $TMPFILENAME
    if [ "$3" == "all" ]
    then
    		SIZE=$(wc -l $TMPFILENAME)
    else
    		SIZE=$3
    fi

    	echo "File "$SOURCEFILENAME" has $(wc -l $SOURCEFILENAME | awk '{ print $1 }') tuples"
    	echo "Selected period has $(wc -l $TMPFILENAME | awk '{ print $1 }') tuples"
 		echo "Sampling "$3" tuples of year "$1" period "$2" into "$DESTFILENAME
 		echo $3 > $DESTFILENAME
 	 	head -n $SIZE $TMPFILENAME >> $DESTFILENAME
else
    printf "\n${RED}Unable to find Scripts library"
    printf "${WHITE}"
fi

