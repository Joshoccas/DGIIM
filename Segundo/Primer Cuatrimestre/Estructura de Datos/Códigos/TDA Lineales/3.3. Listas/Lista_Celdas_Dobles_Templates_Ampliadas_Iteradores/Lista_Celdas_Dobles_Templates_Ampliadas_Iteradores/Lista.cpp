#include <cassert>
//#include "Lista.hpp"

//Clase iterator

template <class T>
Lista<T>::iterator::iterator():puntero(0){
}

template <class T>
Lista<T>::iterator::iterator(const iterator & otro):puntero(otro.puntero){
}

template <class T>
bool Lista<T>::iterator::operator==(const Lista<T>::iterator & otro)const{
  return (puntero == otro.puntero);
}

template <class T>
bool Lista<T>::iterator::operator!=(const Lista<T>::iterator & otro)const{
  return (puntero != otro.puntero);
}

template <class T>
typename Lista<T>::iterator & Lista<T>::iterator::operator=(const Lista<T>::iterator &otro){
  puntero = otro.puntero;
  return (*this);
}

template <class T>
T & Lista<T>::iterator::operator*(){
  return (puntero->elemento);
}

template <class T>
typename Lista<T>::iterator Lista<T>::iterator::operator++(){
  puntero = puntero->siguiente;
  return (*this);
}

template <class T>
typename Lista<T>::iterator Lista<T>::iterator::operator++(int){
  Lista<T>::iterator aux(*this);
  ++(*this);
  return aux;
}

template <class T>
typename Lista<T>::iterator Lista<T>::iterator::operator--(){
  puntero = puntero->anterior;
  return (*this);
}

template <class T>
typename Lista<T>::iterator Lista<T>::iterator::operator--(int){
  Lista<T>::iterator aux(*this);
  --(*this);
  return aux;
}

template <class T>
typename Lista<T>::iterator Lista<T>::begin() const{
  Lista<T>::iterator it;
  it.puntero = cabecera->siguiente;
  return it;
}

template <class T>
typename Lista<T>::iterator Lista<T>::end() const{
  Lista<T>::iterator it;
  it.puntero = cabecera;
  return it;
}

//Clase const_iterator

template <class T>
Lista<T>::const_iterator::const_iterator():puntero(0){
}

template <class T>
Lista<T>::const_iterator::const_iterator(const const_iterator & otro):puntero(otro.puntero){
}

template <class T>
bool Lista<T>::const_iterator::operator==(const Lista<T>::const_iterator & otro)const{
  return (puntero == otro.puntero);
}

template <class T>
bool Lista<T>::const_iterator::operator!=(const Lista<T>::const_iterator & otro)const{
  return (puntero != otro.puntero);
}

template <class T>
typename Lista<T>::const_iterator & Lista<T>::const_iterator::operator=(const Lista<T>::const_iterator &otro){
  puntero = otro.puntero;
  return (*this);
}

template <class T>
const T & Lista<T>::const_iterator::operator*() const{
  return (puntero->elemento);
}

template <class T>
typename Lista<T>::const_iterator Lista<T>::const_iterator::operator++(){
  puntero = puntero->siguiente;
  return (*this);
}

template <class T>
typename Lista<T>::const_iterator Lista<T>::const_iterator::operator++(int){
  Lista<T>::const_iterator aux(*this);
  ++(*this);
  return aux;
}

template <class T>
typename Lista<T>::const_iterator Lista<T>::const_iterator::operator--(){
  puntero = puntero->anterior;
  return (*this);
}

template <class T>
typename Lista<T>::const_iterator Lista<T>::const_iterator::operator--(int){
  Lista<T>::iterator aux(*this);
  --(*this);
  return aux;
}

template <class T>
typename Lista<T>::const_iterator Lista<T>::cbegin() const{
  Lista<T>::const_iterator it;
  it.puntero = cabecera->siguiente;
  return it;
}

template <class T>
typename Lista<T>::const_iterator Lista<T>::cend() const{
  Lista<T>::const_iterator it;
  it.puntero = cabecera;
  return it;
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
  clear();                               //Vaciamos la lista
  delete cabecera;                       //Borramos la cabecera
}

template <class T>
Lista<T>& Lista<T>::operator=(const Lista<T> &l){
  if (this != &l){
    Lista<T> aux(l); //Usamos el constructor de copia
    //Intercambiamos punteros
    swap(cabecera, aux.cabecera);
  }
  return *this;
  //Al salir se destruye aux, que tiene el antiguo contenido de *this
}

template <class T>
void Lista<T>::set(Lista<T>::iterator it, T e){
  *it = e;
}

template <class T>
T Lista<T>::get(Lista<T>::iterator it) const{
  return *it;
}

template <class T>
typename Lista<T>::iterator Lista<T>::insertar(Lista<T>::iterator it, const T & e){
  CeldaLista<T>* q = new CeldaLista<T>;    //Creamos la celda
  q->elemento = e;                   //Almacenamos la información
  q->anterior = it.puntero->anterior; //Ajustamos punteros
  q->siguiente = it.puntero;
  it.puntero->anterior = q;
  q->anterior->siguiente = q;
  it.puntero = q;
  return it;
}

template <class T>
typename Lista<T>::iterator Lista<T>::borrar(Lista<T>::iterator it){
  assert(it!=end());
  CeldaLista<T>* q = it.puntero;
  q->anterior->siguiente = q->siguiente;
  q->siguiente->anterior = q->anterior;
  it.puntero = q->siguiente;
  delete q;
  return it;
}

//Otros métodos de la STL

template <class T>
Lista<T>::Lista(Lista<T>::iterator inicial, Lista<T>::iterator final){
  cabecera = new CeldaLista<T>;      //Creamos la celda cabecera
  cabecera->siguiente = cabecera;
  cabecera->anterior = cabecera;
  
  for(Lista<T>::iterator it=inicial; it!=final; it++){
    CeldaLista<T>* q = new CeldaLista<T>;
    q->elemento = it.puntero->elemento;
    q->anterior = cabecera->anterior;
    cabecera->anterior->siguiente = q;
    cabecera->anterior = q;
    q->siguiente = cabecera;
  }
}

template <class T>
bool Lista<T>::empty(){
  return(begin()==end());
}

template <class T>
void Lista<T>::clear(){
  while(begin()!=end())      //Mientras no esté vacía
    borrar(begin());         //Borramos la primera celda
}

template <class T>
int Lista<T>::size() const{
  int tam = 0;
  for(Lista<T>::const_iterator p=cbegin(); p!=cend(); p++)
    tam++;
  return tam;
}

template <class T>
void Lista<T>::remove(const T &valor){
  Lista<T>::iterator it = begin();
  while(it != end())
//    if(get(it) == c)
    if(*it == valor)
      it = borrar(it);
    else
      ++it;
}

template <class T>
void Lista<T>::reverse(){
  Lista<T> aux;
  for(typename Lista<T>::iterator it=begin(); it!=end(); ++it)
    aux.insertar(aux.begin(), *it);
  std::swap(aux.cabecera, this->cabecera);
  //this->swap(aux);
  //aux.swap(*this);
}



template <class T>
void Lista<T>::push_front(const T & dato){
  insertar(begin(), dato);
}

template <class T>
void Lista<T>::pop_front(){
  borrar(begin());
}

template <class T>
void Lista<T>::push_back(const T &dato){
  insertar(end(), dato);
}

template <class T>
void Lista<T>::pop_back(){
  Lista<T>::iterator p = end();
  borrar(--p);
}

template <class T>
T & Lista<T>::front(){
  return *begin();
}

template <class T>
const T & Lista<T>::front() const{
  return *begin();
}

template <class T>
T & Lista<T>::back(){
  Lista<T>::iterator p = end();
  return *--p;
}

template <class T>
const T & Lista<T>::back() const{
  Lista<T>::iterator p = end();
  return *--p;
}

template <class T>
void Lista<T>::swap(Lista<T> &l){
  CeldaLista<T>* aux(l.cabecera);
  l.cabecera = cabecera;
  cabecera = aux;
}

