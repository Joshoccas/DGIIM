#include <iostream>
#include "AVL.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
  AVL<int> avl;
  AVL<int>::iterator it;
  int e;
  
//  cout << "INSERCIÓN DE DATOS" << endl;
//
//  cout << "Introduce un entero (<0 para terminar) ";
//  cin >> e;
//  while(e>=0){
//    avl.insertar(e);
//    for(it = avl.begin(); it!=avl.end(); ++it)
//      cout << *it << " ";
//    cout << endl;
//    avl.Esquema();
//
//    cout << "Introduce un entero (<0 para terminar) ";
//    cin >> e;
//  }
  
  const int N = 50;
  const float max = 100.0;
  srand(time(NULL));
  for(int i=0; i<N; i++)
    avl.insertar((int) (max*rand()/RAND_MAX));
  
  
  for(it = avl.begin(); it!=avl.end(); ++it)
    cout << *it << " ";
  cout << endl;
  
  avl.Esquema();
  
  cout << "BÚSQUEDA DE DATOS" << endl;
  cout << "Introduce un entero (< 0 para terminar) ";
  cin >> e;
  while(e>=0){
    cout << e << (avl.existe(e)? " SÍ" : " NO") << " está en el AVL" << endl;
    cout << "Introduce un entero (< 0 para terminar) ";
    cin >> e;
  }
  
  avl.Esquema();
  cout << "BORRADO DE DATOS" << endl;
  cout << "Introduce un entero (< 0 para terminar) ";
  cin >> e;
  while(e>=0){
    avl.borrar(e);
    for(it = avl.begin(); it!=avl.end(); ++it)
      cout << *it << " ";
    cout << endl;
    avl.Esquema();
    
    cout << "Introduce un entero (< 0 para terminar) ";
    cin >> e;
  }
  
  return 0;
}

