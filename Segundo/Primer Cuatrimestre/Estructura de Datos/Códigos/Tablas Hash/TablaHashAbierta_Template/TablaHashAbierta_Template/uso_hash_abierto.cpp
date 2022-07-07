#include "hash_abierto.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
  //  TablaHash tabla(5);
  //  const int ndatos = 8;
  //  int datos[2][ndatos] = {{12,21,68,38,52,70,44,18},{0,1,2,3,4,5,6,7}};
  //
  //  for (int i=0; i<ndatos; i++){
  //    tabla.Insertar(datos[0][i], datos[1][i]);
  //  }
  //  tabla.imprimir();
  
  TablaHash<int, int> tabla(13);
  const int N = 100;
  const float max = 100.0;
  srand((unsigned)time(NULL));
  for(int i=0; i<N; i++)
    tabla.Insertar((int) (max*rand()/RAND_MAX), i);
  
  tabla.imprimir();
  
  for(int i=0; i<50; i++)
    tabla.Borrar(i);
  
  tabla.imprimir();
  
  return 0;
}
