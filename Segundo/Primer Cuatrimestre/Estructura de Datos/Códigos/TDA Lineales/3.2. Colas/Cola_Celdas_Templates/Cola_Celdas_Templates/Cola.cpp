#include <cassert>
#include "Cola.hpp"

template <class T>
Cola<T>::Cola(){
  primera = ultima = 0;
}

template <class T>
Cola<T>::Cola(const Cola& c){
  copiar(c);
}

template <class T>
Cola<T>::~Cola(){
  liberar();
}

template <class T>
Cola<T>& Cola<T>::operator=(const Cola<T> &c){
  if(this!=&c){
    liberar();
    copiar(c);
  }
  return *this;
}

//Versión alternativa
//Cola & Cola<T>::operator=(const Cola &c){
//  Cola ctemp(c);
//  Celda * aux;
//  aux = this->primera;
//  this->primera = ctemp.primera;
//  ctemp.primera = aux;
//  aux = this->ultima;
//  this->ultima = ctemp.ultima;
//  ctemp.ultima = aux;
//  return *this;
//}

template <class T>
void Cola<T>::poner(const T & c){
  //Creamos una nueva celda
  CeldaCola<T>* aux = new CeldaCola<T>;
  aux->elemento = c;
  aux->sig = 0;
  //Conectamos la celda
  if (primera==0) //Cola vacía
    primera = ultima = aux;
  else{ //Cola no vacía
    ultima->sig = aux;
    ultima = aux;
  }
}

template <class T>
void Cola<T>::quitar(){
  //Comprobamos que la cola no está vacía
  assert(primera!=0);
  //Hacemos que primera apunte a la siguiente celda
  CeldaCola<T>* aux = primera;
  primera = primera->sig;
  //Borramos la celda
  delete aux;
  //Si la cola queda vacía tenemos que ajustar última
  if (primera==0)
    ultima = 0;
}

template <class T>
T Cola<T>::frente() const{
  //Comprobamos que no está vacía
  assert(primera!=0);
  return primera->elemento;
}

template <class T>
bool Cola<T>::vacia() const{
  return (primera == 0);
}

template <class T>
void Cola<T>::copiar(const Cola& c){
  //Si la cola está vacía
  if (c.primera == 0)
    primera = ultima = 0;
  else{ //Caso general. No está vacía
    //Creamos la primera celda
    primera = new CeldaCola<T>;
    primera->elemento = c.primera->elemento;
    //ultima apunta a la primera y única celda
    ultima = primera;
    //Recorremos y copiamos el resto de la cola
    CeldaCola<T>* orig = c.primera;
    while(orig->sig != 0){
      orig = orig->sig;
      ultima->sig = new CeldaCola<T>;
      ultima = ultima->sig;
      ultima->elemento = orig->elemento;
    }
    ultima->sig = 0;
  }
}

template <class T>
void Cola<T>::liberar(){
  CeldaCola<T>* aux;
  while(primera!=0){
    aux = primera;
    primera = primera->sig;
    delete aux;
  }
  ultima = 0;
}
