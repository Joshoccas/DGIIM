#include <cassert>
#include "Lista.hpp"

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

Lista::Lista(){
  nelementos = 0;
  reservar(1);
}

Lista::Lista(const Lista& l){
  reservar(l.nelementos);
  copiar(l);
}

Lista::~Lista(){
  liberar();
}

Lista& Lista::operator=(const Lista &l){
  if (this != &l){
    liberar();
    reservar(l.nelementos);
    copiar(l);
  }
  return *this;
}

void Lista::set(const Posicion & p, const Tbase &e){
  assert(p.i>=0 && p.i<nelementos);
  datos[p.i] = e;
}

Tbase Lista::get(const Posicion & p) const{
  assert(p.i>=0 && p.i<nelementos);
  return datos[p.i];
}

Posicion Lista::insertar(const Posicion & p, const Tbase & e){
  if(nelementos == reservados)
    redimensionar(reservados*2);
  for(int j=nelementos; j>p.i; j--)
    datos[j] = datos[j-1];
  datos[p.i] = e;
  nelementos++;
  return p;
}

Posicion Lista::borrar(const Posicion & p){
  assert(p!=end());
  for(int j=p.i; j<nelementos-1; j++)
    datos[j] = datos[j+1];
  nelementos--;
  if (nelementos<reservados/4)
    redimensionar(reservados/2);
  return p;
}

Posicion Lista::begin() const{
  Posicion p;
  p.i = 0; //Innecesario
  return p;
}

Posicion Lista::end() const{
  Posicion p;
  p.i = nelementos;
  return p;
}

//Métodos auxiliares privados

void Lista::liberar(){
  delete []datos;
  reservados = nelementos = 0;
}


void Lista::reservar(int n){
  assert(n>0);
  reservados = n;
  datos = new Tbase[reservados];
}

void Lista::copiar(const Lista& l){
  nelementos = l.nelementos;
  for(int i=0; i<nelementos; i++)
    datos[i] = l.datos[i];
}

void Lista::redimensionar(int n){
  assert(n>0 && n>=nelementos);
  Tbase* aux = datos;
  reservar(n);
  for(int i=0; i<nelementos; i++)
    datos[i] = aux[i];
//  memcpy(datos, aux, nelementos*sizeof(Tbase));
  delete[] aux;
}

