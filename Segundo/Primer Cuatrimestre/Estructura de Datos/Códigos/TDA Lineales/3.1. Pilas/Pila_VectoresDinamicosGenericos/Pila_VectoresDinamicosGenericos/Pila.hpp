#ifndef __PILA_H__
#define __PILA_H__

const int TAM =10;
template <class T>
class Pila{
private:
  T *datos;
  int reservados;
  int nelem;
public:
  Pila(int tam=TAM);
  Pila(const Pila & p);
  ~Pila();
  Pila & operator=(const Pila &p);
  
  bool vacia() const;
  void poner(const T &c);
  void operator+=(const T &c);
  void quitar();
  void operator--();
  void operator--(int i);
  T & tope();
  const T & tope() const;
  
private:
  void resize(int n);
  void copiar(const Pila& p);
  void liberar();
  void reservar(int n);
};

#include "Pila.tpp"
#endif /* Pila_hpp */

