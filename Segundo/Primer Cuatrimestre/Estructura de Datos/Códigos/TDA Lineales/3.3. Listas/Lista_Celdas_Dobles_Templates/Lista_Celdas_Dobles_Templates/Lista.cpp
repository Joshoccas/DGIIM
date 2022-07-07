#include <cassert>
#include "util.hpp"
//#include "Lista.hpp"

//Clase Posicion

template <class T>
Posicion<T>::Posicion(){
  puntero = 0;
}

//Operador ++ prefijo
template <class T>
Posicion<T>& Posicion<T>::operator++(){
  puntero = puntero->siguiente;
  return *this;
}

//Operador ++ postfijo
template <class T>
Posicion<T> Posicion<T>::operator++(int){
  Posicion<T> p(*this);
  ++(*this);
  return p;
}

//Operador -- prefijo
template <class T>
Posicion<T>& Posicion<T>::operator--(){
  puntero = puntero->anterior;
  return *this;
}

//Operador -- postfijo
template <class T>
Posicion<T> Posicion<T>::operator--(int){
  Posicion p(*this);
  --(*this);
  return p;
}

template <class T>
bool Posicion<T>::operator==(const Posicion<T>& p) const{
  return (puntero==p.puntero);
}

template <class T>
bool Posicion<T>::operator!=(const Posicion<T>& p) const{
  return (puntero!=p.puntero);
}

//Clase Lista

template <class T>
Lista<T>::Lista(){
  cabecera = new CeldaLista<T>;   //Creamos la cabecera
  cabecera->siguiente = cabecera; //Ajustamos punteros
  cabecera->anterior = cabecera;
}

template <class T>
Lista<T>::Lista(const Lista<T>& l){
  cabecera = new CeldaLista<T>;    //Creamos la celda cabecera
  cabecera->siguiente = cabecera;
  cabecera->anterior = cabecera;
  
  //Recorremos la lista y copiamos
  CeldaLista<T>* p = l.cabecera->siguiente;
  while(p!=l.cabecera){ //Hasta "dar la vuelta completa"
    CeldaLista<T>* q = new CeldaLista<T>;//Creamos una nueva celda
    q->elemento = p->elemento;           //Copiamos la información
    q->anterior = cabecera->anterior;    //Ajustamos punteros
    cabecera->anterior->siguiente = q;
    cabecera->anterior = q;
    q->siguiente = cabecera;
    p = p->siguiente;                    //Avanzamos en l
  }
}

template <class T>
Lista<T>::~Lista(){
  while(begin()!=end())                  //Mientras no esté vacía
    borrar(begin());                     //Borramos la primera celda
  delete cabecera;                       //Borramos la cabecera
}

template <class T>
Lista<T>& Lista<T>::operator=(const Lista<T> &l){
  Lista<T> aux(l); //Usamos el constructor de copia
  //Intercambiamos punteros
  intercambiar(this->cabecera, aux.cabecera); 
  return *this;
  //Al salir se destruye aux, que tiene el antiguo contenido de *this
}

template <class T>
void Lista<T>::set(Posicion<T> p, T e){
  p.puntero->elemento = e;
}

template <class T>
T Lista<T>::get(Posicion<T> p) const{
  return p.puntero->elemento;
}

template <class T>
Posicion<T> Lista<T>::insertar(Posicion<T> p, T e){
  CeldaLista<T>* q = new CeldaLista<T>;    //Creamos la celda
  q->elemento = e;                   //Almacenamos la información
  q->anterior = p.puntero->anterior; //Ajustamos punteros
  q->siguiente = p.puntero;
  p.puntero->anterior = q;
  q->anterior->siguiente = q;
  p.puntero = q;
  return p;
}

template <class T>
Posicion<T> Lista<T>::borrar(Posicion<T> p){
  assert(p!=end());
  CeldaLista<T>* q = p.puntero;
  q->anterior->siguiente = q->siguiente;
  q->siguiente->anterior = q->anterior;
  p.puntero = q->siguiente;
  delete q;
  return p;
}

template <class T>
Posicion<T> Lista<T>::begin() const{
  Posicion<T> p;
  p.puntero = cabecera->siguiente;
  return p;
}

template <class T>
Posicion<T> Lista<T>::end() const{
  Posicion<T> p;
  p.puntero = cabecera;
  return p;
}

