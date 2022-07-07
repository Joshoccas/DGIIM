#include <cstdlib>
#include <ctime>
#include <iostream>
#include <APO.h>

using namespace std;

int main(){
  int i;
  int tam = 100000;
  APO<int> a(tam);
  
  srand(time(NULL));
  
  for (i=0;i<tam;i+=2)
    a.insertar((int)(10000.0*rand()/RAND_MAX));
  
  while (!a.empty()){
    cout << a.minimo() << ' ';
    a.borrar_minimo();
  }
  cout << endl;
  
  return 0;
}
