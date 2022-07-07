#ifndef __LISTA_H__
#define __LISTA_H__

#include <stdio.h>

typedef char Tbase;

class Lista;

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
  friend class Lista;
};

class Lista{
private:
  Tbase* datos;
  int nelementos;
  int reservados;
public:
  Lista();
  Lista(const Lista& l);
  ~Lista();
  Lista& operator=(const Lista& l);
  Tbase get(const Posicion & p) const;
  void set(const Posicion & p, const Tbase & e);
  Posicion insertar(const Posicion & p, const Tbase & e);
  Posicion borrar(const Posicion & p);
  Posicion begin() const;
  Posicion end() const;
private:
  void liberar();
  void redimensionar(int n);
  void copiar(const Lista& l);
  void reservar(int n);
};

#endif // __LISTA_H__

