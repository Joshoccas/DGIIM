/**
 * @file palabras_longitud.cpp
 * @brief Prueba el funcionamiento del TDA Dictionary
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */
#include "dictionary.h"
#include<fstream>

int main(int argc, char* argv[]){

    Dictionary aux;
    ifstream entrada;
    entrada.open(argv[1]);

    if(!entrada.is_open()){
        cout << "Error al abrir el fichero" << argv[1] << endl;
        cerr << "Error en open()" << endl;
        return -1;
    }

    string cad;
    while(entrada){
        entrada >> cad;
        aux.insert(cad);
    }

    entrada.close();

    vector<string> v(aux.wordsOfLength(atoi(argv[2])));
    Dictionary result;

    for(int i = 0; i < v.size(); i++)
        result.insert(v[i]);

    Dictionary::iterator it;

    cout << "Palabras de longitud " << atoi(argv[2]) << endl;
    for(it = result.begin(); it != result.end(); ++it)
        cout << (*it) << endl;

    return 0;
}