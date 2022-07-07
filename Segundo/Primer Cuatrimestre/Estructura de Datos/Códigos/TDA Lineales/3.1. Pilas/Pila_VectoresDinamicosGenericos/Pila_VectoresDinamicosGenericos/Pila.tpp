#include <cassert>

template <class T>
Pila<T>::Pila(int tam){
  reservar(tam);
  nelem = 0;
}

template <class T>
Pila<T>::Pila(const Pila &p){
  reservar(p.reservados);
  copiar(p);
}

template <class T>
Pila<T>::~Pila(){
  liberar();
}

template <class T>
Pila<T> & Pila<T>::operator=(const Pila<T> &p){
  if (this != &p){
    liberar();
    reservar(p.reservados);
    copiar(p);
  }
  return(*this);
}

template <class T>
bool Pila<T>::vacia() const{
  return(nelem==0);
}

template <class T>
void Pila<T>::poner(const T &c){
  if (nelem==reservados)
    resize(2*reservados);
  datos[nelem++] = c;
}

template <class T>
void Pila<T>::operator+=(const T &c){
  poner(c);
}

template <class T>
void Pila<T>::quitar(){
  assert(nelem>0);
  nelem--;
  if(nelem<reservados/4)
    resize(reservados/2);
}

template <class T>
void Pila<T>::operator--(){
  quitar();
}

template <class T>
void Pila<T>::operator--(int i){
  quitar();
}

template <class T>
T & Pila<T>::tope() {
  assert(nelem>0);
  return datos[nelem-1];
}

template <class T>
const T & Pila<T>::tope() const{
  assert(nelem>0);
  return datos[nelem-1];
}

template <class T>
void Pila<T>::resize(int n){
  T * aux = datos;
  reservar(n);
  for(int i=0; i<nelem; i++)
    datos[i] = aux[i];
  delete []aux;
}

template <class T>
void Pila<T>::liberar(){
  if (datos!=0){
    delete []datos;
    reservados = 0;
    nelem = 0;
  }
}

template <class T>
void Pila<T>::reservar(int n){
  assert(n>0);
  reservados = n;
  datos = new T[reservados];
}

template <class T>
void Pila<T>::copiar(const Pila<T>& p){
  assert(reservados>=p.nelem);
  nelem = p.nelem;
  for(int i=0; i<nelem; i++)
    datos[i] = p.datos[i];
}

