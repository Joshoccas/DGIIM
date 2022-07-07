#ifndef __PILA_H__
#define __PILA_H__

typedef char Tbase;

struct CeldaPila{
  Tbase elemento;
  CeldaPila * sig;
};

class Pila{
private:
  CeldaPila * primera;
public:
  Pila();
  Pila(const Pila& p);
  ~Pila();
  Pila& operator=(const Pila& p);
  
  bool vacia() const;
  void poner(Tbase c);
  void quitar();
  Tbase tope() const;
  
private:
  void copiar(const Pila& p);
  void liberar();
};

#endif // Pila_hpp
