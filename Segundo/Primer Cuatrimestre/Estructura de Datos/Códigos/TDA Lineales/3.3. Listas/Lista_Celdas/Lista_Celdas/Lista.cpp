#include <cassert>
#include <utility>
#include "Lista.hpp"
using namespace std;

//Clase Posicion

Posicion::Posicion(){
  primera = puntero = 0;
}

//Operador ++ prefijo
Posicion& Posicion::operator++(){
  puntero = puntero->siguiente;
  return *this;
}

//Operador ++ postfijo
Posicion Posicion::operator++(int){
  Posicion p(*this);
  //operator++();
  ++(*this);
  return p;
}

//Operador -- prefijo
Posicion& Posicion::operator--(){
  assert(puntero!=primera);
  CeldaLista* aux = primera;
  while(aux->siguiente!=puntero){
    aux = aux->siguiente;
  }
  puntero = aux;
  return *this;
}

//Operador -- postfijo
Posicion Posicion::operator--(int){
  Posicion p(*this);
  //operator--();
  --(*this);
  return p;
}

bool Posicion::operator==(const Posicion & p) const{
  return(puntero==p.puntero);
}

bool Posicion::operator!=(const Posicion &p) const{
  return(puntero!=p.puntero);
}

//Clase Lista

Lista::Lista(){
  ultima = cabecera = new CeldaLista;
  cabecera->siguiente = 0;
}

Lista::Lista(const Lista& l){
  ultima = cabecera = new CeldaLista;
  CeldaLista* orig = l.cabecera;
  while(orig->siguiente!=0){
    ultima->siguiente = new CeldaLista;
    ultima = ultima->siguiente;
    orig = orig->siguiente;
    ultima->elemento = orig->elemento;
  }
  ultima->siguiente = 0;
}

Lista::~Lista(){
  CeldaLista* aux;
  while(cabecera!=0){
    aux = cabecera;
    cabecera = cabecera->siguiente;
    delete aux;
  }
}

Lista& Lista::operator=(const Lista& l){
  Lista aux(l);
  swap(cabecera, aux.cabecera);
  swap(ultima, aux.ultima);
  return *this;
}

void Lista::set(Posicion p, Tbase e){
  p.puntero->siguiente->elemento = e;
}

Tbase Lista::get(Posicion p) const{
  return p.puntero->siguiente->elemento;
}

Posicion Lista::insertar(Posicion p, Tbase e){
  CeldaLista* nueva = new CeldaLista;
  nueva->elemento = e;
  nueva->siguiente = p.puntero->siguiente;
  p.puntero->siguiente = nueva;
  if(p.puntero == ultima)
    ultima = nueva;
  return p;
}

Posicion Lista::borrar(Posicion p){
  assert(p!=end());
  CeldaLista* aux = p.puntero->siguiente;
  p.puntero->siguiente = aux->siguiente;
  if(aux==ultima)
    ultima = p.puntero;
  delete aux;
  return p;
}

Posicion Lista::begin()const{
  Posicion p;
  p.puntero = p.primera = cabecera;
  return p;
}

Posicion Lista::end() const{
  Posicion p;
  p.puntero = ultima;
  p.primera = cabecera;
  return p;
}


