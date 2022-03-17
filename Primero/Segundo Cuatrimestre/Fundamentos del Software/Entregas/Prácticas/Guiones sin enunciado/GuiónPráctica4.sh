#!/bin/bash
#Autor: José Alberto Hoces Castro
#Fecha: 12/04/2021
#Título: Ejercicio Práctica 4

if(( $#==2 )) ; then
   
   echo "Parámetro 1: $1" && echo "Parámetro 2: $2"
   
   if(( $1 < $2 )) ; then
   echo "$1 es menor que $2."
   
     elif(( $1>$2 )) ; then
     echo "$1 es mayor que $2"
      
     else
     echo "$1 es igual que $2".
   fi;
      
else echo "Ha introducido más de dos parámetros" && exit 1
fi;
