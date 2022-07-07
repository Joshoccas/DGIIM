#ifndef __COLA_PRI__
#define __COLA_PRI__

#include <string>
#include "APO.hpp"
using namespace std;


template <class T>
class ColaPri{
private:
  APO<T> apo;
public:
  ColaPri() = default;
  ColaPri(const ColaPri<T>& c) = default;
  ~ColaPri() = default;
  ColaPri& operator=(const ColaPri<T>& c) = default;
  
  bool vacia() const;
  T frente() const;
  void poner(T e);
  void quitar();
};

#include "ColaPri.cpp"
#endif /* ColaPri_hpp */
