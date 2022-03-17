#!/bin/bash

opcion=0

while [ opcion != 4 ]
do
	echo "Seleccione una opción: "
	echo "1)Sumar números"
	echo "2)Restar números"
	echo "3)Multiplicar números"
	echo "4)Salir"
	
	read opcion
	
	case $opcion in 
		1)read num1
		  read num2
		  echo "Los números introducidos son $num1 y $num2 y su suma es $(($num1 $num2))";;
		2)read num1
		  read num2
		  echo "Los números introducidos son $num1 y $num2 y su diferencia es $(($num1 - $num2))";;
		3)read num1
		  read num2
		  echo "Los números introducidos son $num1 y $num2 y su producto es $(($num1 * $num2))";;
		4)exit 1;;
	esac
done
