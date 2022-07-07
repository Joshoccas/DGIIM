#!/bin/bash

TELEGRAM_USER_ID=1355682542
USER_ID=77142621
# GROUP_ID="GIIA3"
# GROUP_ID="GIIB1"
# GROUP_ID="GIIB2"
GROUP_ID="DGIIMA2"

JUDGE_URL="mcs.ugr.es"

# NO MODIFICAR ESTA VARIABLE, INDICA EL NOMBRE DE LA ENTREGA
EXERCISE='ej01_imagenes'

if [[ $TELEGRAM_USER_ID -eq 0 ]]
then
    echo "El ID de usuario de Telegram no está bien configurado. Debes hablar"
    echo "con el bot de Telegram del Juez Online (@JuezOnlineEDbot), al que"
    echo "puedes acceder con la siguiente URL: https://t.me/JuezOnlineEDbot,"
    echo "abrir este script y sustituir el valor de la variable TELEGRAM_USER_ID"
    echo "por el número que te especifique el bot"
    exit 1
fi

if [[ $USER_ID -eq 0 ]]
then
    echo "El DNI del usuario que realiza la entrenga no está bien"
    echo "configurado. Debes abrir este script y modificar la variable USER_ID"
    echo "con el DNI del usuario que va a realizar la entrega SIN LETRA. Los dos"
    echo "miembros de la pareja deberán utilizar el mismo DNI, que deberá"
    echo "coincidir con el DNI del alumno que realiza la entrega en PRADO."
    exit 1
fi

if [[ "$JUDGE_URL" = "localhost" ]]
then
    echo "La URL del juez no está bien configurada. Debes abrir este script y"
    echo "modificar la variable JUDGE_URL con la dirección que te ha indicado tu"
    echo "profesor. Si no te ha indicado ninguna dirección, ponte en contacto"
    echo "con él para que lo haga."
    exit 1
fi

zip -L > /dev/null
if [[ $? -ne 0 ]]
then
    echo "El programa zip no está instalado. Debes instalar este programa"
    echo "para que el script funcione correctamente. Si trabajas en un"
    echo "entorno linux, puedes instalar el programa con el comando:"
    echo "sudo apt-get install -y zip"
    exit 1
fi

if [ -f submission.zip ]
then
    echo "Ya existe un archivo submission.zip en el directorio en el que estás,"
    echo "probablemente propio de un intento de entrega anterior. Este script borrará"
    echo "dicho archivo si continúas. Si deseas conservar ese archivo, muévelo"
    echo "antes de continuar o cambia su nombre. Si no quieres guardar el"
    echo "archivo, puedes continuar sin problemas."
    read -p "Quieres continuar con el envío de la práctica? [Y/N]: " -n 1 -r
    echo    # (optional) move to a new line
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        echo "Borrando el archivo y continuando la ejecución..."
        rm submission.zip
    else
        echo "Cancelando el envío..."
        exit 1
    fi
fi

echo "Comprimiendo los archivos de la práctica..."
zip -r submission.zip Doxyfile.in estudiante/doc estudiante/src estudiante/include

echo "Enviando los archivos al juez online..."
curl -X POST -H "accept: application/json" \
     -H "Content-Type: multipart/form-data" \
     -F "uploaded_file=@submission.zip;type=application/x-zip-compressed" \
     "http://$JUDGE_URL:8000/assignments/$EXERCISE/$GROUP_ID/$USER_ID?telegram=$TELEGRAM_USER_ID" > /dev/null


echo "Los archivos se han enviado al juez. Debes recibir el mensaje de"
echo "resultados por Telegram en unos minutos. Si no recibes dicho mensaje,"
echo "intenta de nuevo el envío. Si tras un segundo envío sigues sin recibir"
echo "una respuesta, contacta con tu profesor para arreglar el posible"
echo "problema."
