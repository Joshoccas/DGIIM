// Fichero: zoom.cpp
// Genera una nueva imagen resultado de aplicar zoom 2X
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    Image image;
    int fila, col; // indican la coordenada (sobre la imagen  original) de la esquina superior izquierda
    // de la subimagen que se va a extraer.
    int lado; // Número de filas y columnas que tendrá el recorte sobre el que se hace zoom

    // Comprobar validez de la llamada
    if (argc != 6){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: zoom <FichImagenOriginal> <FichImagenDestino> <FilaSupIzq> <ColumnaSupIzq> <LadoImagenAumentada>\n";
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

    // Leer los demás parámetros especificados

    fila = atoi(argv[3]);
    col = atoi(argv[4]);
    lado = atoi(argv[5]);

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // Hacer zoom a la imagen

    Image resultado(image.Crop(fila,col,lado,lado));
    resultado = resultado.Zoom2X();

    // Guardar la imagen resultado en el fichero
    if (resultado.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}