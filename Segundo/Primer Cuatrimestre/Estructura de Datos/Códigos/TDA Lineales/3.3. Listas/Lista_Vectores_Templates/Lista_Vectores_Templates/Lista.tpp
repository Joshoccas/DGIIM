#include <cassert>
using namespace std;

//Clase Posicion

Posicion::Posicion(){
  i = 0;
}

//Operador ++ prefijo
Posicion& Posicion::operator++(){
  i++;
  return *this;
}

//Operador ++ postfijo
Posicion Posicion::operator++(int){
  Posicion aux(*this);
  i++;
  return aux;
}

//Operador -- prefijo
Posicion& Posicion::operator--(){
  i--;
  return  *this;
}

//Operador -- postfijo
Posicion Posicion::operator--(int){
  Posicion aux(*this);
  i--;
  return aux;
}

bool Posicion::operator==(const Posicion& p) const{
  return i==p.i;
}

bool Posicion::operator!=(const Posicion& p) const{
  return i!=p.i;
}

//Clase Lista

template <typename T>
Lista<T>::Lista(){
  nelementos = 0;
  reservar(1);
}

template <typename T>
Lista<T>::Lista(const Lista<T>& l){
  reservar(l.nelementos);
  copiar(l);
}

template <typename T>
Lista<T>::~Lista(){
  liberar();
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T> &l){
  if (this != &l){
    liberar();
    reservar(l.nelementos);
    copiar(l);
  }
  return *this;
}

template <typename T>
void Lista<T>::set(const Posicion & p, const T &e){
  assert(p.i>=0 && p.i<nelementos);
  datos[p.i] = e;
}

template <typename T>
T Lista<T>::get(const Posicion & p) const{
  assert(p.i>=0 && p.i<nelementos);
  return datos[p.i];
}

template <typename T>
Posicion Lista<T>::insertar(const Posicion & p, const T & e){
  if(nelementos == reservados)
    redimensionar(reservados*2);
  for(int j=nelementos; j>p.i; j--)
    datos[j] = datos[j-1];
  datos[p.i] = e;
  nelementos++;
  return p;
}

template <typename T>
Posicion Lista<T>::borrar(const Posicion & p){
  assert(p!=end());
  for(int j=p.i; j<nelementos-1; j++)
    datos[j] = datos[j+1];
  nelementos--;
  if (nelementos<reservados/4)
    redimensionar(reservados/2);
  return p;
}

template <typename T>
Posicion Lista<T>::begin() const{
  Posicion p;
  p.i = 0; //Innecesario
  return p;
}

template <typename T>
Posicion Lista<T>::end() const{
  Posicion p;
  p.i = nelementos;
  return p;
}

//Métodos auxiliares privados

template <typename T>
void Lista<T>::liberar(){
  delete []datos;
  reservados = nelementos = 0;
}


template <typename T>
void Lista<T>::reservar(int n){
  assert(n>0);
  reservados = n;
  datos = new T[reservados];
}

template <typename T>
void Lista<T>::copiar(const Lista& l){
  nelementos = l.nelementos;
  for(int i=0; i<nelementos; i++)
    datos[i] = l.datos[i];
}

template <typename T>
void Lista<T>::redimensionar(int n){
  assert(n>0 && n>=nelementos);
  T* aux = datos;
  reservar(n);
  for(int i=0; i<nelementos; i++)
    datos[i] = aux[i];
//  memcpy(datos, aux, nelementos*sizeof(T));
  delete[] aux;
}

