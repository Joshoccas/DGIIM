#ifndef __COLA_H__
#define __COLA_H__


template <class T>
class Cola{
private:
  T * datos;
  int reservados;
  int nelem;
  int anterior, posterior;
public:
  Cola();
  Cola(const Cola& c);
  ~Cola();
  Cola& operator=(const Cola & c);
  bool vacia() const;
  void poner(const T & valor);
  void quitar();
  T frente() const;
private:
  void reservar(const int n);
  void liberar();
  void copiar(const Cola& c);
  void resize(const int n);
};

#include "Cola.tpp"
#endif // __COLA_H__
