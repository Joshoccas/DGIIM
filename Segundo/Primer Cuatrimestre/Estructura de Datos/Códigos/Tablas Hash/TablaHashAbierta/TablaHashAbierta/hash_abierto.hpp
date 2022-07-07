#ifndef hash_abierto_hpp
#define hash_abierto_hpp

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class CeldaLista{
private:
  int clave;
  int ptr;
public:
  CeldaLista();
  CeldaLista(int c, int p);
  int & Clave();
  int & Valor();
};

CeldaLista:: CeldaLista() : clave(-1),ptr(-1){
}

CeldaLista:: CeldaLista(int c, int p): clave(c),ptr(p){
}

int & CeldaLista:: Valor(){
  return ptr;
}

int & CeldaLista:: Clave(){
  return clave;
}


class TablaHash{
private:
  vector<list<CeldaLista>> tabla;
  int fhash(int clave);
  list<CeldaLista>::iterator EstaEnFila(int clave, int fila);
public:
  TablaHash(int tam);
  bool Existe(int clave);
  bool Insertar(int clave, int ptrdatos);
  bool Borrar(int clave);
  bool Cambiar(int clave, int ptrdatos);
  int Obtener(int clave);
  void imprimir();
};


TablaHash::TablaHash(int tam){
  assert(tam>0);
  tabla.resize(tam);
}

int TablaHash::fhash(int clave){
  return clave%tabla.size();
}

list<CeldaLista>::iterator TablaHash::EstaEnFila(int clave, int fila){
  list<CeldaLista>::iterator it;
  for(it=tabla[fila].begin(); it!=tabla[fila].end(); it++)
    if(it->Clave() == clave)
      return it;
  return it; //Si no lo encuentra devuelve end()
}

bool TablaHash::Existe(int clave){
  int fila = fhash(clave);
  return (EstaEnFila(clave, fila) != tabla[fila].end());
}

bool TablaHash::Insertar(int clave, int ptrdatos){
  bool exito = false;
  int fila = fhash(clave);
  if (EstaEnFila(clave, fila) == tabla[fila].end()){
    tabla[fila].push_back(CeldaLista(clave,ptrdatos));
    exito = true;
  }
  return exito;
}

bool TablaHash::Cambiar(int clave, int ptrdatos){
  bool exito = false;
  int fila = fhash(clave);
  list<CeldaLista>::iterator donde = EstaEnFila(clave, fila);
  
  if (donde != tabla[fila].end()){
    donde->Valor() = ptrdatos;
    exito = true;
  }
  return exito;
}

int TablaHash::Obtener(int clave){
  int fila = fhash(clave);
  list<CeldaLista>::iterator donde = EstaEnFila(clave, fila);
  
  return(donde!=tabla[fila].end() ? donde->Valor(): -1);
}

bool TablaHash::Borrar(int clave){
  bool exito = false;
  int fila = fhash(clave);
  list<CeldaLista>::iterator donde = EstaEnFila(clave, fila);
  
  if (donde!=tabla[fila].end()){
    tabla[fila].erase(donde);
    exito = true;
  }
  return exito;
}

void TablaHash::imprimir(){
  list<CeldaLista>::iterator it;
  for(int i=0; i<tabla.size(); i++){
    cout << "Fila " << i << ": ";
    for(it=tabla[i].begin(); it!=tabla[i].end(); it++)
      cout << "(" << it->Clave() << "." << it->Valor() << ")";
    cout << endl;
  }
}




#endif /* hash_abierto_hpp */
