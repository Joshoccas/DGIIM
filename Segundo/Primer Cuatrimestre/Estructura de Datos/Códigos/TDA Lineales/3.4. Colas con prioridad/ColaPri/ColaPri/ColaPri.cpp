#include <cassert>
#include <utility>
#include "ColaPri.hpp"

ColaPri::ColaPri(){
  primera = 0;
}

ColaPri::ColaPri(const ColaPri& c){
  if(c.primera==0) //Si está vacía
    primera = 0;
  else{            //Si no está vacía
    primera = new CeldaColaPri;      //Crea la primera celda
    primera->dato = c.primera->dato; //Copia el dato
    CeldaColaPri* src = c.primera;   //Inicializa punteros
    CeldaColaPri* dest = primera;
    while(src->sig!=0){              //Mientras queden celdas
      dest->sig = new CeldaColaPri;  //Crea nueva celda
      src = src->sig;                //Avanza punteros
      dest = dest->sig;
      dest->dato = src->dato;        //Copia el dato
    }
    dest->sig = 0;                   //Ajusta el puntero de la última
  }
}

ColaPri::~ColaPri(){
  CeldaColaPri* aux;
  while(primera != 0){        //Mientras queden celdas
    aux = primera;            //Referencia a la primera celda
    primera = primera->sig;   //Avanza primera
    delete aux;               //Borra la celda
  }
}

ColaPri& ColaPri::operator=(const ColaPri &c){
  ColaPri colatemp(c);    //Usamos el constructor de copia
  swap(this->primera, colatemp.primera);
  return *this;
  //El destructor libera el contenido de *this
}

bool ColaPri::vacia() const{
  return (primera==0);
}

Tbase ColaPri::frente()const{
  assert(primera!=0);
  return (primera->dato.elemento);
}

Tprio ColaPri::prioridad_frente() const{
  assert(primera!=0);
  return(primera->dato.prioridad);
}

void ColaPri::quitar(){
  assert(primera!=0);
  CeldaColaPri* aux = primera;
  primera = primera->sig;
  delete aux;
}

void ColaPri::poner(Tbase e, Tprio prio){
  CeldaColaPri* aux = new CeldaColaPri;  //Creamos una nueva celda
  aux->dato.elemento = e;                //Guardamos la información
  aux->dato.prioridad = prio;
  aux->sig = 0;
  if (primera==0)                        //Si la cola está vacía
    primera = aux;
  else if(primera->dato.prioridad<prio){ //Si no está vacía y tiene
                                         //prioridad máxima
    aux->sig = primera;                  //La insertamos la primera
    primera = aux;
  }
  else{                                  //Caso general
    CeldaColaPri* p = primera;
    while(p->sig!=0){                    //Avanza por las celdas
      if(p->sig->dato.prioridad<prio){
        aux->sig = p->sig;
        p->sig = aux;
        return;
      }
      else p = p->sig;
    }
    p->sig = aux;
  }
}



