#ifndef __LISTA_H__
#define __LISTA_H__

typedef char Tbase;

template <class T>
struct CeldaLista{
  T elemento;
  CeldaLista* siguiente;
};

template <class T> class Lista;

template <class T>
class Posicion{
private:
  CeldaLista<T>* puntero;
  CeldaLista<T>* primera;
public:
  Posicion();
  Posicion(const Posicion& p) = default;
  ~Posicion() = default;
  Posicion& operator=(const Posicion& p) = default;
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
  CeldaLista<T>* ultima;
public:
  Lista();
  Lista(const Lista<T>& l);
  ~Lista();
  Lista& operator=(const Lista<T>& l);
  
  T get(Posicion<T> p) const;
  void set(Posicion<T> p, T e);
  Posicion<T> insertar(Posicion<T> p, T e);
  Posicion<T> borrar(Posicion<T> p);
  Posicion<T> begin() const;
  Posicion<T> end() const;
};

#include "Lista.tpp"
#endif // __LISTA_H__
