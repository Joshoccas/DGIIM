#include <iostream>
#include <ctime>
#include "APO.hpp"

using namespace std;

//Ordena 100 valores aleatorios

int main(int argc, const char * argv[]) {
  const int N = 100;
  const float max = 100.0;
//  APO<int> a(N);
  APO<int> a;
  srand((unsigned) time(NULL));
  
  for(int i=0; i<N; i++)
    a.insertar((int) (max*rand()/RAND_MAX));
  
  while(!a.empty()){
    cout << a.raiz() << " " ;
    a.borrar_raiz();
  }
  cout <<endl;
  return 0;
}
