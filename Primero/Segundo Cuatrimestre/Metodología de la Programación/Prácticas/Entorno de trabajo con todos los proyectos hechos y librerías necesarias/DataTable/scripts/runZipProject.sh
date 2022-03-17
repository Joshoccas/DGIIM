#!/bin/bash
# Author: Luis Castillo Vidal L.Castillo@decsai.ugr.es
VERSION=1.0
# Helpinfo
HELPTEXT='# Script runZipProject.sh   \n
+ It is used to create backups of the project into the ./zip folder. These are the zip files that will be delivered to Prado by students. \n\n

+ The zip file takes its name from the folder name which contains the NetBeans project\n\n
'

# Load configuration & moves to the project root folder
if [ -d ../../Scripts ]
then
    source ../../Scripts/doConfig.sh $*
    runZipProject
else
    echo "Unable to find Scripts library"
fi

