#include <cassert>
#include "util.hpp"
#include "Lista.hpp"

//Clase Posicion

Posicion::Posicion(){
  puntero = 0;
}

//Operador ++ prefijo
Posicion& Posicion::operator++(){
  puntero = puntero->siguiente;
  return *this;
}

//Operador ++ postfijo
Posicion Posicion::operator++(int){
  Posicion p(*this);
  ++(*this);
  return p;
}

//Operador -- prefijo
Posicion& Posicion::operator--(){
  puntero = puntero->anterior;
  return *this;
}

//Operador -- postfijo
Posicion Posicion::operator--(int){
  Posicion p(*this);
  --(*this);
  return p;
}

bool Posicion::operator==(const Posicion& p) const{
  return (puntero==p.puntero);
}

bool Posicion::operator!=(const Posicion& p) const{
  return (puntero!=p.puntero);
}

//Clase Lista

Lista::Lista(){
  cabecera = new CeldaLista;      //Creamos la cabecera
  cabecera->siguiente = cabecera; //Ajustamos punteros
  cabecera->anterior = cabecera;
}

Lista::Lista(const Lista& l){
  cabecera = new CeldaLista;      //Creamos la celda cabecera
  cabecera->siguiente = cabecera;
  cabecera->anterior = cabecera;
  
  CeldaLista* p = l.cabecera->siguiente; //Recorremos la lista y copiamos
  while(p!=l.cabecera){                  //Hasta "dar la vuelta completa"
    CeldaLista* q = new CeldaLista;      //Creamos una nueva celda
    q->elemento = p->elemento;           //Copiamos la información
    q->anterior = cabecera->anterior;    //Ajustamos punteros
    cabecera->anterior->siguiente = q;
    cabecera->anterior = q;
    q->siguiente = cabecera;
    p = p->siguiente;                    //Avanzamos en l
  }
}

Lista::~Lista(){
  while(begin()!=end())                  //Mientras no esté vacía
    borrar(begin());                     //Borramos la primera celda
  delete cabecera;                       //Borramos la cabecera
}

Lista& Lista::operator=(const Lista &l){
  Lista aux(l);                               //Usamos constructor de copia
  intercambiar(this->cabecera, aux.cabecera); //Intercambiamos punteros
  return *this;
  //Al salir se destruye aux, que tiene el antiguo contenido de *this
}

void Lista::set(Posicion p, Tbase e){
  p.puntero->elemento = e;
}

Tbase Lista::get(Posicion p) const{
  return p.puntero->elemento;
}

Posicion Lista::insertar(Posicion p, Tbase e){
  CeldaLista* q = new CeldaLista;    //Creamos la celda
  q->elemento = e;                   //Almacenamos la información
  q->anterior = p.puntero->anterior; //Ajustamos punteros
  q->siguiente = p.puntero;
  p.puntero->anterior = q;
  q->anterior->siguiente = q;
  p.puntero = q;
  return p;
}

Posicion Lista::borrar(Posicion p){
  assert(p!=end());
  CeldaLista* q = p.puntero;
  q->anterior->siguiente = q->siguiente;
  q->siguiente->anterior = q->anterior;
  p.puntero = q->siguiente;
  delete q;
  return p;
}

Posicion Lista::begin() const{
  Posicion p;
  p.puntero = cabecera->siguiente;
  return p;
}

Posicion Lista::end() const{
  Posicion p;
  p.puntero = cabecera;
  return p;
}

