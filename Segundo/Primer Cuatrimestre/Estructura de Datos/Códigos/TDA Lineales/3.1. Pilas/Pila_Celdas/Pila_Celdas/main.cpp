#include <iostream>
#include "Pila.hpp"

using namespace std;

int main() {
  Pila p, q, r;
  char dato;
  
  cout << "Escriba una frase" << endl;
  while((dato=cin.get())!='\n')
    p.poner(dato);
  
  cout << "La escribimos del revés" << endl;
  while(!p.vacia()){
    cout << p.tope();
    q.poner(p.tope());
    p.quitar();
  }
  
//    r = p = q;
  
  cout << endl << "La frase original era" << endl;
  while(!q.vacia()){
    cout << q.tope();
    q.quitar();
  }
  cout << endl;
  
  
//    cout << "La frase original era" << endl;
//    while(!r.vacia()){
//      cout << r.tope();
//      r.quitar();
//    }
//    cout << endl;
  
  return 0;
}

