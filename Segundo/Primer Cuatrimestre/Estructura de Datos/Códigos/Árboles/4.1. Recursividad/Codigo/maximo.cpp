#include <cstdlib>
#include <iostream>

using namespace std;

int maximo(int v[], int izqda, int drcha);

int main(){
  const int TAM=100;
  int v[TAM], util_v, i, posicion;

  do{
    cout << "Introduzca el número de datos: ";
    cin >> util_v;
  } while (util_v<=0);

  cout << "Introduzca los " << util_v << " datos: ";
  for(i=0; i<util_v; i++)
    cin >> v[i];

  posicion = maximo(v, 0, util_v-1);
  cout << "El máximo es " << v[posicion] << " y está en la posición " << posicion+1 << endl;

  system("PAUSE");
  return 0;
}

int maximo(int v[], int izqda, int drcha){
  int pos_maximo_resto;
  if (izqda == drcha)
    return izqda;
  else{
    pos_maximo_resto = maximo(v, izqda+1, drcha);
    return v[izqda]>v[pos_maximo_resto] ? izqda : pos_maximo_resto;
  }
}
