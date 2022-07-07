#ifndef __LISTA_H__
#define __LISTA_H__

template <typename T> class Lista;

class Posicion{
private:
  int i;
public:
  Posicion();
  Posicion(const Posicion& p) = default;
  ~Posicion() = default;
  Posicion& operator=(const Posicion& p) = default;
  Posicion& operator++();
  Posicion operator++(int);
  Posicion& operator--();
  Posicion operator--(int);
  bool operator==(const Posicion& p) const;
  bool operator!=(const Posicion& p) const;
  template <typename T> friend class Lista;
};

template <typename T>
class Lista{
private:
  T* datos;
  int nelementos;
  int reservados;
public:
  Lista();
  Lista(const Lista& l);
  ~Lista();
  Lista& operator=(const Lista& l);
  T get(const Posicion & p) const;
  void set(const Posicion & p, const T & e);
  Posicion insertar(const Posicion & p, const T & e);
  Posicion borrar(const Posicion & p);
  Posicion begin() const;
  Posicion end() const;
private:
  void liberar();
  void redimensionar(int n);
  void copiar(const Lista& l);
  void reservar(int n);
};



#include "Lista.tpp"
#endif // __LISTA_H__

