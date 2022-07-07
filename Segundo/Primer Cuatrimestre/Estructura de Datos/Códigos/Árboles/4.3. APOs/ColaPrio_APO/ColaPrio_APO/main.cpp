#include <iostream>
#include <string>
#include "ColaPri.hpp"

using namespace std;

int main(){
  ColaPri<pair<float,string> > c;
  pair<float,string> pareja;

  cout << "Escriba una nota: ";
  cin >> pareja.first;
  while(pareja.first >=0 && pareja.first <=10){
    cout << "Escriba un dni: ";
    cin >> pareja.second;
    c.poner(pareja);
    cout << "Escriba una nota: ";
    cin >> pareja.first;
  }
  
//  ColaPri<pair<float,string>> otra(c);
//  otra = c;
  cout << "DNIs ordenados por nota:" << endl;
  while(!c.vacia()){
    cout << "DNI: " << c.frente().second << " Nota: "
    << c.frente().first << endl;
    c.quitar();
  }
  return 0;
}
