#include <cassert>
#include "ColaPri.hpp"

template <class T>
ColaPri<T>::ColaPri(){
  primera = 0;
}

template <class T>
ColaPri<T>::ColaPri(const ColaPri<T>& c){
  if(c.primera==0) //Si está vacía
    primera = 0;
  else{            //Si no está vacía
    primera = new CeldaColaPri<T>;      //Crea la primera celda
    primera->dato = c.primera->dato; //Copia el dato
    CeldaColaPri<T>* src = c.primera;   //Inicializa punteros
    CeldaColaPri<T>* dest = primera;
    while(src->sig!=0){              //Mientras queden celdas
      dest->sig = new CeldaColaPri<T>;  //Crea nueva celda
      src = src->sig;                //Avanza punteros
      dest = dest->sig;
      dest->dato = src->dato;        //Copia el dato
    }
    dest->sig = 0;                   //Ajusta el puntero de la última
  }
}

template <class T>
ColaPri<T>::~ColaPri(){
  CeldaColaPri<T>* aux;
  while(primera != 0){        //Mientras queden celdas
    aux = primera;            //Referencia a la primera celda
    primera = primera->sig;   //Avanza primera
    delete aux;               //Borra la celda
  }
}

template <class T>
ColaPri<T>& ColaPri<T>::operator=(const ColaPri<T> &c){
  ColaPri<T> colatemp(c);    //Usamos el constructor de copia
  swap(this->primera, colatemp.primera);
  return *this;
  //El destructor libera el contenido de *this
}

template <class T>
bool ColaPri<T>::vacia() const{
  return (primera==0);
}

template <class T>
T ColaPri<T>::frente()const{
  assert(primera!=0);
  return (primera->dato);
}

template <class T>
void ColaPri<T>::quitar(){
  assert(primera!=0);
  CeldaColaPri<T>* aux = primera;
  primera = primera->sig;
  delete aux;
}

template <class T>
void ColaPri<T>::poner(T e){
  CeldaColaPri<T>* aux = new CeldaColaPri<T>; //Creamos una nueva celda
  aux->dato = e;                         //Guardamos la información
  aux->sig = 0;
  if (primera==0)                        //Si la cola está vacía
    primera = aux;
  else if(primera->dato<e){ //Si no está vacía y tiene
    //prioridad máxima
    aux->sig = primera;                  //La insertamos la primera
    primera = aux;
  }
  else{                                  //Caso general
    CeldaColaPri<T>* p = primera;
//    while(p->sig!=0){                    //Avanza por las celdas
//      if(p->sig->dato<e){
//        aux->sig = p->sig;
//        p->sig = aux;
//        return;
//      }
//      else p = p->sig;
//    }
    bool salir = false;
    while(p->sig!=0 && !salir){                    //Avanza por las celdas
      if(p->sig->dato<e){
        aux->sig = p->sig;
        p->sig = aux;
        salir = true;
      }
      else p = p->sig;
    }
    p->sig = aux;
  }
}



