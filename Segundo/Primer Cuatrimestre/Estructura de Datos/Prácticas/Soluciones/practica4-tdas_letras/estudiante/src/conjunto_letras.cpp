/**
 * @file conjunto_letras.cpp
 * @brief Prueba el funcionamiento del TDA LettersSet
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include "letters_set.h"
#include <fstream>

int main(int argc, char* argv[]){

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

    int score = letters.getScore(argv[2]);

    cout << score << endl;
    return 0;
}