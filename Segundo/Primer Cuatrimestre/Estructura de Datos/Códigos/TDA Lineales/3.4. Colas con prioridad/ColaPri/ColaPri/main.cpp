#include <iostream>
#include "ColaPri.hpp"

using namespace std;

int main(){
  ColaPri c;
  int nota;
  string dni;
  
  cout << "Escriba una nota: ";
  cin >> nota;
  while(nota >=0 && nota <=10){
    cout << "Escriba un dni: ";
    cin >> dni;
    c.poner(dni, nota);
    cout << "Escriba una nota: ";
    cin >> nota;
  }
  cout << "DNIs ordenados por nota:" << endl;
  while(!c.vacia()){
    cout << "DNI: " << c.frente() << " Nota: "
         << c.prioridad_frente() << endl;
    c.quitar();
  }
  return 0;
}
