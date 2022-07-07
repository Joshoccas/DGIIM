#ifndef __LISTA_H__
#define __LISTA_H__

template <class T>
struct CeldaLista{
  T elemento;
  CeldaLista* anterior;
  CeldaLista* siguiente;
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
  Posicion<T> insertar(Posicion<T> p, T e);
  Posicion<T> borrar(Posicion<T> p);
  Posicion<T> begin() const;
  Posicion<T> end() const;
};
#include "Lista.cpp"
#endif //__LISTA_H__
