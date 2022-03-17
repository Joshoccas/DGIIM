#!/bin/bash

if [ test -d $1 ] && [ test $2 =~ "^[0-9]+$" ]; then
	find $1 -size -$2 > archivosSizN.txt
else
	exit 1
fi


-------------------------------------------------------------------------------------

if [ $# == 1 ]; then
	if [ test -d $1 ]; then
		
		for archivo in $(ls $1)
		do
			if [ test -h $archivo ]; then
				echo "Enlace: $archivo"
			elif [ test -d $archivo ]; then
				echo "Subdirectorio: $archivo"
			elif [ test -f $archivo ]; then
				echo "Archivo regular: $archivo"
			fi
		done
	else
		echo "El directorio no existe"
	fi
else
	"Número de parámetros incorrecto"
fi

-------------------------------------------------------------------------------------

read TECLA

case "$TECLA" in
	[0-9]) echo "Fila 1" ;;
	Q|W|E|R|T|Y|U|I|O|P) echo "Fila 2" ;;
	A|S|D|F|G|H|J|K|L|Ñ) echo "Fila 3" ;;
	Z|X|C|V|B|N|M) echo "Fila 4" ;;
	*) echo "No pertecene a ninguna de las 4 filas" ;;
esac

-------------------------------------------------------------------------------------

read MES

case "$MES" in
	1|ENE) echo "Enero" ;;
	2|FEB) echo "Febrero" ;;
	3|MAR) echo "Marzo" ;;
	4|ABR) echo "Abril" ;;
	5|MAY) echo "Mayo" ;;
	6|JUN) echo "Junio" ;;
	7|JUL) echo "Julio" ;;
	8|AGO) echo "Agosto" ;;
	9|SEP) echo "Septiembre" ;;
	10|OCT) echo "Octubre" ;;
	11|NOV) echo "Noviembre" ;;
	12|DIC) echo "Diciembre" ;;
	*) echo "No se reconoce ningún mes correspondiente a lo indicado" ;;
esac

-------------------------------------------------------------------------------------

read numero

while [ $numero < 1 ] || [ $numero > 10 ];
do
	echo "Debe introducir un número entre 1 y 10"
	read numero
done

-------------------------------------------------------------------------------------

if [ $# == 3 ]; then
	dirname=$1
	num_files=$2
	basefilename=$3
	
	if [ $num_files >= 1 ] && [ $num_files <= 99 ]; then
	
		if [ test -d $dirname ]; then
			cd $dirname
			for count in `seq 1 1 $num_files`
			do
				touch $basefilename$count
			done
		else
			mkdir $dirname
			chmod u+rw $dirname
			
			cd $dirname
			for count in `seq 1 1 $num_files`
			do
				touch $basefilename$count
			done
		fi
	else
		echo "El número de archivos debe de estar entre 1 y 99"
		exit 1
	fi
else
	echo "El número de argumentos no es 3"
	exit 2
fi
