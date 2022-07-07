#include <cassert>

template <class T>
Pila<T>::Pila(){
  nelem = 0;
  datos = new T[TAM];
  reservados = TAM;
}

template <class T>
Pila<T>::Pila(const Pila &p){
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
void Pila<T>::quitar(){
  assert(nelem>0);
  nelem--;
  if(nelem<reservados/4)
    resize(reservados/2);
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
  datos = new T[n];
  reservados = n;
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
void Pila<T>::copiar(const Pila<T>& p){
  reservados = p.reservados;
  datos = new T[reservados];
  nelem = p.nelem;
  for(int i=0; i<nelem; i++)
    datos[i] = p.datos[i];
}

