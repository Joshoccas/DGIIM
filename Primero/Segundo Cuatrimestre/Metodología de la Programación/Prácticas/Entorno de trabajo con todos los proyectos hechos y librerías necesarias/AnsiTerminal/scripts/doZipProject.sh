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

# Folders not to be included in the zip. Otherwise left empty
if [ $ZIP_NAME == $PROJECT_NAME ]
then
    EXCLUDED_FOLDERS="$PROJECT_NAME/nbproject/private/**\*  $PROJECT_NAME/dist/**\* $PROJECT_NAME/build/**\* $PROJECT_NAME/doc/html/**\* $PROJECT_NAME/doc/latex/**\*"
else
    EXCLUDED_FOLDERS="nbproject/private/**\*  dist/**\* build/**\* doc/html/**\* doc/latex/**\*"
fi
# Remove older copies
rm $ZIP_FOLDER/*.zip
# Zips the project. It either zips the whole NetBeans folder, or just the folders inside it	
echo "Zipping project"
if [ $ZIP_NAME == $PROJECT_NAME ]
then
    cd ..
    eval "zip -r $PROJECT_NAME/$ZIP_FOLDER/$ZIP_NAME.zip $PROJECT_NAME/* -x $EXCLUDED_FOLDERS"
    cd -
else
    eval "zip -r $ZIP_FOLDER/$ZIP_NAME.zip * -x $EXCLUDED_FOLDERS"
fi