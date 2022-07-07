#ifndef __LISTA_H__
#define __LISTA_H__

typedef char Tbase;

struct CeldaLista{
  Tbase elemento;
  CeldaLista* siguiente;
};

class Lista;

class Posicion{
private:
  CeldaLista* puntero;
  CeldaLista* primera;
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
  CeldaLista* cabecera;
  CeldaLista* ultima;
public:
  Lista();
  Lista(const Lista& l);
  ~Lista();
  Lista& operator=(const Lista& l);
  
  Tbase get(Posicion p) const;
  void set(Posicion p, Tbase e);
  Posicion insertar(Posicion p, Tbase e);
  Posicion borrar(Posicion p);
  Posicion begin() const;
  Posicion end() const;
};


#endif // __LISTA_H__
