#ifndef ABB_hpp
#define ABB_hpp
#include "ArbolBinario.hpp"

template <class Tbase>
class ABB{
private:
  //Declaramos Nodo y nodonulo por claridad del código
  //Si no, tendríamos que estar haciendo referencia
  //continuamente a Arbolbinario<Tbase>::
  typedef typename ArbolBinario<Tbase>::Nodo Nodo;
  const Nodo nodonulo = ArbolBinario<Tbase>::nodonulo;
  //Representación
  ArbolBinario<Tbase> arbolb;
public:
  ABB();
  ABB(const ABB<Tbase>& a);
  ABB(const Tbase& e);
  ~ABB();
  bool existe(const Tbase& e) const;
  void insertar(const Tbase& e);
  void borrar(const Tbase& e);
  void Esquema();
private:
  void borrar_nodo(Nodo n);

  /**
   Clase iterator para recorrer el árbol en Inorden
   */
public:
  class iterator{
  private:
    Nodo elnodo;
    iterator(Nodo n);
    friend class ABB<Tbase>;
    const Nodo nodonulo = ArbolBinario<Tbase>::nodonulo;
  public:
    iterator();
    iterator(const iterator & it);
    bool operator!=(const iterator & it) const;
    bool operator==(const iterator & it) const;
    iterator & operator=(const iterator & it);
    Tbase & operator*();
    iterator & operator++();
  };
  
  iterator begin();
  iterator end();
  
  class const_iterator{
  private:
    Nodo elnodo;
    const_iterator(Nodo n);
    friend class ArbolBinario<Tbase>;
    const Nodo nodonulo = ArbolBinario<Tbase>::nodonulo;
  public:
    const_iterator();
    const_iterator(const const_iterator & i);
    bool operator!=(const const_iterator & i) const;
    bool operator==(const const_iterator & i) const;
    const_iterator & operator=(const const_iterator & i);
    const Tbase & operator*() const;
    const_iterator & operator++();
  };
  
  const_iterator begin() const;
  const_iterator end() const;

};


//////////////////////////////////////
//////////////////////////////////////
//        IMPLEMENTACIÓN
//////////////////////////////////////
//////////////////////////////////////


template <class Tbase>
ABB<Tbase>::ABB(){
}

template <class Tbase>
ABB<Tbase>::ABB(const ABB<Tbase>& a):arbolb(a.arbolb){
}

template <class Tbase>
ABB<Tbase>::ABB(const Tbase& e):arbolb(e){
}

template <class Tbase>
ABB<Tbase>::~ABB(){
}

template <class Tbase>
bool ABB<Tbase>::existe(const Tbase &e) const{
  if(arbolb.vacio())
    return false;
  else{
    //Empezamos a buscar por la raíz
    Nodo n = arbolb.raiz();
    bool encontrado = false;
    //Mientras no lo hayamos encontrado
    //ni hayamos llegado a un nodo nulo
    while(!encontrado && n != nodonulo){
      if(arbolb.etiqueta(n)==e)
        encontrado = true;
      else if(e<arbolb.etiqueta(n))
        n = arbolb.izquierda(n);
      else
        n = arbolb.derecha(n);
    }
    return encontrado;
  }
}

template <class Tbase>
void ABB<Tbase>::insertar(const Tbase& e){
  if (arbolb.vacio())
    //Si el árbol está vacío
    arbolb = ArbolBinario<Tbase>(e);
  else{
    //Si el árbol no está vacío
    //Buscamos dónde insertar el nuevo nodo
    Nodo n = arbolb.raiz();
    bool posicionEncontrada = false;
    while(!posicionEncontrada){
      if (e<arbolb.etiqueta(n))
        if(arbolb.izquierda(n) != nodonulo)
          n = arbolb.izquierda(n);
        else
          posicionEncontrada = true;
      else
        if(arbolb.derecha(n) != nodonulo)
          n = arbolb.derecha(n);
        else
          posicionEncontrada = true;
    }
    //Una vez localizada la posición
    //creamos el nodo y lo insertamos
    ArbolBinario<Tbase> a(e);
    if (e<arbolb.etiqueta(n))
      arbolb.insertar_izquierda(n,a);
    else
      arbolb.insertar_derecha(n,a);
  }
}

template <class Tbase>
void ABB<Tbase>::borrar(const Tbase &e){
  if (!arbolb.vacio()){
    //Buscamos la etiqueta e en el árbol
    Nodo n = arbolb.raiz();
    bool encontrado = false;
    while(!encontrado && n!=nodonulo){
      if (e == arbolb.etiqueta(n))
        encontrado = true;
      else if(e<arbolb.etiqueta(n))
        n = arbolb.izquierda(n);
      else
        n = arbolb.derecha(n);
    }
    //Si lo hemos encontrado, lo borramos
    //Si no, no hacemos nada
    if (encontrado)
      borrar_nodo(n);
  }
}

template <class Tbase>
void ABB<Tbase>::borrar_nodo(typename ArbolBinario<Tbase>::Nodo n){
  
  if(arbolb.izquierda(n)==nodonulo)
    if(arbolb.derecha(n)==nodonulo){
      //Caso 1: n es un nodo hoja
      Nodo padre = arbolb.padre(n);
      if(padre == nodonulo)
        //El árbol sólo tiene un nodo
        arbolb = ArbolBinario<Tbase>();
      else if (n == arbolb.izquierda(padre)){
        //n es un nodo hoja y es hijo izquierdo de su padre
        //Sólo tenemos que eliminarlo
        ArbolBinario<Tbase> a;
        arbolb.podar_izquierda(padre, a);
      }
      else {
        //n es un nodo hoja y es hijo derecho de su padre
        //Sólo tenemos que eliminarlo
        ArbolBinario<Tbase> a;
        arbolb.podar_derecha(padre, a);
      }
    }
    else{
      //Caso 2: n sólo tiene un hijo a la derecha
      Nodo padre = arbolb.padre(n);
      if (padre != nodonulo){
        //Podamos el hijo para insertarlo en su lugar
        ArbolBinario<Tbase> a;
        arbolb.podar_derecha(n, a);
        if(n == arbolb.izquierda(padre))
          arbolb.insertar_izquierda(padre, a);
        else
          arbolb.insertar_derecha(padre, a);
      }
      else
        //n era la raíz y el subárbol derecho pasa
        //a ser el árbol
        arbolb.asignar_subarbol(arbolb, arbolb.derecha(n));
    }
  
  else //arbol.izquierda(n)!=nodonulo
    if(arbolb.derecha(n) == nodonulo){
      //Caso 3: n sólo tiene un hijo a la izquierda
      Nodo padre = arbolb.padre(n);
      if(padre != nodonulo){
        //Podamos el hijo para insertarlo en su lugar
        ArbolBinario<Tbase> a;
        arbolb.podar_izquierda(n, a);
        if(n == arbolb.izquierda(padre))
          arbolb.insertar_izquierda(padre, a);
        else
          arbolb.insertar_derecha(padre, a);
      }
      else
        //n era la raíz y el subárbol izquierdo pasa
        //a ser el árbol
        arbolb.asignar_subarbol(arbolb, arbolb.izquierda(n));
    }
    else{
      //Caso 4: el nodo tiene dos hijos
      Nodo mhi;
      //Buscamos el mayor hijo a la izquierda
      mhi = arbolb.izquierda(n);
      while(arbolb.derecha(mhi) != nodonulo)
        mhi = arbolb.derecha(mhi);
      arbolb.etiqueta(n) = arbolb.etiqueta(mhi);
      borrar_nodo(mhi);
    }
}



//////////////////////////////
// ITERADORES
//////////////////////////////

template <class Tbase>
ABB<Tbase>::iterator::iterator():elnodo(0){
}

template <class Tbase>
ABB<Tbase>::iterator::iterator(Nodo n):elnodo(n){
}

template <class Tbase>
ABB<Tbase>::iterator::iterator(const ABB<Tbase>::iterator& it):elnodo(it.elnodo){
}

template <class Tbase>
bool ABB<Tbase>::iterator::operator==(const ABB<Tbase>::iterator &it)const{
  return elnodo == it.elnodo;
}

template <class Tbase>
bool ABB<Tbase>::iterator::operator!=(const ABB<Tbase>::iterator &it)const{
  return elnodo != it.elnodo;
}

template <class Tbase>
typename ABB<Tbase>::iterator&
ABB<Tbase>::iterator::operator=(const ABB::iterator &it){
  if (this!=&it)
    elnodo = it.elnodo;
  return *this;
}

template <class Tbase>
Tbase& ABB<Tbase>::iterator::operator*(){
  return elnodo->etiqueta;
}

template <class Tbase>
typename ABB<Tbase>::iterator& ABB<Tbase>::iterator::operator++(){
//  if(elnodo==nodonulo)
//    return *this;
  assert(elnodo!=nodonulo);
  
  if(elnodo->drcha != nodonulo){
    //Si hay hijo derecho, buscamos
    //su descendiente más a la izquierda
    elnodo = elnodo->drcha;
    while(elnodo->izqda != nodonulo)
      elnodo = elnodo->izqda;
  }
  else{
    //Si no hay hijo derecho
    //Ascendemos mientras sigamos subiendo
    //por hijos derechos
    while(elnodo->padre != nodonulo &&
          elnodo->padre->drcha == elnodo)
      elnodo = elnodo->padre;
    elnodo = elnodo->padre;
  }
  return *this;
}

template <class Tbase>
typename ABB<Tbase>::iterator ABB<Tbase>::begin(){
  Nodo n = arbolb.raiz();
  if(n != nodonulo)
    while(n->izqda != nodonulo)
      n = n->izqda;
  return ABB<Tbase>::iterator(n);
}

template <class Tbase>
typename ABB<Tbase>::iterator ABB<Tbase>::end(){
  return iterator(nodonulo);
}

//////////////////////////////

template <class Tbase>
ABB<Tbase>::const_iterator::const_iterator():elnodo(0){
}

template <class Tbase>
ABB<Tbase>::const_iterator::const_iterator(typename ArbolBinario<Tbase>::Nodo n):elnodo(n){
}


template <class Tbase>
ABB<Tbase>::const_iterator::const_iterator(const ABB<Tbase>::const_iterator& it):elnodo(it.elnodo){
}

template <class Tbase>
bool ABB<Tbase>::const_iterator::operator!=(const ABB<Tbase>::const_iterator &it)const{
  return elnodo != it.elnodo;
}

template <class Tbase>
bool ABB<Tbase>::const_iterator::operator==(const ABB<Tbase>::const_iterator &it)const{
  return elnodo == it.elnodo;
}

template <class Tbase>
typename ABB<Tbase>::const_iterator&
ABB<Tbase>::const_iterator::operator=(const ABB::const_iterator &it){
  if (this!=&it)
    elnodo = it.elnodo;
  return *this;
}

template <class Tbase>
const Tbase& ABB<Tbase>::const_iterator::operator*()const{
  return elnodo->etiqueta;
}

template <class Tbase>
typename ABB<Tbase>::const_iterator& ABB<Tbase>::const_iterator::operator++(){
  if(elnodo==nodonulo)
    return *this;
  if(elnodo->drcha != nodonulo){
    elnodo = elnodo->drcha;
    while(elnodo->izqda != nodonulo)
      elnodo = elnodo->izqda;
  }
  else{
    while(elnodo->padre != nodonulo &&
          elnodo->padre->drcha == elnodo)
      elnodo = elnodo->padre;
    elnodo = elnodo->padre;
  }
  return *this;
}


template <class Tbase>
typename ABB<Tbase>::const_iterator ABB<Tbase>::begin()const{
  Nodo n = arbolb.raiz();
  if(n != nodonulo)
    while(n->izqda != nodonulo)
      n = n->izqda;
  return ABB<Tbase>::iterator(n);
}

template <class Tbase>
typename ABB<Tbase>::const_iterator ABB<Tbase>::end()const{
  return iterator(nodonulo);
}

template <class Tbase>
void ABB<Tbase>::Esquema(){
  string pre = "";
  arbolb.Esquema(arbolb.raiz(), pre);
}



#endif /* ABB_hpp */
