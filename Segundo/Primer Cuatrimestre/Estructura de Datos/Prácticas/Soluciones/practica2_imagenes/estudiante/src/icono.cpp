// Fichero: icono.cpp
// Crea una imagen de tamaño muy reducido a partir de una imagen original PGM.
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
    if (argc != 4){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: icono <FichImagenOriginal> <FichImagenDestino>\n"; //completar
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];
    int factor = atoi(argv[3]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Factor de reduccion: " << factor << endl;

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

    // Recortar el icono

    Image new_image(image.Subsample(factor));

    // Guardar la imagen resultado en el fichero
    if (new_image.Save(destino))
        cout  << "El icono se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}
