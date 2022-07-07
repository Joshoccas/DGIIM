#ifndef __COLA_H__
#define __COLA_H__

typedef char Tbase;

class Cola{
private:
  Tbase * datos;
  int reservados;
  int nelem;
  int anterior, posterior;
public:
  Cola();
  Cola(const Cola& c);
  ~Cola();
  Cola& operator=(const Cola & c);
  bool vacia() const;
  void poner(const Tbase & valor);
  void quitar();
  Tbase frente() const;
private:
  void reservar(const int n);
  void liberar();
  void copiar(const Cola& c);
  void redimensionar(const int n);
};

#endif // __COLA_H__


