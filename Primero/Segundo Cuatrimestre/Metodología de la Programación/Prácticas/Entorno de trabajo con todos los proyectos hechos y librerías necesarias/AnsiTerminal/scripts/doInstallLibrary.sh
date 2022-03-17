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

# Copy library's shared files into local directory
if ls ./dist/Debug/GNU-Linux/*.a;
then
    LIBRARY_FILE=$(ls ./dist/Debug/GNU-Linux/*.a)
    INCLUDE_FILES=$(ls ./include/*.h)
    echo "Updating $LIBRARY_FILE" 
    cp $LIBRARY_FILE $LOCAL_LIB_FOLDER/
    echo "Updating $INCLUDE_FILES"
    cp ./include/*.h $LOCAL_H_FOLDER
    zip -j "$ZIP_FOLDER/$ZIP_NAME"lib.zip $LIBRARY_FILE $INCLUDE_FILES 
else
    echo "No library files found"
fi