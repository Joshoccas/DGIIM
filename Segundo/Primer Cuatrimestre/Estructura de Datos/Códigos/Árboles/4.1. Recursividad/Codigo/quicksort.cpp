#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void quicksort(int v[], int izqda, int drcha);
int partir(int v[], int primero, int ultimo);
void swap(int v[], int pos1, int pos2);

int main(){
  const int TAM_MAX = 100;
  const int maximo = 100, minimo = 0;
  int v[TAM_MAX], util_v=TAM_MAX;

//  rand() genera valores x ~ U[0, RAND_MAX]
//  Llevamos x al intervalo [min, max] mediante una transformación
//  afín: y=A*x+B, donde A=(max-min) y B=min

  srand(time(NULL));
  for(int i=0; i<util_v; i++)
    v[i] = double(rand()) /RAND_MAX * (maximo-minimo) + minimo;

  cout << "Vector desordenado:" << endl;
  for(int i=0; i<util_v; i++)
    cout << v[i] << " ";
  cout << endl;

  quicksort(v, 0, util_v-1);

  cout << "Vector ordenado: " << endl;
  for (int i=0; i<util_v; i++)
    cout << v[i] << " ";
  cout << endl;

  system("pause");

  return 0;
}

void quicksort(int v[], int izqda, int drcha){
  int pos_pivote;

  if(izqda<drcha){
    pos_pivote = partir(v, izqda, drcha);
    quicksort(v, izqda, pos_pivote-1);
    quicksort(v, pos_pivote+1, drcha);
  }
}

int partir(int v[], int primero, int ultimo){
 int pivote = v[primero],
      izqda = primero+1,
      drcha = ultimo;
  while(izqda<=drcha){ //Mientras no se crucen los índices
    //Busco por la izquierda el primer elemento mayor que el pivote
    while((izqda<=drcha) && (v[izqda]<pivote))
      izqda++;
    //Busco por la derecha el primer elemento menor que el pivote
    while((izqda<=drcha) && (v[drcha]>=pivote))
      drcha--;
    //Si no se han cruzado los índices, intercambiar
    if (izqda<drcha)
      swap(v, izqda++, drcha--);
  }
  //Al terminar la partición, situar el pivote en su posición
  swap(v,primero, drcha);
  return drcha; //Devolvemos la nueva posición del pivote
}

//Función auxiliar de intercambio
void swap(int v[], int pos1, int pos2){
  int aux;

  aux = v[pos1];
  v[pos1] = v[pos2];
  v[pos2] = aux;
}

