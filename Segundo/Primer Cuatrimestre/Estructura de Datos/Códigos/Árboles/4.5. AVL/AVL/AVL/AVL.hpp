#ifndef AVL_hpp
#define AVL_hpp
#include "ArbolBinario.hpp"

template <class Tbase>
class AVL{
public:
  //Declaramos Nodo y nodonulo por claridad del código
  //Si no, tendríamos que estar haciendo referencia
  //continuamente a Arbolbinario<Tbase>::
  //lo que dificulta notablemente la legibilidad del código
  typedef typename ArbolBinario<Tbase>::Nodo Nodo;
  const Nodo nodonulo = ArbolBinario<Tbase>::nodonulo;
private:
  //Representación
  //Un AVL al fin y al cabo es un árbol binario de búsqueda
  //en el que realizamos ajustes para mantenerlo equilibrado
  ArbolBinario<Tbase> arbolb;
public:
  AVL();
  AVL(const AVL<Tbase>& a);
  AVL(const Tbase& e);
  ~AVL();
  bool existe(const Tbase& e) const;
  void insertar(const Tbase& e);
  void borrar(const Tbase& e);
  void Esquema();
private:
  Nodo buscar(const Tbase & e) const;
  void ajustarArbol(Nodo& n);
  void rotacionSimpleADerecha(Nodo& n);
  void rotacionSimpleAIzquierda(Nodo& n);
  void borrar_nodo(Nodo n);
  
  //Clase iterator para recorrer el árbol en Inorden
  
public:
  class iterator{
  private:
    Nodo elnodo;
    iterator(Nodo n);
    friend class AVL<Tbase>;
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
  
  //Clase const_iterator para recorrer el árbol en Inorden

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
AVL<Tbase>::AVL(){
}

template <class Tbase>
AVL<Tbase>::AVL(const AVL<Tbase>& a):arbolb(a.arbolb){
}

template <class Tbase>
AVL<Tbase>::AVL(const Tbase& e):arbolb(e){
}

template <class Tbase>
AVL<Tbase>::~AVL(){
}

template <class Tbase>
bool AVL<Tbase>::existe(const Tbase &e) const{
  return (buscar(e) != nodonulo);
}

template <class Tbase>
void AVL<Tbase>::insertar(const Tbase& e){
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
    
    //Ajustamos el árbol desde el nodo n hacia la raíz
    ajustarArbol(n);
  }
}

template <class Tbase>
void AVL<Tbase>::borrar(const Tbase &e){
  Nodo n = buscar(e);
  //  if(buscar(e) != nodonulo)
  if(n != nodonulo)
    borrar_nodo(n);
}


template <class Tbase>
void AVL<Tbase>::Esquema(){
  string pre = "";
  arbolb.Esquema(arbolb.raiz(), pre);
}

//////////////////////
//Métodos privados
//////////////////////

template <class Tbase>
void AVL<Tbase>::borrar_nodo(typename ArbolBinario<Tbase>::Nodo n){
  
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
        //Ajustamos desde el padre
        ajustarArbol(padre);
      }
      else {
        //n es un nodo hoja y es hijo derecho de su padre
        //Sólo tenemos que eliminarlo
        ArbolBinario<Tbase> a;
        arbolb.podar_derecha(padre, a);
        //Ajustamos desde el padre
        ajustarArbol(padre);
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
        //Ajustamos desde el padre
        ajustarArbol(padre);
      }
      else
        //n era la raíz y el subárbol derecho pasa
        //a ser el árbol
        arbolb.asignar_subarbol(arbolb, arbolb.derecha(n));
      //No tenemos que ajustar
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
          //Ajustamos desde el padre
          ajustarArbol(padre);
        }
        else
          //n era la raíz y el subárbol izquierdo pasa
          //a ser el árbol
          arbolb.asignar_subarbol(arbolb, arbolb.izquierda(n));
        //No tenemos que ajustar
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


template <class Tbase>
typename ArbolBinario<Tbase>::Nodo AVL<Tbase>::buscar(const Tbase & e) const{
  Nodo n = arbolb.raiz();
  bool encontrado = false;
  //Mientras no lo hayamos encontrado
  //ni hayamos llegado a un nodo nulo
  while(!encontrado && n != nodonulo)
    if(arbolb.etiqueta(n)==e)
      encontrado = true;
    else if(e<arbolb.etiqueta(n))
      n = arbolb.izquierda(n);
    else
      n = arbolb.derecha(n);
  return n;
}


template <class Tbase>
void AVL<Tbase>::ajustarArbol(Nodo &n){
  int alturaIzqda, alturaDrcha;
  Nodo hijoIzqda, hijoDrcha;
//  cout << "Ajuste " << arbolb.etiqueta(n) << endl;
  //Ajustamos desde n hacia arriba, hasta la raíz del árbol
  while(n != nodonulo){
    alturaIzqda = arbolb.altura(arbolb.izquierda(n));
    alturaDrcha = arbolb.altura(arbolb.derecha(n));
    
    if (abs(alturaIzqda-alturaDrcha)>1){ //Hay que ajustar
      if(alturaIzqda>alturaDrcha){
        //Exceso de altura por la izquierda
        hijoIzqda = arbolb.izquierda(n);
        if(arbolb.altura(arbolb.izquierda(hijoIzqda))>
           arbolb.altura(arbolb.derecha(hijoIzqda)))
          //Desequilibrio en el hijo izquierdo del hijo izquierdo
          rotacionSimpleADerecha(n);
        else{
          //Desequilibrio en el hijo derecho del hijo izquierdo
          //Rotación doble a la derecha
          rotacionSimpleAIzquierda(hijoIzqda);
          rotacionSimpleADerecha(n);
        }
      }
      else{
        //Exceso de altura por la derecha
        hijoDrcha = arbolb.derecha(n);
        if(arbolb.altura(arbolb.derecha(hijoDrcha))>
           arbolb.altura(arbolb.izquierda(hijoDrcha)))
          //Desequilibrio en el hijo derecho del hijo derecho
          rotacionSimpleAIzquierda(n);
        else{
          //Desequilibrio en el hijo izquierdo del hijo derecho
          //Rotación doble a la izquierda
          rotacionSimpleADerecha(hijoDrcha);
          rotacionSimpleAIzquierda(n);
        }
      }
    }
    n = arbolb.padre(n);
  }
}



template <class Tbase>
void AVL<Tbase>::rotacionSimpleADerecha(Nodo &n){
  assert(n!=nodonulo);
  
  enum hijo {izquierdo, derecho};
  hijo que_hijo;
  Nodo padre = arbolb.padre(n);
  
  cout << "RSD " << arbolb.etiqueta(n) << endl;
  
  ArbolBinario<Tbase> a;
  //Podamos el subárbol izquierdo del nodo
  //en el que se ha producido el desequilibrio
  arbolb.podar_izquierda(n, a);
  
  ArbolBinario<Tbase> aux;
  
  if(padre!=nodonulo){
    //Podamos el nodo en el que se ha producido el desequilibrio
    //y anotamos qué hijo era, si el derecho o el izquierdo
    if(arbolb.izquierda(padre)==n){
      arbolb.podar_izquierda(padre, aux);
      que_hijo = izquierdo;
    }
    else{
      arbolb.podar_derecha(padre, aux);
      que_hijo = derecho;
    }
    
    ArbolBinario<Tbase> b;
    //Podamos el hijo derecho del hijo izquierdo,
    //que habíamos podado antes y habíamos guardado en a
    a.podar_derecha(a.raiz(), b);
    //Insertamos la rama podada como hijo izquierdo
    //del nodo n, el que estaba desequilibrado
    aux.insertar_izquierda(aux.raiz(), b);
    //Insertamos el nodo n como hijo derecho
    //del que era el hijo izquierdo
    a.insertar_derecha(a.raiz(), aux);
    
    //Reubicamos la rama rotada como hija del padre de n
    if(que_hijo == izquierdo){
      arbolb.insertar_izquierda(padre, a);
      n = arbolb.izquierda(padre);
    }
    else{
      arbolb.insertar_derecha(padre, a);
      n = arbolb.derecha(padre);
    }
    
  }
  else{
    //En el caso en el que n es la raíz del árbol,
    //la rotación se simplifica, ya que no tenemos
    //que reenganchar la rama rotada como hija del padre.
    //Directamente, esa rama es el árbol
    aux = arbolb;
    
    ArbolBinario<Tbase> b;
    a.podar_derecha(a.raiz(), b);
    aux.insertar_izquierda(aux.raiz(), b);
    a.insertar_derecha(a.raiz(), aux);
    arbolb = a;
    n = arbolb.raiz();
  }
}


template <class Tbase>
void AVL<Tbase>::rotacionSimpleAIzquierda(Nodo &n){
  assert(n!=nodonulo);
  enum hijo {izquierdo, derecho};
  hijo que_hijo;
  Nodo padre = arbolb.padre(n);
  
  cout << "RSI " << arbolb.etiqueta(n) << endl;
  
  ArbolBinario<Tbase> a;
  //Podamos el subárbol derecho del nodo
  //en el que se ha producido el desequilibrio
  arbolb.podar_derecha(n, a);
  
  ArbolBinario<Tbase> aux;
  
  if(padre!=nodonulo){
    //Podamos el nodo en el que se ha producido el desequilibrio
    //y anotamos qué hijo era, si el derecho o el izquierdo
    if(arbolb.izquierda(padre)==n){
      arbolb.podar_izquierda(padre, aux);
      que_hijo = izquierdo;
    }
    else{
      arbolb.podar_derecha(padre, aux);
      que_hijo = derecho;
    }
    
    ArbolBinario<Tbase> b;
    //Podamos el hijo izquierdo del hijo derecho,
    //que habíamos podado antes y habíamos guardado en a
    a.podar_izquierda(a.raiz(), b);
    //Insertamos la rama podada como hijo derecho
    //del nodo n, el que estaba desequilibrado
    aux.insertar_derecha(aux.raiz(), b);
    //Insertamos el nodo n como hijo izquierdo
    //del que era el hijo derecho
    a.insertar_izquierda(a.raiz(), aux);
    
    //Reubicamos la rama rotada como hija del padre de n
    if(que_hijo == izquierdo){
      arbolb.insertar_izquierda(padre, a);
      n = arbolb.izquierda(padre);
    }
    else{
      arbolb.insertar_derecha(padre, a);
      n = arbolb.derecha(padre);
    }
  }
  else{
    //En el caso en el que n es la raíz del árbol,
    //la rotación se simplifica, ya que no tenemos
    //que reenganchar la rama rotada como hija del padre.
    //Directamente, esa rama es el árbol
    aux = arbolb;
    
    ArbolBinario<Tbase> b;
    a.podar_izquierda(a.raiz(), b);
    aux.insertar_derecha(aux.raiz(), b);
    a.insertar_izquierda(a.raiz(), aux);
    arbolb = a;
    n = arbolb.raiz();
  }
}




//////////////////////////////
// ITERADORES
//////////////////////////////

template <class Tbase>
AVL<Tbase>::iterator::iterator():elnodo(0){
}

template <class Tbase>
AVL<Tbase>::iterator::iterator(Nodo n):elnodo(n){
}

template <class Tbase>
AVL<Tbase>::iterator::iterator(const AVL<Tbase>::iterator& it):elnodo(it.elnodo){
}

template <class Tbase>
bool AVL<Tbase>::iterator::operator==(const AVL<Tbase>::iterator &it)const{
  return elnodo == it.elnodo;
}

template <class Tbase>
bool AVL<Tbase>::iterator::operator!=(const AVL<Tbase>::iterator &it)const{
  return elnodo != it.elnodo;
}

template <class Tbase>
typename AVL<Tbase>::iterator&
AVL<Tbase>::iterator::operator=(const AVL::iterator &it){
  if (this!=&it)
    elnodo = it.elnodo;
  return *this;
}

template <class Tbase>
Tbase& AVL<Tbase>::iterator::operator*(){
  return elnodo->etiqueta;
}

template <class Tbase>
typename AVL<Tbase>::iterator& AVL<Tbase>::iterator::operator++(){
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
    //Si el nodo es hijo izquierdo, el siguiente es el padre
    //Si el nodo es hijo derecho, ascendemos mientras sigamos
    //subiendo por hijos derechos
    while(elnodo->padre != nodonulo &&
          elnodo->padre->drcha == elnodo)
      elnodo = elnodo->padre;
    elnodo = elnodo->padre;
  }
  return *this;
}

template <class Tbase>
typename AVL<Tbase>::iterator AVL<Tbase>::begin(){
  //Partimos de la raíz
  Nodo n = arbolb.raiz();
  if(n != nodonulo)
    //Mientras haya hijo izquierda, descendemos
    while(n->izqda != nodonulo)
      n = n->izqda;
  return AVL<Tbase>::iterator(n);
}

template <class Tbase>
typename AVL<Tbase>::iterator AVL<Tbase>::end(){
  return iterator(nodonulo);
}

//////////////////////////////

template <class Tbase>
AVL<Tbase>::const_iterator::const_iterator():elnodo(0){
}

template <class Tbase>
AVL<Tbase>::const_iterator::const_iterator(Nodo n):elnodo(n){
}


template <class Tbase>
AVL<Tbase>::const_iterator::const_iterator(const AVL<Tbase>::const_iterator& it):elnodo(it.elnodo){
}

template <class Tbase>
bool AVL<Tbase>::const_iterator::operator!=(const AVL<Tbase>::const_iterator &it)const{
  return elnodo != it.elnodo;
}

template <class Tbase>
bool AVL<Tbase>::const_iterator::operator==(const AVL<Tbase>::const_iterator &it)const{
  return elnodo == it.elnodo;
}

template <class Tbase>
typename AVL<Tbase>::const_iterator&
AVL<Tbase>::const_iterator::operator=(const AVL::const_iterator &it){
  if (this!=&it)
    elnodo = it.elnodo;
  return *this;
}

template <class Tbase>
const Tbase& AVL<Tbase>::const_iterator::operator*()const{
  return elnodo->etiqueta;
}

template <class Tbase>
typename AVL<Tbase>::const_iterator& AVL<Tbase>::const_iterator::operator++(){
  //Si el nodo es nulo, no hacemos nada
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
  //Si no hay hijo derecho
  //Si el nodo es hijo izquierdo, el siguiente es el padre
  //Si el nodo es hijo derecho, ascendemos mientras sigamos
  //subiendo por hijos derechos
  else{
    while(elnodo->padre != nodonulo &&
          elnodo->padre->drcha == elnodo)
      elnodo = elnodo->padre;
    elnodo = elnodo->padre;
  }
  return *this;
}


template <class Tbase>
typename AVL<Tbase>::const_iterator AVL<Tbase>::begin()const{
  //Partimos de la raíz
  Nodo n = arbolb.raiz();
  if(n != nodonulo)
    //Mientras haya hijo izquierda, descendemos
    while(n->izqda != nodonulo)
      n = n->izqda;
  return AVL<Tbase>::iterator(n);
}

template <class Tbase>
typename AVL<Tbase>::const_iterator AVL<Tbase>::end()const{
  return iterator(nodonulo);
}


#endif /* AVL_hpp */

