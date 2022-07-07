#include <cassert>
#include <utility>

//Clase Posicion

template <class T>
Posicion<T>::Posicion(){
  primera = puntero = 0;
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
  //operator++();
  ++(*this);
  return p;
}

//Operador -- prefijo
template <class T>
Posicion<T>& Posicion<T>::operator--(){
  assert(puntero!=primera);
  CeldaLista<T>* aux = primera;
  while(aux->siguiente!=puntero){
    aux = aux->siguiente;
  }
  puntero = aux;
  return *this;
}

//Operador -- postfijo
template <class T>
Posicion<T> Posicion<T>::operator--(int){
  Posicion<T> p(*this);
  //operator--();
  --(*this);
  return p;
}

template <class T>
bool Posicion<T>::operator==(const Posicion<T> & p) const{
  return(puntero==p.puntero);
}

template <class T>
bool Posicion<T>::operator!=(const Posicion<T> &p) const{
  return(puntero!=p.puntero);
}

//Clase Lista

template <class T>
Lista<T>::Lista(){
  ultima = cabecera = new CeldaLista<T>;
  cabecera->siguiente = 0;
}

template <class T>
Lista<T>::Lista(const Lista<T>& l){
  ultima = cabecera = new CeldaLista<T>;
  CeldaLista<T>* orig = l.cabecera;
  while(orig->siguiente!=0){
    ultima->siguiente = new CeldaLista<T>;
    ultima = ultima->siguiente;
    orig = orig->siguiente;
    ultima->elemento = orig->elemento;
  }
  ultima->siguiente = 0;
}

template <class T>
Lista<T>::~Lista(){
  CeldaLista<T>* aux;
  while(cabecera!=0){
    aux = cabecera;
    cabecera = cabecera->siguiente;
    delete aux;
  }
}

template <class T>
Lista<T>& Lista<T>::operator=(const Lista<T>& l){
  Lista<T> aux(l);
  swap(cabecera, aux.cabecera);
  swap(ultima, aux.ultima);
  return *this;
}

template <class T>
void Lista<T>::set(Posicion<T> p, T e){
  p.puntero->siguiente->elemento = e;
}

template <class T>
T Lista<T>::get(Posicion<T> p) const{
  return p.puntero->siguiente->elemento;
}

template <class T>
Posicion<T> Lista<T>::insertar(Posicion<T> p, T e){
  CeldaLista<T>* nueva = new CeldaLista<T>;
  nueva->elemento = e;
  nueva->siguiente = p.puntero->siguiente;
  p.puntero->siguiente = nueva;
  if(p.puntero == ultima)
    ultima = nueva;
  return p;
}

template <class T>
Posicion<T> Lista<T>::borrar(Posicion<T> p){
  assert(p!=end());
  CeldaLista<T>* aux = p.puntero->siguiente;
  p.puntero->siguiente = aux->siguiente;
  if(aux==ultima)
    ultima = p.puntero;
  delete aux;
  return p;
}

template <class T>
Posicion<T> Lista<T>::begin()const{
  Posicion<T> p;
  p.puntero = p.primera = cabecera;
  return p;
}

template <class T>
Posicion<T> Lista<T>::end() const{
  Posicion<T> p;
  p.puntero = ultima;
  p.primera = cabecera;
  return p;
}




