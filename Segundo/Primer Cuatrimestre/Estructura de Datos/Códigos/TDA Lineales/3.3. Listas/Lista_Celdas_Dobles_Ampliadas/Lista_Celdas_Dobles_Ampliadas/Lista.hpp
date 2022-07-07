#ifndef __LISTA_H__
#define __LISTA_H__

typedef char Tbase;

struct CeldaLista{
  Tbase elemento;
  CeldaLista* anterior;
  CeldaLista* siguiente;
};

class Lista;

class Posicion{
private:
  CeldaLista* puntero;
public:
  Posicion();
  //Posicion(const Posicion& p);
  //~Posicion();
  //Posicion& operator=(const Posicion& p);
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
public:
  Lista();
  Lista(const Lista& l);
  ~Lista();
  Lista& operator=(const Lista& l);
  void set(Posicion p, Tbase e);
  Tbase get(Posicion p) const;
  Posicion insertar(Posicion p, Tbase e);
  Posicion borrar(Posicion p);
  Posicion begin() const;
  Posicion end() const;
  //Otros métodos de la STL
  Lista(const Posicion inicio, const Posicion final);
  void clear();
  int size();
  void push_front(const Tbase & dato);
  void push_back(const Tbase & dato);
  void pop_front();
  void pop_back();
  Tbase & front();
  const Tbase & front() const;
  Tbase & back();
  const Tbase & back() const;
  void swap(Lista & l);
};
#endif //__LISTA_H__
