#ifndef APO_hpp
#define APO_hpp

/**
 @brief TDA APO
 
 Definición:
 
 Una instancia, a, del TDA APO sobre un dominio Tbase es un árbol binario conb
 etiquetas en Tbase y un orden parcial que consiste en que la etiqueta de un
 nodo es menor o igual que la de sus descendientes. Para poder gestionarlo,
 el tipo Tbase debe tener definida la operación <
 */

template <class Tbase>
class APO{
private:
  Tbase* vec;
  int nelementos;
  int reservados;
public:
  APO();
  APO(int tam);
  APO(const APO<Tbase>& a);
  ~APO();
  APO<Tbase>& operator=(const APO<Tbase>& a);
  const Tbase& raiz() const;
  void borrar_raiz();
  void insertar(const Tbase& e);
  void clear();
  int size() const;
  bool empty() const;
private:
  void reservar(int tam);
  void liberar();
  void copiar(const APO<Tbase>& otro);
  void expandir(int nelem);
};

#include "APO.cpp"
#endif /* APO_hpp */
