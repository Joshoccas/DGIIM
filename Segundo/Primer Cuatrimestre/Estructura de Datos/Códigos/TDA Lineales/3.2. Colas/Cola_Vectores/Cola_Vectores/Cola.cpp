#include <cassert>
#include "Cola.hpp"

Cola::Cola(){
  reservar(10);
  anterior = posterior = nelem = 0;
}

Cola::Cola(const Cola& c){
  reservar(c.reservados);
  copiar(c);
}

Cola& Cola::operator=(const Cola& c){
  if(this!=&c){
    liberar();
    reservar(c.reservados);
    copiar(c);
  }
  return(*this);
}

Cola::~Cola(){
  liberar();
}

void Cola::poner(const Tbase & valor){
  if(nelem==reservados)
    redimensionar(2*reservados);
  datos[posterior] = valor;
  posterior = (posterior+1)%reservados;
  nelem++;
}

void Cola::quitar(){
  assert(!vacia());
  anterior = (anterior+1)%reservados;
  nelem--;
  if (nelem< reservados/4)
    redimensionar(reservados/2);
}

Tbase Cola::frente() const{
  assert(!vacia());
  return datos[anterior];
}

bool Cola::vacia() const{
  return (nelem == 0);
}

//Métodos auxiliares privados

void Cola::reservar(const int n){
  assert(n>0);
  reservados = n;
  datos = new Tbase[n];
}

void Cola::liberar(){
  delete[] datos;
  datos = 0;
  anterior = posterior = nelem = reservados = 0;
}

void Cola::copiar(const Cola &c){
  for (int i= c.anterior; i!=c.posterior; i= (i+1)%reservados)
    datos[i] = c.datos[i];
  anterior = c.anterior;
  posterior = c.posterior;
  nelem = c.nelem;
  
}

void Cola::redimensionar(const int n){
  assert(n>0 && n>=nelem);
  Tbase* aux = datos;
  int tam_aux = reservados;
  reservar(n);
  for(int i=0; i<nelem; i++)
    datos[i] = aux[(anterior+i)%tam_aux];
  anterior = 0;
  posterior = nelem;
  delete[] aux;
}

