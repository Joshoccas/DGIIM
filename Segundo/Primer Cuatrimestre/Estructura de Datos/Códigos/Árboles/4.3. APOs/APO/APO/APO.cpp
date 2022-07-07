#include <cassert>
#include <iostream>
#include "APO.hpp"

using namespace std;

template <class Tbase>
APO<Tbase>::APO(){
  nelementos = 0;
  reservar(1);
}

template <class Tbase>
APO<Tbase>::APO(int tam){
  assert(tam>0);
  reservar(tam);
  nelementos = 0;
}

template <class Tbase>
APO<Tbase>::APO(const APO<Tbase>& otro){
  reservar((otro.nelementos==0) ? 1 : otro.nelementos);
  copiar(otro);
}

template <class Tbase>
APO<Tbase>::~APO(){
  liberar();
}

template <class Tbase>
APO<Tbase>& APO<Tbase>::operator=(const APO<Tbase> &otro){
  if (this != &otro){
    liberar();
    reservar((otro.nelementos==0) ? 1: otro.nelementos);
    copiar(otro);
  }
  return *this;
}

template <class Tbase>
void APO<Tbase>::clear(){
  nelementos = 0;
}

template <class Tbase>
int APO<Tbase>::size() const{
  return nelementos;
}

template <class Tbase>
bool APO<Tbase>::empty() const{
  return (nelementos == 0);
}

template <class Tbase>
const Tbase& APO<Tbase>::raiz() const{
  assert(nelementos>0);
  return vec[0];
}

template <class Tbase>
void APO<Tbase>::insertar(const Tbase &e){
  int pos, pos_padre;
  if (nelementos == reservados)
    expandir(2*reservados);
  //Insertamos en la hoja más a la derecha
  pos = nelementos;
  vec[pos] = e;
  //Mientras el elemento sea menor que su padre
  //lo promocionamos, intercambiándolo con él
  pos_padre = (pos-1)/2;
  while((pos>0) && (vec[pos]<vec[pos_padre])){
    swap(vec[pos], vec[pos_padre]);
    pos = pos_padre;
    pos_padre = (pos-1)/2;
  }
  nelementos++;
}

template <class Tbase>
void APO<Tbase>::borrar_raiz(){
  int pos, pos_min, ultimo, pos_hizq, pos_hder;
  bool terminar;
  
  assert(nelementos>0);
  //Colocamos la última hoja en la raíz
  vec[0] = vec[nelementos-1];
  nelementos--;
  if(nelementos>1){
    ultimo = nelementos-1;
    pos = 0;
    terminar = false;
    //Mientras queden niveles por recorrer (bajada)
    while(pos<=(ultimo-1)/2 && !terminar){
      pos_hizq = 2*pos+1;
      pos_hder = pos_hizq+1;
      //Si no hay hijo derecha
      if(ultimo == pos_hizq)
        //el minimo de los hijos es el izquierdo
        pos_min = pos_hizq;
      //Si tiene los dos hijos, los comparamos para seleccionar el mínimo
      else pos_min = (vec[pos_hizq]<vec[pos_hder] ? pos_hizq : pos_hder);
      //Si es mayor que el mínimo de los hijos
      //promocionamos ese hijo intercambiándolos
      if(vec[pos_min]<vec[pos]){
        swap(vec[pos], vec[pos_min]);
        pos = pos_min;
      }
      else //Si no, hemos terminado
        terminar = true;
    }
  }
}


//Métodos auxiliares privados

template <class Tbase>
void APO<Tbase>::expandir(int tam){
  assert(tam>reservados);
  APO<Tbase> aux(tam);
  
  aux.copiar(*this);
  
  swap(aux.vec, this->vec);
  this->reservados = aux.reservados;
  //El destructor de aux libera el antiguo
  //espacio reservado de *this
}

template <class Tbase>
void APO<Tbase>::reservar(int tam){
  assert(tam>0);
  vec = new Tbase[tam];
  reservados = tam;
}

template <class Tbase>
void APO<Tbase>::liberar(){
  delete [] vec;
}

template <class Tbase>
void APO<Tbase>::copiar(const APO<Tbase>& otro){
  assert(reservados>=otro.nelementos);
  nelementos = otro.nelementos;
  for(int i=0; i<nelementos; i++)
    vec[i] = otro.vec[i];
}
