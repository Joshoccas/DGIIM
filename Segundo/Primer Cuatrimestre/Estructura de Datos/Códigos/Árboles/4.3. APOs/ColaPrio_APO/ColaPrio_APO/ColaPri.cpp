#include <cassert>
#include "ColaPri.hpp"

//template <class T>
//ColaPri<T>::ColaPri(){
//}
//
//template <class T>
//ColaPri<T>::ColaPri(const ColaPri<T>& c):apo(c.apo){
//}
//
//template <class T>
//ColaPri<T>::~ColaPri(){
//}
//
//template <class T>
//ColaPri<T>& ColaPri<T>::operator=(const ColaPri<T> &c){
//  if (this != &c)
//    apo = c.apo;
//  return (*this);
//}

template <class T>
bool ColaPri<T>::vacia() const{
  return (apo.empty());
}

template <class T>
T ColaPri<T>::frente()const{
  assert(!apo.empty());
  return(apo.raiz());
}

template <class T>
void ColaPri<T>::quitar(){
  assert(!apo.empty());
  apo.borrar_raiz();
}

template <class T>
void ColaPri<T>::poner(T e){
  apo.insertar(e);
}
