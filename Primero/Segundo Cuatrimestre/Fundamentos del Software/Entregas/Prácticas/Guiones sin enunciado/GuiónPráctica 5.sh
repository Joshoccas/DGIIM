#!/bin/bash
#Autor: José Alberto Hoces Castro
#Fecha: 12/04/2021
#Descripción: Menú que nos permite efectuar una suma, resta o multiplicación de las dos cifras que nosotros deseemos y que finaliza si se le introduce 4 (ya que es la opción de salir)

res=0
operacion=1

while [ $operacion != 4 ]
do

echo "Introduce la primera cifra"
read n1
echo "Introduce la segunda cifra"
read n2
echo "Los números introducidos son: $n1 y $n2. Escoge una de las cuatro opciones: "

echo "1.Sumar números"
echo "2.Restar números"
echo "3.Multiplicar números"
echo "4.Salir"
read operacion
case $operacion in
    1)res=`expr $n1 + $n2`
     echo "Resultado ="$res;;
    2)res=`expr $n1 - $n2`
     echo "Resultado = "$res;;
    3)res=`expr $n1 \* $n2`
     echo "Resultado = "$res;;
esac
done
