#!/bin/bash
if [ $1 ]
then
	if ! cmp -s ./tests/validation/$1.expected ./tests/output/$1.output;
	then
#	 wdiff -n -w $'\033[30;41m' -x $'\033[0m' -y $'\033[30;42m' -z $'\033[0m' ./tests/validation/$1.expected ./tests/output/$1.output
	wdiff -n ./tests/validation/$1.expected ./tests/output/$1.output
	fi
else
	echo "Call error. Please use getDifferenceOutput.sh <testname>"
fi
	 
