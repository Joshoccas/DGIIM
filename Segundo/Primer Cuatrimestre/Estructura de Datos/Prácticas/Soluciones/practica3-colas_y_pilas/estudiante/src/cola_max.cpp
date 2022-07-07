/**
 * @file cola_max.cpp
 * @brief  Archivo de implementación del programa cola con máximo
 * @author Guillermo Gómez Trenado
 */

#include <iostream>
#include "maxqueue.h"

int main (int argc, char ** argv) {
    MaxQueue queue;
    for (int i=1; i<argc; i++) {
        char * v = argv[i];
        if (v[0] == '.'){
            cout << queue.front() << endl;
            queue.pop();
        }
        else{
            int vint = atoi(v);
            queue.push(vint);
        }
    }
}