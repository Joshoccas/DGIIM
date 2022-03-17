#!/bin/bash

if(( $# == 2 )); then
     if(( -e $2 )); then
      head $2 -3 > salida.txt
      echo "El archivo salida.txt contiene las tres primeras líneas del segundo archivo introducido"
     else
      echo "Se ha producido un error ya que el segundo argumento no es un archivo" && exit 1
     fi
     
     if(( -d $1 )); then
      echo "El directorio $1 contiene `ls $1|wc -l` archivos"
     else
      mkdir $1
     fi
     
     find $1 -readable >> salida.txt
     echo "De un total de `ls $1|wc -l` archivos, hay `find $1 -readable|wc -l` archivos con permiso de lectura"
     
else
 echo "Para hacer uso de este guión debes introducir 2 argumentos: primero un directorio después un archivo"
fi
