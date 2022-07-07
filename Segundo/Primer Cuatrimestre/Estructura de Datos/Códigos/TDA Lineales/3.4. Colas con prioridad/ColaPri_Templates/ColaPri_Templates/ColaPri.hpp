#ifndef __COLA_PRI__
#define __COLA_PRI__

#include <string>
using namespace std;

template <class T>
struct CeldaColaPri{
  T dato;
  CeldaColaPri* sig;
};

template <class T>
class ColaPri{
private:
  CeldaColaPri<T>* primera;
public:
  ColaPri();
  ColaPri(const ColaPri<T>& c);
  ~ColaPri();
  ColaPri& operator=(const ColaPri<T>& c);
  
  bool vacia() const;
  T frente() const;
  void poner(T e);
  void quitar();
};

#include "ColaPri.cpp"
#endif /* ColaPri_hpp */
