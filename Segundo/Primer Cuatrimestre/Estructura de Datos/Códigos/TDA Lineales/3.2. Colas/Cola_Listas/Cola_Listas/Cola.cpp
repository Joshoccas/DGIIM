#include <cassert>
#include "Cola.hpp"

Cola::Cola(){
  primera = ultima = 0;
}

Cola::Cola(const Cola& c){
  copiar(c);
}

Cola::~Cola(){
  liberar();
}

Cola& Cola::operator=(const Cola &c){
  if(this!=&c){
    liberar();
    copiar(c);
  }
  return *this;
}

//Versión alternativa
//Cola & Cola::operator=(const Cola &c){
//  Cola ctemp(c);
//  Celda * aux;
//  aux = this->primera;
//  this->primera = ctemp.primera;
//  ctemp.primera = aux;
//  aux = this->ultima;
//  this->ultima = ctemp.ultima;
//  ctemp.ultima = aux;
//  return *this;
//}

void Cola::poner(const Tbase & c){
  //Creamos una nueva celda
  CeldaCola* nueva = new CeldaCola;
  nueva->elemento = c;
  nueva->sig = 0;
  //Conectamos la celda
  if (primera==0) //Cola vacía
    primera = ultima = nueva;
  else{ //Cola no vacía
    ultima->sig = nueva;
    ultima = nueva;
  }
}

void Cola::quitar(){
  //Comprobamos que la cola no está vacía
  assert(primera!=0);
  //Hacemos que primera apunte
  //a la siguiente celda
  CeldaCola* aux = primera;
  primera = primera->sig;
  //Borramos la celda
  delete aux;
  //Si la cola queda vacía, tenemos que ajustar última
  if (primera==0)
    ultima = 0;
}

Tbase Cola::frente() const{
  //Comprobamos que no está vacía
  assert(primera!=0);
  return primera->elemento;
}

bool Cola::vacia() const{
  return (primera == 0);
}

void Cola::copiar(const Cola& c){
  if (c.primera == 0) //Si la cola está vacía
    primera = ultima = 0;
  else{ //Caso general. No está vacía
    //Creamos la primera celda
    primera = new CeldaCola;
    primera->elemento = c.primera->elemento;
    ultima = primera;
    //Recorremos y copiamos el resto de la cola
    CeldaCola* orig = c.primera;
    while(orig->sig != 0){
      orig = orig->sig;
      ultima->sig = new CeldaCola;
      ultima = ultima->sig;
      ultima->elemento = orig->elemento;
    }
    ultima->sig = 0;
  }
}

void Cola::liberar(){
  CeldaCola* aux;
  while(primera!=0){
    aux = primera;
    primera = primera->sig;
    delete aux;
  }
  ultima = 0;
}
