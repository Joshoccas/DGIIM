/**
 * @file cantidad_letras.cpp
 * @brief Prueba el funcionamiento del TDA Dictionary
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include "dictionary.h"
#include "letters_set.h"
#include<fstream>

int main(int argc, char* argv[]){

    Dictionary dictionary;
    ifstream entrada;
    entrada.open(argv[1]);
    string cad;

    if(!entrada.is_open()){
        cout << "Error al abrir el fichero" << argv[1] << endl;
        cerr << "Error en open()" << endl;
        return -1;
    }

    while(entrada){
        entrada >> cad;
        dictionary.insert(cad);
    }

    entrada.close();

    LettersSet letters;
    ifstream entrada1;

    entrada1.open(argv[2]);
    entrada1 >> letters;
    entrada1.close();

    char letter = 'A';
    int totalletters = dictionary.getTotalLetters();

    cout << "Letra\tFAbs.\tFrel." << "\n";
    while(letter <= 'Z'){
        if(letters[letter].repetitions != 0) {
            int ocurrences = dictionary.getOcurrences(letter);
            cout << letter << "\t" << ocurrences << "\t" << (double)ocurrences/totalletters << "\n";
        }
        letter++;
    }

    return 0;
}