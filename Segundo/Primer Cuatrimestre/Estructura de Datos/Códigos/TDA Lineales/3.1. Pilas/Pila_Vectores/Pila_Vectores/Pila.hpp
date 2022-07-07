#ifndef __PILA_H__
#define __PILA_H__

typedef char Tbase;
const int TAM =500;

class Pila{
private:
  Tbase datos[TAM];
  int nelem;
public:
  Pila();
  Pila(const Pila & p);
  ~Pila() = default;
  Pila & operator=(const Pila &p);
  bool vacia() const;
  void poner(const Tbase & c);
//  Pila & operator += (const Tbase & c);
  void operator+=(const Tbase & c);
  void quitar();
  void operator--();
  void operator--(int);
  Tbase & tope();
  const Tbase & tope() const;
private:
  //Método auxiliar privado
  void copiar(const Pila &p);
};

#endif /* Pila_hpp */
