#include<iostream>
#include "grafo.h"

using namespace std;

template<class Tn,class Ta>
void Presentar_Grafo(grafo<Tn,Ta> & G);

/* Ejercicio 1 */

void  Ejemplo_Flujo(grafo <char,int>&G){
  //grafo<char,int> G;
 

  G.insertarNodo('s');
  G.insertarNodo('a');
  G.insertarNodo('b');
  G.insertarNodo('c');
  G.insertarNodo('d');
  G.insertarNodo('t');			 

  G.insertarArco(G.buscarNodo(0),G.buscarNodo(1),3);        
  G.insertarArco(G.buscarNodo(0),G.buscarNodo(2),2);

  G.insertarArco(G.buscarNodo(1),G.buscarNodo(2),1);
  G.insertarArco(G.buscarNodo(1),G.buscarNodo(3),3);
  G.insertarArco(G.buscarNodo(1),G.buscarNodo(4),4);

  G.insertarArco(G.buscarNodo(2),G.buscarNodo(4),2);

  G.insertarArco(G.buscarNodo(3),G.buscarNodo(5),2);

  G.insertarArco(G.buscarNodo(4),G.buscarNodo(5),3);

  
}

template<class Tn,class Ta>
grafo<Tn,Ta> Ejemplo_FlujoTemplate( Tn x1, Ta x2){
  grafo<Tn,Ta> G;
 

  G.insertarNodo('s');
  G.insertarNodo('a');
  G.insertarNodo('b');
  G.insertarNodo('c');
  G.insertarNodo('d');
  G.insertarNodo('t');			 


  G.insertarArco(G.buscarNodo('s'),G.buscarNodo('a'),3);        
  G.insertarArco(G.buscarNodo('s'),G.buscarNodo('b'),2);

  G.insertarArco(G.buscarNodo('a'),G.buscarNodo('b'),1);
  G.insertarArco(G.buscarNodo('a'),G.buscarNodo('c'),3);
  G.insertarArco(G.buscarNodo('a'),G.buscarNodo('d'),4);

  G.insertarArco(G.buscarNodo('b'),G.buscarNodo('d'),2);

  G.insertarArco(G.buscarNodo('c'),G.buscarNodo('t'),2);

  G.insertarArco(G.buscarNodo('d'),G.buscarNodo('t'),3);

  return G;
}

/* Ejercicio 2 */




template<class Tn,class Ta>
void Presentar_Grafo(grafo<Tn,Ta>& G){
  typename grafo<Tn,Ta>::nodoIterator n;
  typename nodo<Tn,Ta>::arcoIterator a;
  
  for (n=G.nbegin(); n!=G.nend() ; ++n){
    cout << n->etiqueta()<<"->\n";
    for (a=n->abegin(); a!=n->aend() ; ++a){
      cout << "   " <<a->nodoDestino()->etiqueta()
           << " : " << a->etiqueta() << endl;
    }
  }
}




/* 5.- */
template <class Tn, class Ta>
void Presentar_Incidentes(nodo<Tn,Ta> * n){
  
  typename nodo<Tn,Ta>::arcoIterator i;

  cout <<"Listado de Incidentes\n";
  for ( i = n->ibegin(); i != n->iend() ; i++ ){
    cout << n->etiqueta();
    cout << i->nodoDestino()->etiqueta();
    cout << i->etqArco() << endl;
  }
}


/* 6.- */
template <class Tn,class Ta>
void Orden_Nodos( grafo<Tn,Ta> &  G){
  grafo<Tn,Ta> aux(G);
  typename grafo<Tn,Ta>::nodoIterator n;
  typename nodo<Tn,Ta>::arcoIterator a;
  bool enc;

  
  cout << "Grafo :" << endl;
 
  do {
    enc=false;
  
    for (n=aux.nbegin(); n!=aux.nend(); ){
      a=n->ibegin();
      if (a == n->iend()) {
	    cout << ".. " << n->etiqueta();
        n=aux.borrarNodo(n);
        enc = true;
      }
      else
        ++n;
    }
  } while (enc);
  
 if (aux.nbegin()!=aux.nend())
   cout <<"\nHay Ciclo\n";
 else
   cout << endl; 
}




/* 7.- */
template <class Tn,class Ta>
bool camino(nodo<Tn,Ta>* org, nodo<Tn,Ta>* dest, 
	       grafo<Tn,Ta> &G, list< arco<Tn,Ta> * > & L){
  
  bool enc=0;
  arco<Tn,Ta> *ar;
  typename nodo<Tn,Ta>::arcoIterator a;

  if ((ar=G.buscarArco(org,dest))) {
    L.push_front(ar);
    return true;
  }
  else{
    for (a = org->abegin(); a!= org->aend() && !enc ; ){
      if (camino( a->nodoDestino(),dest,G,L)){
        enc=true;
        L.push_front(&(*a));
      }
      else
        ++a;
    }
    return enc; 
  }
}



int main(){

  grafo<char,int> a;
  grafo<char,int> b,c,d,e;
  list< arco<char,int> * > L; 
  char x1; int x2;
  int kk;

  Ejemplo_Flujo(b);
  Presentar_Grafo(b);
  
  grafo<char,int> kn(b);
  Presentar_Grafo(kn);
   
  cout << "Orden Nodos para b" << endl;

  Orden_Nodos(b);
  camino(b.buscarNodo('s'),b.buscarNodo('t'),b,L);

  list< arco<char,int> * >::iterator itr;

  cout << "Camino  s ... t"<< endl;
  for (itr = L.begin(); itr!= L.end(); ++itr){
    cout << "("<< (*itr)->nodoOrigen()->etiqueta() << "-";
    cout << (*itr)->nodoDestino()->etiqueta() << ")";
  }
 
  cout << endl;

  b.insertarNodo('x');
  b.insertarNodo('y');
  b.insertarNodo('z');  
  b.insertarArco(b.buscarNodo('x'),b.buscarNodo('z'),12);

  cout << "Recorrido Profundidad "<< endl;

//  grafo<char,int>::profIterator k;
  profundidadIterator<char, int> k;
  nodo<char,int> minodo;
 

  for (k = b.pbegin(); k!=b.pend(); ){
    minodo=*k;
    cout <<"elemento "<< minodo.etiqueta()<< endl;
    ++k;
  }

  b.borrarNodo(b.buscarNodo('d'));
  Presentar_Grafo(b);

  for (k = b.pbegin(); k!=b.pend(); ){
    minodo=*k;
    cout <<"elemento "<< minodo.etiqueta()<< endl;
    ++k;
  }
  
//  grafo<char,int>::nodeIterator n,m;
//  //nodo<char,int> n1,n2;

//  nodo<char,int>::ady_iterator i1;
//  nodo<char,int>::inc_iterator i2;
//  nodo<char,int>*p1, *p2;

//  arco<char,int> e; 
//  a.insertarNodo('a');
//  a.insertarNodo('b');
//  a.insertarNodo('c');
//  a.insertarNodo('d');

//  p1 = a.buscarNodo('a');
//  p2 = a.buscarNodo('b');
  
//  cout << p1->etiqueta() <<endl;
//  a.insertarArco(p1,p2,10);
  


//  p2 = a.buscarNodo('d');
  
//  a.insertarArco(p1,p2,12);
//  for (n= b.nbegin(); n!= b.nend(); n++){
//    cout<< n->etiqueta() << "->";
//    for (i1 = n->abegin(); i1!= n->aend(); i1++){
    
//      cout << i1->etqArco()<< i1->nodoDestino()->etiqueta()<< "+" ;
//    }
//    cout << endl;
//  }

//  if (a.buscarArco(p1,p2))
//    cout << " Existe arco " << a.buscarArco(p1,p2)->etqArco() << "\n";
//  else cout << "No existe arco \n";

//  p2 = a.buscarNodo('c');
//  if (a.buscarArco(p1,p2))
//  cout << " Existe arco " << a.buscarArco(p1,p2)->etqArco() << "\n";
//  else cout << "No existe arco \n";

}



