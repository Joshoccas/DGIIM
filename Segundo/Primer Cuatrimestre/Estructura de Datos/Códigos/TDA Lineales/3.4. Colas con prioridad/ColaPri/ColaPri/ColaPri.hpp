#ifndef __COLA_PRI__
#define __COLA_PRI__

#include <string>
using namespace std;
typedef int Tprio;
typedef string Tbase;

struct Pareja{
  Tprio prioridad;
  Tbase elemento;
};

struct CeldaColaPri{
  Pareja dato;
  CeldaColaPri* sig;
};

class ColaPri{
private:
  CeldaColaPri* primera;
public:
  ColaPri();
  ColaPri(const ColaPri& c);
  ~ColaPri();
  ColaPri& operator=(const ColaPri& c);
  
  bool vacia() const;
  Tbase frente() const;
  Tprio prioridad_frente() const;
  void poner(Tbase e, Tprio prio);
  void quitar();
};

#endif /* ColaPri_hpp */
