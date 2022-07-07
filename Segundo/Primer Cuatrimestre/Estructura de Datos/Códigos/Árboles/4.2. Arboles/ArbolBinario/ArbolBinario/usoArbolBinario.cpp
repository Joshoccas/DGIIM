#include <iostream>
#include <queue>
#include "ArbolBinario.hpp"
using namespace std;

template <class Tbase>
void preorden(const ArbolBinario<Tbase>& a,
              const typename ArbolBinario<Tbase>::Nodo n){
  if (n!=0){
    cout << a.etiqueta(n) << ' ';
    preorden(a,a.izquierda(n));
    preorden(a,a.derecha(n));
  }
}


template <class Tbase>
void inorden(const ArbolBinario<Tbase>& a,
             const typename ArbolBinario<Tbase>::Nodo n){
  if (n!=0){
    inorden(a,a.izquierda(n));
    cout << a.etiqueta(n) << ' ';
    inorden(a,a.derecha(n));
  }
}

template <class Tbase>
void postorden(const ArbolBinario<Tbase>& a,
               const typename ArbolBinario<Tbase>::Nodo n){
  if (n!=0){
    postorden(a,a.izquierda(n));
    postorden(a,a.derecha(n));
    cout << a.etiqueta(n) << ' ';
  }
}


template <class Tbase>
int Altura(const ArbolBinario<Tbase>& a,
           const typename ArbolBinario<Tbase>::Nodo n){
  int iz,de;
  if (n==0)
    return -1;
  else {
    iz= Altura(a,a.izquierda(n));
    de= Altura(a,a.derecha(n));
    return 1 + (iz > de ? iz : de);
  }
}


template <class Tbase>
void refleja(ArbolBinario<Tbase>& a){
  ArbolBinario<Tbase> ai,ad;

  if (!a.vacio()){
    a.podar_izquierda(a.raiz(),ai);
    a.podar_derecha(a.raiz(),ad);
    refleja(ai);
    refleja(ad);
    a.insertar_izquierda(a.raiz(),ad);
    a.insertar_derecha(a.raiz(),ai);
  }
}


template <class Tbase>
void Esquema(const ArbolBinario<Tbase>& a,
             const typename ArbolBinario<Tbase>::Nodo n, string& pre){

  if (n==0)
    cout << pre << "-- x" << endl;
  else {
    cout << pre << "-- " << a.etiqueta(n) << endl;
    if (a.derecha(n)!=0 || a.izquierda(n)!=0) {// Si no es una hoja
      pre += "   |";
      Esquema(a, a.derecha(n), pre);
      pre.replace(pre.size()-4, 4, "    ");
      Esquema (a, a.izquierda(n), pre);
      pre.erase(pre.size()-4, 4);
    }
  }
}

template <class Tbase>
void Niveles(const ArbolBinario<Tbase> & a){
  queue<typename ArbolBinario<Tbase>::Nodo> c;
  typename ArbolBinario<Tbase>::Nodo n;

  if (!a.vacio()){
    c.push(a.raiz());
    while (!c.empty()){
      n=c.front();
      c.pop();
      cout << a.etiqueta(n) << ' ';
      if (a.izquierda(n) != 0)
        c.push(a.izquierda(n));
      if (a.derecha(n) != 0)
        c.push(a.derecha(n));
    }
  }
  cout << endl;
}

int main(int argc, const char * argv[]) {
  string pre;
  ArbolBinario<float> a;


  cout << "Introduce el arbol en el formato:" << endl;
  cout << "n 1 n 2 n 4 x x n 5 x n 8 x x n 3 n 6 x x n 7 x x" << endl;
  
  cin >> a;
  
  ArbolBinario<float>b;
  
  b.asignar_subarbol(b, a.izquierda(a.raiz()));

  cout << "El arbol: " << a << " tiene recorridos:" << endl;

  cout << "Preorden: ";
  preorden(a,a.raiz());
  cout << endl;

  cout << "Inorden: ";
  inorden(a,a.raiz());
  cout << endl;

  cout << "Postorden: ";
  postorden(a,a.raiz());
  cout << endl;

  cout << "y la altura es: " << Altura(a,a.raiz()) << endl;

  cout << "Listado por niveles del arbol" << endl;
  Niveles(a);

  cout << "El arbol: " << a << " tiene el esquema:" << endl;
  pre="";
  Esquema(a,a.raiz(), pre);

  refleja(a);

  cout << "Listado por niveles del arbol reflejado" << endl;
  Niveles(a);

  cout << "El arbol reflejado tiene el esquema:" << endl;
  pre="";
  Esquema(a,a.raiz(), pre);

  return 0;
}
