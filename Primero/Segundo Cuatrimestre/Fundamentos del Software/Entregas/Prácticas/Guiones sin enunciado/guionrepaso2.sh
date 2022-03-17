#!/bin/bash
#Autor: José Alberto Hoces Castro
#Fecha: 12/04/2021
#Título: Ejercicio 7 Repaso 2

if (( $# != 3)); then echo "Para ejecutar este guión debes pasar 3 argumentos: un directorio, una letra y una palabra" && exit 1; else

	test -d $1
	
	if(( $? == 1 )); then 
		mkdir $1
	fi
	
	if [ "f" != $2 ] && [ "d" != $2 ]; then 
		exit 2
	else
		grep -rn $3 $1 > resultado.txt
		find $1 -type $2 >> resultado.txt
	fi
fi
