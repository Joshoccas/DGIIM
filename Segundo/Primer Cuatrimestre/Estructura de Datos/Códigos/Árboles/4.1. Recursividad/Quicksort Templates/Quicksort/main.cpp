#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
void quicksort(T v[], int izqda, int drcha);
template <class T>
int partir(T v[], int primero, int ultimo);
template <class T>
void intercambiar(T & v1, T & v2);

int main(){
  const int TAM_MAX = 100;
  const int maximo = 100, minimo = 0;
  int v[TAM_MAX], util_v=TAM_MAX;
  
  //  rand() genera valores x ~ U[0, RAND_MAX]
  //  Llevamos x al intervalo [min, max] mediante una transformación
  //  afÌn: y=A*x+B, donde A=(max-min) y B=min
  
  srand((unsigned int) time(NULL));
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
  
  return 0;
}

template <class T>
void quicksort(T v[], int izqda, int drcha){
  int pos_pivote;
  
  if(izqda<drcha){
    pos_pivote = partir(v, izqda, drcha);
    quicksort(v, izqda, pos_pivote-1);
    quicksort(v, pos_pivote+1, drcha);
  }
}

template <class T>
int partir(T v[], int primero, int ultimo){
  int pivote = v[primero],
  izqda = primero+1,
  drcha = ultimo;
  while(izqda<=drcha){ //Mientras no se crucen los Ìndices
    //Busco por la izquierda el primer elemento mayor que el pivote
    while((izqda<=drcha) && (v[izqda]<pivote))
      izqda++;
    //Busco por la derecha el primer elemento menor que el pivote
    while((izqda<=drcha) && (v[drcha]>=pivote))
      drcha--;
    //Si no se han cruzado los índices, intercambiar
    if (izqda<drcha)
      intercambiar(v[izqda++], v[drcha--]);
  }
  //Al terminar la partición, situar el pivote en su posición
  intercambiar(v[primero], v[drcha]);
  return drcha; //Devolvemos la nueva posición del pivote
}

//Función auxiliar de intercambio
template <class T>
void intercambiar(T & v1, T &v2){
  T aux(v1);
  v1 = v2;
  v2 = aux;
}

