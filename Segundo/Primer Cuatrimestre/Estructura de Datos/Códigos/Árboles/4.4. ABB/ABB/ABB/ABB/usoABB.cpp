//
//  main.cpp
//  ABB
//
//  Created by Javier Abad on 23/10/17.
//  Copyright © 2017 Javier Abad. All rights reserved.
//

#include <iostream>
#include "ABB.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
  ABB<int> abb;
  int e;

//  cout << "INSERCIÓN DE DATOS" << endl;
//  cout << "Introduce un entero (<0 para terminar) ";
//  cin >> e;
//  while(e>=0){
//    abb.insertar(e);
//    cout << "Introduce un entero (<0 para terminar) ";
//    cin >> e;
//  }
  
  const int N = 20;
  const float max = 100.0;
  srand(time(NULL));
  for(int i=0; i<N; i++)
    abb.insertar((int) (max*rand()/RAND_MAX));

  
  ABB<int>::iterator it;
  for(it = abb.begin(); it!=abb.end(); ++it)
    cout << *it << " ";
  cout << endl;
  
  cout << "BÚSQUEDA DE DATOS" << endl;
  cout << "Introduce un entero (< 0 para terminar) ";
  cin >> e;
  while(e>=0){
    cout << e << (abb.existe(e)? " SÍ" : " NO") << " está en el ABB" << endl;
    cout << "Introduce un entero (< 0 para terminar) ";
    cin >> e;
  }
  
  abb.Esquema();
  cout << "BORRADO DE DATOS" << endl;
  cout << "Introduce un entero (< 0 para terminar) ";
  cin >> e;
  while(e>=0){
    abb.borrar(e);
    for(it = abb.begin(); it!=abb.end(); ++it)
      cout << *it << " ";
    cout << endl;
    abb.Esquema();

    cout << "Introduce un entero (< 0 para terminar) ";
    cin >> e;
  }
  
  return 0;
}
