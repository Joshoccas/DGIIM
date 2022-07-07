/**
 * @file bolsa_letras.cpp
 * @brief Prueba el funcionamiento del TDA LettersBag
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include "letters_bag.h"
#include<fstream>

int main(int argc, char** argv){

    LettersSet letters;
    ifstream entrada;
    entrada.open(argv[1]);

    if(!entrada.is_open()){
        cout << "Error al abrir el fichero" << argv[1] << endl;
        cerr << "Error en open()" << endl;
        return -1;
    }

    entrada >> letters;
    entrada.close();

    LettersBag letterbag(letters);

    while(letterbag.size() != 0)
        cout << letterbag.extractLetter() << endl;

    return 0;
}