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
# Remember the currect folder to come back to it at the end of the script
BASE=$(pwd)
echo "Exploring for other NetBeans project in the same subfolder ..."
cd ..
# Copies the scripts in this folder into any other brother folder
for folder in $(ls)
do
    # Only copies scripts into Netbeans projects which also uses the folder scripts/
    if [ -d $folder/nbproject ] && [ -d $folder/scripts ] && [ ! $folder == $PROJECT_NAME ]
    then
        echo "Found Netbeans folder with scripts at "$folder" ... Updating scripts"
        cp $BASE/scripts/*.sh $folder/scripts
    fi
done 
cd $BASE
