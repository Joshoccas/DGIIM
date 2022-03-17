#!/bin/bash
#Autor: José Alberto Hoces Castro
#Fecha: 03/05/2021

if [ $# == 2 ]; then

	if [ $1 =~ [a-z] ] && [ test -d $2 ]; then
		
	    case $1 in
	    [ae])
	    	total=`find $2 -name "$1*"|wc -l`
	     	echo "Hay un total de $total archivos que empiezan por la letra $1 en el directorio $2";;
	    [iou])
	    	nombre="$2copy.tar"
	    	
	    	if [ test -f $nombre ]; then
	    		echo "La copia de seguridad a realizar ya existe"
	    	else
	    		tar -cvf $nombre $2
	    	fi;;
	esac

	else
		echo "Hay un fallo en los argumentos. EL primero debe ser una letra minúscula y el segundo un directorio"
		exit 1
	fi;
else
	echo "No se han introducido dos argumentos"
	exit 2
fi;
