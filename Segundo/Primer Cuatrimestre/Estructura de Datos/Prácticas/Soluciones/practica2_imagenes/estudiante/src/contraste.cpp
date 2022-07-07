// Fichero: contraste.cpp
// Modifica el contraste de una imagen
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    Image image;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: contraste <FichImagenOriginal> <FichImagenDestino> <UmbralInferiorIn> <UmbralSuperiorIn> <UmbralInferiorOut> <UmbralSuperiorOut>\n";
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // Leer el resto de parámetros especificados

    byte e1 = atoi(argv[3]);
    byte e2 = atoi(argv[4]);
    byte out1 = atoi(argv[5]);
    byte out2 = atoi(argv[6]);

    // Modificar el contraste

    image.AdjustContrast(e1,e2,out1,out2);

    // Guardar la imagen resultado en el fichero
    if (image.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}

