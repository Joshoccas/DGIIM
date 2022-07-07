#include <cstdlib>
#include <iostream>

using namespace std;

int BusquedaLineal(int v[], int izqda, int drcha, int buscado);

int main(){
  const int TAM=100;
  int v[TAM], util_v, i, buscado, posicion;

  do{
    cout << "Introduzca el número de datos: ";
    cin >> util_v;
  } while (util_v<=0);

  cout << "Introduzca los " << util_v << " datos: ";
  for(i=0; i<util_v; i++)
    cin >> v[i];

  cout << "Elemento a buscar: ";
  cin >> buscado;

  posicion = BusquedaLineal(v, 0, util_v-1, buscado);
  if (posicion == -1)
    cout << "No está en el vector";
  else
    cout << "Está en la posición " << posicion+1;
  cout << endl;

  system("PAUSE");
  return 0;
}

int BusquedaLineal(int v[], int izqda, int drcha, int buscado){
  if (izqda>drcha)
    return -1;
  else if (v[izqda] == buscado)
    return izqda;
  else
    return BusquedaLineal(v, izqda+1, drcha, buscado);
}
