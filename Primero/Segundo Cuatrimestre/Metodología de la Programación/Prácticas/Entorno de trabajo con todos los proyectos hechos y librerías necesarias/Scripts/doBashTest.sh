#!/bin/bash
ME=$(whoami)
echo -e "Hola <cosa>\n¿Cómo estás <cosa>?" > f1.tb
echo -e "Hola cosa\n¿Cómo estás cosa?" > f2.tb
echo -e "Hola cosa>\n¿Cómo estás cosa>?" > f3.tb
for fi in *.tb
do
	if grep --quiet "<cosa>" $fi;
	then
		echo 
		echo "Por favor, comprueba que este es tu nombre de usuario en esta máquina: "$ME
		echo "Y comprueba que lo siguiente que aparece es un mensaje de bienvenida"
		cat $fi | sed "s/<cosa>/$ME/" 
		echo
	fi
done

