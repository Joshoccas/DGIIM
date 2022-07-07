#include <iostream>
#include "grafo.h"

template <typename Tn, typename Ta>
void DFS(grafo<Tn,Ta> g, int n){
  vector<bool> visitados(g.size(), false);
  stack<int> pila;
  pila.push(g.buscarNodo(n)->etiqueta());
  
}

int main(int argc, const char * argv[]) {
  grafo<int, int> g;
  
  for(int i=1; i<=8; i++)
    g.insertarNodo(i);
  
  g.insertarArco(g.buscarNodo(1),g.buscarNodo(2),0);
  g.insertarArco(g.buscarNodo(1),g.buscarNodo(4),0);
  g.insertarArco(g.buscarNodo(4),g.buscarNodo(3),0);
  g.insertarArco(g.buscarNodo(3),g.buscarNodo(5),0);
  g.insertarArco(g.buscarNodo(3),g.buscarNodo(6),0);
  g.insertarArco(g.buscarNodo(5),g.buscarNodo(6),0);
  g.insertarArco(g.buscarNodo(5),g.buscarNodo(7),0);
  g.insertarArco(g.buscarNodo(7),g.buscarNodo(6),0);
  g.insertarArco(g.buscarNodo(7),g.buscarNodo(8),0);
  g.insertarArco(g.buscarNodo(8),g.buscarNodo(6),0);

  DFS(g,1);
  
  return 0;
}

