/**
 * @file bolsa.cpp
 * @brief Prueba el funcionamiento del TDA Bag
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "bag.h"

using namespace std;

int main(int argc, char *argv[])
{
  // // Inicializamos el generador de números aleatorios
  srand(time(NULL));

  // // Creamos una bolsa de caracteres si el primer argumento es una C
  if (toupper(argv[1][0]) == 'C') {
     Bag <string> bag;

  //   // Metemos todos los argumentos en la bolsa
     for (int i = 2; i < argc; ++i) {
       bag.add(argv[i]);
     }

  //   // Los extraemos aleatoriamente y los imprimimos hasta que se nos quede la
  //   // bolsa vacía
     while(bag.size() > 0){
       cout << bag.get() << endl;
     }

  //   // Creamos una bolsa de enteros si el primer argumento es una I
   } else if (toupper(argv[1][0]) == 'I') {
     Bag <int> bag;

  //   // Metemos todos los argumentos en la bolsa
     for (int i = 2; i < argc; ++i) {
       bag.add(atoi(argv[i]));
     }

  //   // Los extraemos aleatoriamente y los imprimimos hasta que se nos quede la
  //   // bolsa vacía
     while(bag.size() > 0){
       cout << bag.get() << endl;
     }
   }

   return 0;
}

