#ifndef hash_abierto_hpp
#define hash_abierto_hpp

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <class K, class V>
class CeldaLista{
private:
  K clave;
  V valor;
public:
//  CeldaLista();
  CeldaLista(K c, V v);
  K & Clave();
  V & Valor();
};

//template <class K, class V>
//CeldaLista<K,V>:: CeldaLista() : clave(0),valor(-1){
//}

template <class K, class V>
CeldaLista<K,V>:: CeldaLista(K c, V v): clave(c),valor(v){
}

template <class K, class V>
K & CeldaLista<K,V>:: Clave(){
  return clave;
}

template <class K, class V>
V & CeldaLista<K,V>:: Valor(){
  return valor;
}

template <class K, class V>
class TablaHash{
private:
  vector<list<CeldaLista<K,V>>> tabla;
  int fhash(K clave);
  typename list<CeldaLista<K,V>>::iterator EstaEnFila(K clave, int fila);
public:
  TablaHash(int tam);
  bool Existe(K c);
  bool Insertar(K c, V v);
  bool Borrar(K c);
  bool Cambiar(K c, V valor);
  V Obtener(K clave);
  void imprimir();
};


template <class K, class V>
TablaHash<K,V>::TablaHash(int tam){
  assert(tam>0);
  tabla.resize(tam);
}

template <class K, class V>
int TablaHash<K,V>::fhash(K clave){
  return clave%tabla.size();
}

template <class K, class V>
typename list<CeldaLista<K,V>>::iterator TablaHash<K,V>::EstaEnFila(K clave, int fila){
  typename list<CeldaLista<K,V>>::iterator it;
  for(it=tabla[fila].begin(); it!=tabla[fila].end(); it++)
    if(it->Clave() == clave)
      return it;
  return it; //Si no lo encuentra devuelve end()
}

template <class K, class V>
bool TablaHash<K,V>::Existe(K c){
  int fila = fhash(c);
  return (EstaEnFila(c, fila) != tabla[fila].end());
}

template <class K, class V>
bool TablaHash<K,V>::Insertar(K c, V v){
  bool exito = false;
  int fila = fhash(c);
  if (EstaEnFila(c, fila) == tabla[fila].end()){
    tabla[fila].push_back(CeldaLista<K,V>(c,v));
    exito = true;
  }
  return exito;
}

template <class K, class V>
bool TablaHash<K,V>::Cambiar(K c, V v){
  bool exito = false;
  int fila = fhash(c);
  typename list<CeldaLista<K,V>>::iterator donde = EstaEnFila(c, fila);
  
  if (donde != tabla[fila].end()){
    donde->Valor() = v;
    exito = true;
  }
  return exito;
}

template <class K, class V>
V TablaHash<K,V>::Obtener(K c){
  int fila = fhash(c);
  typename list<CeldaLista<K,V>>::iterator donde = EstaEnFila(c, fila);
  
  return(donde!=tabla[fila].end() ? donde->Valor(): -1);
}

template <class K, class V>
bool TablaHash<K,V>::Borrar(K c){
  bool exito = false;
  int fila = fhash(c);
  typename list<CeldaLista<K,V>>::iterator donde = EstaEnFila(c, fila);
  
  if (donde!=tabla[fila].end()){
    tabla[fila].erase(donde);
    exito = true;
  }
  return exito;
}

template <class K, class V>
void TablaHash<K,V>::imprimir(){
  typename list<CeldaLista<K,V>>::iterator it;
  for(int i=0; i<tabla.size(); i++){
    cout << "Fila " << i << ": ";
    for(it=tabla[i].begin(); it!=tabla[i].end(); it++)
      cout << "(" << it->Clave() << "." << it->Valor() << ")";
    cout << endl;
  }
}




#endif /* hash_abierto_hpp */
