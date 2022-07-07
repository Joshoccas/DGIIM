#ifndef __LISTA_H__
#define __LISTA_H__

template <class T>
struct CeldaLista{
  T elemento;
  CeldaLista<T>* anterior;
  CeldaLista<T>* siguiente;
};

template <class T> class Lista;

template <class T>
class Posicion{
private:
  CeldaLista<T>* puntero;
public:
  Posicion();
  //Posicion(const Posicion<T>& p);
  //~Posicion();
  //Posicion<T>& operator=(const Posicion& p);
  Posicion<T>& operator++();
  Posicion<T> operator++(int);
  Posicion<T>& operator--();
  Posicion<T> operator--(int);
  bool operator==(const Posicion<T>& p) const;
  bool operator!=(const Posicion<T>& p) const;
  friend class Lista<T>;
  T & operator*();
  T & operator*()const;
};

template <class T>
class Lista{
private:
  CeldaLista<T>* cabecera;
public:
  Lista();
  Lista(const Lista& l);
  ~Lista();
  Lista& operator=(const Lista& l);
  void set(Posicion<T> p, T e);
  T get(Posicion<T> p) const;
  Posicion<T> insertar(Posicion<T> p, const T &e);
  Posicion<T> borrar(Posicion<T> p);
  Posicion<T> begin() const;
  Posicion<T> end() const;
  //Otros métodos de la STL
  Lista(Posicion<T> inicio, Posicion<T> final);
  void clear();
  int size() const;
  void push_front(const T &dato);
  void push_back(const T &dato);
  void pop_front();
  void pop_back();
  T & front();
  const T & front() const;
  T & back() ;
  const T & back() const;
  void swap(Lista<T> & l);
};
#include "Lista.cpp"
#endif //__LISTA_H__
