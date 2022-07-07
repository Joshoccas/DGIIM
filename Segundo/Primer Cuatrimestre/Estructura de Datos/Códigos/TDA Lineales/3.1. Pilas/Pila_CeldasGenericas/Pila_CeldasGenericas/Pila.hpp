#ifndef __PILA_H__
#define __PILA_H__

template <class T>
struct CeldaPila{
  T elemento;
  CeldaPila * sig;
};

template <class T>
class Pila{
private:
  CeldaPila<T> * primera;
public:
  Pila();
  Pila(const Pila& p);
  ~Pila();
  Pila& operator=(const Pila& p);
  bool vacia() const;
  void poner(const T &c);
  void quitar();
  T & tope();
  const T &tope() const;
private:
  void copiar(const Pila& p);
  void liberar();
};

#include "Pila.tpp"
#endif // Pila_hpp

