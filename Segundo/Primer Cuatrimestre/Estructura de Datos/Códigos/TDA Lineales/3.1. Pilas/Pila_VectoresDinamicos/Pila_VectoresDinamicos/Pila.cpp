#include <cassert>
#include "Pila.hpp"

Pila::Pila(int tam){
  reservar(tam);
  nelem = 0;
}

Pila::Pila(const Pila &p){
  reservar(p.reservados);
  copiar(p);
}

Pila::~Pila(){
  liberar();
}

Pila & Pila::operator=(const Pila &p){
  if (this != &p){
    liberar();
    reservar(p.reservados);
    copiar(p);
  }
  return(*this);
}

bool Pila::vacia() const{
  return(nelem==0);
}

void Pila::poner(Tbase c){
  if (nelem==reservados)
    resize(2*reservados);
  datos[nelem++] = c;
}

void Pila::operator+=(const Tbase &c){
  this->poner(c);
}

void Pila::quitar(){
  assert(nelem>0);
  nelem--;
  if(nelem<reservados/4)
    resize(reservados/2);
}

void Pila::operator--(){
  this->quitar();
}

void Pila::operator--(int i){
  this->quitar();
}

Tbase & Pila::tope(){
  assert(nelem>0);
  return datos[nelem-1];
}

const Tbase & Pila::tope() const{
  assert(nelem>0);
  return datos[nelem-1];
}

//Métodos auxiliares privados

void Pila::resize(int n){
  Tbase * aux = datos;
  reservar(n);
  for(int i=0; i<nelem; i++)
    datos[i] = aux[i];
  delete []aux;
}

void Pila::liberar(){
  if (datos!=0){
    delete []datos;
    reservados = 0;
    nelem = 0;
  }
}

void Pila::reservar(int n){
  assert(n>0);
  datos = new Tbase[n];
  reservados = n;
}

void Pila::copiar(const Pila& p){
  nelem = p.nelem;
  for(int i=0; i<nelem; i++)
    datos[i] = p.datos[i];
}

