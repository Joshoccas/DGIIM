#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int BusquedaBinaria(int v[], int izqda, int drcha, int buscado);
int BusquedaSecuencial(int v[], int izqda, int drcha, int buscado);
void intercambio(int v[], int nelem);

int main(){
  const int TAM=100;
  const int maximo = 100, minimo = 0;
  int v[TAM], util_v=TAM, i, buscado, posicion;

  srand(time(NULL));
  for(i=0; i<util_v; i++)
    v[i] = double(rand()) /RAND_MAX * (maximo-minimo) + minimo;

  intercambio(v, util_v);

  cout << "Vector: " << endl;

  for(i=0; i<util_v; i++)
    cout << v[i] << " ";
  cout << endl;

  cout << "Elemento a buscar: ";
  cin >> buscado;

  posicion = BusquedaBinaria(v, 0, util_v-1, buscado);
  if (posicion == -1)
    cout << "No está en el vector";
  else
    cout << "Está en la posición " << posicion+1;
  cout << endl;

  system("PAUSE");
  return 0;
}

int BusquedaBinaria(int v[], int izqda, int drcha, int buscado){
  const int UMBRAL=10;
  int centro;

  cout << "Binaria" << endl;
  cout << "I: " << izqda << " D: " << drcha << endl;
  if (drcha-izqda+1 <= UMBRAL)
    return BusquedaSecuencial(v,izqda, drcha, buscado);
  else {
    centro = (izqda + drcha)/2;
    if (v[centro] == buscado)
      return centro;
    else if (v[centro] < buscado)
      return BusquedaBinaria(v, centro+1, drcha, buscado);
    else
      return BusquedaBinaria(v, izqda, centro-1, buscado);
  }

}

int BusquedaSecuencial(int v[], int izqda, int drcha, int buscado){
  int i, pos;
  bool encontrado;

  cout << "Secuencial" << endl;
  cout << "I: " << izqda << " D: " << drcha << endl;

  for (i=izqda, pos=-1, encontrado=false; (i<=drcha) && !encontrado; i++)
    if (v[i] == buscado){
      encontrado = true;
      pos = i;
    }

  return pos;
}

void intercambio(int v[], int nelem){
  int izqda, aux, i;

  //En este bucle desplazamos el extremo izquierdo
  //del intervalo a considerar
  for (izqda=0; izqda<nelem; izqda++)

    //Recorremos de derecha a izquierda el intervalo
    //desde la derecha hasta izqda+1
    for (i=nelem-1 ; i>izqda ; i--)

      //Si los elementos de las posiciones i e i-1
      //no están ordenados, los intercambiamos
      if (v[i] < v[i-1]){
        aux = v[i];
        v[i] = v[i-1];
        v[i-1] = aux;
      }
}
