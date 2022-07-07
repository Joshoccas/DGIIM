#ifndef __LISTA_H__
#define __LISTA_H__

template <class T>
struct CeldaLista{
  T elemento;
  CeldaLista<T>* anterior;
  CeldaLista<T>* siguiente;
};

template <class T>
class Lista{
private:
  CeldaLista<T>* cabecera;
public:
  
  //Clase iterador
  class iterator{
  private:
    CeldaLista<T> * puntero;
  public:
    iterator();
    iterator(const iterator & otro);
    bool operator !=(const iterator & otro) const;
    bool operator ==(const iterator & otro) const;
    iterator& operator=(const iterator & otro);
    T & operator*();
    iterator operator++();
    iterator operator++(int);
    iterator operator--();
    iterator operator--(int);
    friend class Lista;
  };

  //Clase const_iterador
  class const_iterator{
  private:
    CeldaLista<T> * puntero;
  public:
    const_iterator();
    const_iterator(const const_iterator & otro);
    bool operator !=(const const_iterator & otro) const;
    bool operator ==(const const_iterator & otro) const;
    const_iterator& operator=(const const_iterator & otro);
    const T & operator*() const;
    const_iterator operator++();
    const_iterator operator++(int);
    const_iterator operator--();
    const_iterator operator--(int);
    friend class Lista;
  };

  //Fin clase iterador
  
  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  Lista();
  Lista(const Lista& l);
  ~Lista();
  Lista& operator=(const Lista& l);
  void set(iterator it, T e);
  T get(iterator it) const;
  iterator insertar(iterator it, const T &e);
  iterator borrar(iterator it);
  //Otros métodos de la STL
  Lista(iterator inicio, iterator final);
  bool empty();
  void clear();
  int size() const;
  void remove(const T &valor);
  void reverse();
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
