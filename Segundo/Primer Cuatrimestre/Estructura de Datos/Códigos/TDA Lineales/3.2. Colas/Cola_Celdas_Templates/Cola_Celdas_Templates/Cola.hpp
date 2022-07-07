#ifndef __COLA_H__
#define __COLA_H__

template <class T>
struct CeldaCola{
  T elemento;
  CeldaCola* sig;
};

template <class T>
class Cola{
private:
  CeldaCola<T>* primera, *ultima;
public:
  Cola();
  Cola(const Cola& c);
  ~Cola();
  Cola& operator=(const Cola& c);
  bool vacia() const;
  void poner(const T & c);
  void quitar();
  T frente() const;
private:
  void copiar(const Cola& c);
  void liberar();
};

#endif // __COLA_H__
