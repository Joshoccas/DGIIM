#include <iostream>
#include "Pila.hpp"

using namespace std;

int main() {
  Pila<char> p, q;
  char dato;
  
  cout << "Escriba una frase" << endl;
  while((dato=cin.get())!='\n')
    //p.poner(dato);
    p += dato;
  
  cout << "La escribimos del revés" << endl;
  while(!p.vacia()){
    cout << p.tope();
    q.poner(p.tope());
    //p.quitar();
    p--;
  }
  
  cout << endl << "La frase original era" << endl;
  while(!q.vacia()){
    cout << q.tope();
    //q.quitar();
    --q;
  }
  cout << endl;
  
  return 0;
}

