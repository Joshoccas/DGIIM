#include <cassert>

//
// Operaciones de nodewrapper
//
template <typename T>
bintree<T>::nodewrapper::nodewrapper()
//:pad(0),izda(0),dcha(0)
{
}


template <typename T>
bintree<T>::nodewrapper::nodewrapper(const T & e):etiqueta(e)
//,pad(0),izda(0),dcha(0)
{
}


//
// Operaciones de node
//

template <typename T>
bintree<T>::node::node(){
  elnodo = 0;
};


template <typename T>
bintree<T>::node::node(const T & e){
  elnodo = new nodewrapper(e);
}


template <typename T>
bintree<T>::node::node(const typename bintree<T>::node & n): elnodo(n.elnodo){
}


template <typename T>
typename bintree<T>::node &
bintree<T>::node::operator=(const typename bintree<T>::node & n){
  if (this != &n)
    elnodo = n.elnodo;
  return *this;
}

template <typename T>
bool bintree<T>::node::null() const{
  return elnodo == 0;
}


template <typename T>
typename bintree<T>::node bintree<T>::node::parent() const{
  return (elnodo->pad);
}


template <typename T>
typename bintree<T>::node bintree<T>::node::left() const{
  return (elnodo->izda);
}


template <typename T>
typename bintree<T>::node bintree<T>::node::right() const{
  return (elnodo->dcha);
}


template <typename T>
T & bintree<T>::node::operator*(){
  return elnodo->etiqueta;
}


template <typename T>
const T & bintree<T>::node::operator*() const{
  return elnodo->etiqueta;
}


template <typename T>
void bintree<T>::node::remove(){
  delete elnodo;
  elnodo = 0;
}


template <typename T>
bool bintree<T>::node::operator==(const node & n) const{
  return elnodo == n.elnodo;
}


template <typename T>
bool bintree<T>::node::operator!=(const node & n) const{
  return elnodo != n.elnodo;
}


//Funciones privadas para uso exclusivo de bintree


template <typename T>
void bintree<T>::node::parent(typename bintree<T>::node n){
  elnodo->pad = n;
}


template <typename T>
void bintree<T>::node::left(typename bintree<T>::node n){
  elnodo->izda = n;
}


template <typename T>
void bintree<T>::node::right(typename bintree<T>::node n){
  elnodo->dcha = n;
}



