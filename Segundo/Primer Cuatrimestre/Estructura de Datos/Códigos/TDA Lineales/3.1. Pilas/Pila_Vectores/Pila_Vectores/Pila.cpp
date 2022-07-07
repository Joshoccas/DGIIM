#include <cassert>
#include "Pila.hpp"

Pila::Pila():nelem(0){
}

//Método auxiliar
void Pila::copiar(const Pila &p){
  this->nelem = p.nelem;
  for(int i=0; i<nelem; i++)
    datos[i] = p.datos[i];
}

Pila::Pila(const Pila &p){
  this->copiar(p);
}

//No es necesario definir el destructor


Pila & Pila::operator=(const Pila &p){
  if (this != &p)
    copiar(p);
  return(*this);
}

bool Pila::vacia() const{
  return(nelem==0);
}

void Pila::poner(const Tbase &c){
  assert(nelem<TAM);
  datos[nelem++] = c;
}

//Pila & Pila::operator+=(const Tbase & c){
//  poner(c);
//  return *this;
//}

//Podemos también sobrecargarlo como método void
//Al fin y al cabo el encadenamiento casi no merece la pena,
//ya que son necesarios paréntesis para poder encadenar
//porque el operador += asocia de derecha a izquierda

void Pila::operator+=(const Tbase &c){
  poner(c);
}

void Pila::quitar(){
  assert(nelem>0);
  nelem--;
}

void Pila::operator--(){
  quitar();
}

void Pila::operator--(int i){
  quitar();
}

Tbase & Pila::tope(){
  assert(nelem>0);
  return datos[nelem-1];
}

const Tbase & Pila::tope() const{
  assert(nelem>0);
  return datos[nelem-1];
}
