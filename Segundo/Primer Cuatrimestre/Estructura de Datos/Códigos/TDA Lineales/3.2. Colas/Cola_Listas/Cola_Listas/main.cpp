#include <iostream>
#include "Pila.hpp"
#include "Cola.hpp"
using namespace std;

int main() {

  Pila p;
  Cola c;
  char dato;
  cout << "Escriba una frase" << endl;
  while((dato=cin.get()) !='\n')
    if (dato != ' '){
      p.poner(dato);
      c.poner(dato);
    }
  bool palindromo = true;
  while(!p.vacia() && palindromo){
    if(c.frente() != p.tope())
      palindromo = false;
    p.quitar();
    c.quitar();
  }
  if (palindromo)
    cout << "La frase es un palíndromo" << endl;
  else
    cout << "La frase no es un palíndromo" << endl;
    
  return 0;
}
