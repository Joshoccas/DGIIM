#ifndef __PILA_H__
#define __PILA_H__

typedef char Tbase;
const int TAM =10;

class Pila{
private:
  Tbase *datos;
  int reservados;
  int nelem;
public:
  Pila(int tam=TAM);
  Pila(const Pila & p);
  ~Pila();
  Pila & operator=(const Pila &p);
  bool vacia() const;
  void poner(Tbase c);
  void operator+=(const Tbase &c);
  void quitar();
  void operator--();
  void operator--(int);
  Tbase & tope();
  const Tbase & tope() const;
private:
  void resize(int n);
  void copiar(const Pila& p);
  void liberar();
  void reservar(int n);
};

#endif /* Pila_hpp */
