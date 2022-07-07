#include "Pila.hpp"

Pila::Pila(){
  primera = 0;
}

Pila::Pila(const Pila& p){
  copiar(p);
}

Pila::~Pila(){
  liberar();
}

Pila& Pila::operator=(const Pila &p){
  if(this!=&p){
    liberar();
    copiar(p);
  }
  return *this;
}

void Pila::poner(Tbase c){
  CeldaPila *aux = new CeldaPila;
  aux->elemento = c;
  aux->sig = primera;
  primera = aux;
}

void Pila::quitar(){
  CeldaPila *aux = primera;
  primera = primera->sig;
  delete aux;
}

Tbase Pila::tope() const{
  return primera->elemento;
}

bool Pila::vacia() const{
  return (primera==0);
}

void Pila::copiar(const Pila &p){
  if (p.primera==0)
    primera = 0;
  else{
    primera = new CeldaPila;
    primera->elemento = p.primera->elemento;
    CeldaPila *orig = p.primera,
              *dest = primera;
    while(orig->sig!=0){
      dest->sig = new CeldaPila;
      orig = orig->sig;
      dest = dest->sig;
      dest->elemento = orig->elemento;
    }
    dest->sig = 0;
  }
}

void Pila::liberar(){
  CeldaPila* aux;
  while(primera!=0){
    aux = primera;
    primera = primera->sig;
    delete aux;
  }
  primera = 0;
}

