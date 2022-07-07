#ifndef GRAFO__H
#define GRAFO__H

#include <list>
#include <vector>
#include <stack>

using namespace std;

template <typename Tn,typename Ta> class arco;
template <typename Tn,typename Ta> class nodo;
template <typename Tn,typename Ta> class profundidadIterator;
template <typename Tn,typename Ta> class grafo;

//////////////////////////
//CLASE ARCO
//////////////////////////

template <typename Tn,typename Ta> class arco {
private:
  nodo<Tn,Ta> * origen;
  nodo<Tn,Ta> * destino;
  Ta valor;

public:

  //Constructor por defecto
  arco():origen(nullptr),destino(nullptr){
  }

  //Constructor de copia
  arco(const arco<Tn,Ta> &a):
    origen(a.origen),
    destino(a.destino),
    valor(a.valor)
  {}
  
  //Constructor con parámetros
  arco( nodo<Tn,Ta> * o, nodo<Tn,Ta> * d, Ta v):
    origen(o),
    destino(d),
    valor(v)
  {}

  //Etiqueta del arco
  Ta & etiqueta( ){
    return valor;
  }
  
  //Operador de asignación
  arco<Tn,Ta>& operator = (const arco<Tn,Ta>&a){
    origen = a.origen;
    destino = a.destino;
    valor = a.valor;
    return *this;
  }
  
  //Nodo destino
  nodo<Tn,Ta> * nodoDestino() const{
    return destino;
  }
  
  //Nodo origen
  nodo<Tn,Ta> * nodoOrigen() const{
    return origen;
  }
};

//////////////////////////
//CLASE NODO
//////////////////////////

template <typename Tn,typename Ta> class nodo {

  friend class grafo<Tn,Ta>;

private:
  int ind; // Codigo interno que permite numerar los nodos de 1 a n
  Tn valor;
  list< arco<Tn,Ta> > ady; //Lista de arcos adyacentes
  list< arco<Tn,Ta> > inc; // Lista de arcos incidentes

public:

  //Constructor por defecto
  nodo(){
  }
  
  //Constructor de copia
  nodo(const nodo<Tn,Ta> &n):
    ind(n.ind),
    valor(n.valor),
    ady(n.ady),
    inc(n.inc)
  {}
  
  //Constructor con parámetros
  nodo(Tn et, int i): valor(et), ind(i){
  }
  
  //Operador de asignación
  nodo & operator=(const nodo<Tn,Ta> &n){
    ind = n.ind;
    valor = n.valor;
    ady = n.ady;
    inc = n.inc;
    return *this;
  }
  
  //Etiqueta
  Tn & etiqueta(){
    return valor;
  }
  
  //Índice (interno)
  int indice(){
    return ind;
  }

  //Añade un nodo a la lista de arcos adyacentes
  void insertarAdy(nodo<Tn,Ta> * destino,Ta valor){
    ady.push_back(arco<Tn,Ta>(this,destino,valor));
  }

  //Añade un nodo a la lista de arcos incidentes
  void insertarInc(nodo<Tn,Ta> * origen,Ta valor){
    inc.push_back(arco<Tn,Ta>(origen,this,valor));
  }

  //Iterador sobre las listas de arcos
  
  typedef typename list< arco<Tn,Ta> >::iterator arcoIterator;

  arcoIterator abegin(){
    return ady.begin();
  }
  
  arcoIterator aend(){
    return ady.end();
  }
 
  arcoIterator ibegin(){
    return inc.begin();
  }
  
  arcoIterator iend(){
    return inc.end();
  }

  arcoIterator borrarAdy(arcoIterator i){
    return ady.erase(i);
  }

  arcoIterator borrarInc(arcoIterator i){
    return inc.erase(i);
  }

};

//////////////////////////
//CLASE GRAFO
//////////////////////////

template <typename Tn, typename Ta> class grafo{

private:
  list<nodo<Tn,Ta> > g;
  int num_nodos;
  
public:
  
  typedef typename list< nodo<Tn,Ta> >::iterator nodoIterator;
  
  //Constructores, destructor y operador de asignación
  grafo();
  grafo(grafo<Tn,Ta> &otro);
  ~grafo();
  grafo<Tn,Ta> & operator=( grafo<Tn,Ta> &otro);

  int size();
  bool empty();
  
  nodoIterator nbegin();
  nodoIterator nend();
  
  //Inserta un nodo con etiqueta etq en un grafo
  //Asociada al nodo encontramos una label (valor entero) que indica el
  //orden en que se ha introducido el nodo en el grafo.
  //Esta etiqueta es importante porque permite referenciar los nodos
  //mediante un valor entero (desde 0 hasta num_nodos-1) en el grafo
  void insertarNodo(Tn etq);

  void insertarArco(nodo<Tn,Ta> *origen, nodo<Tn,Ta> *destino, Ta valor);

  arco<Tn,Ta> * buscarArco( nodo<Tn,Ta> * o, nodo<Tn,Ta> *d);

  nodo<Tn,Ta>* buscarNodo(Tn etq);
  nodo<Tn,Ta>* buscarNodo(int i);

  nodoIterator borrarNodo(nodoIterator it);
  void borrarNodo( nodo<Tn,Ta> * n);

  profundidadIterator<Tn, Ta> pbegin();
  profundidadIterator<Tn, Ta> pend();
 
private:
  
  void copiar(grafo<Tn,Ta> & otro){
    nodoIterator nodo_it;
    typename nodo<Tn,Ta>::arcoIterator arco_it;
    
    num_nodos=0;
    
    for (nodo_it= otro.nbegin(); nodo_it!= otro.nend() ; ++nodo_it)
      this->insertarNodo( nodo_it->etiqueta());
    
    for (nodo_it= otro.nbegin(); nodo_it!= otro.nend() ; ++nodo_it){
      for (arco_it=nodo_it->abegin(); arco_it!=nodo_it->aend() ; ++arco_it){
        nodo<Tn,Ta> * ori=this->buscarNodo(arco_it->nodoOrigen()->etiqueta());
        nodo<Tn,Ta> * des=this->buscarNodo(arco_it->nodoDestino()->etiqueta());
        this->insertarArco(ori,des,arco_it->etiqueta());
      }
    }
  }
  
};
 

/////////////////////////////////
// IMPLEMENTACIÓN DE OPERACIONES
/////////////////////////////////


template<typename Tn, typename Ta>
grafo<Tn,Ta>::grafo(){
  num_nodos = 0;
}


template <typename Tn, typename Ta>
grafo<Tn,Ta>::grafo(grafo<Tn,Ta> &otro){
  num_nodos=0;
  copiar(otro);
}


template <typename Tn, typename Ta>
grafo<Tn,Ta>::~grafo() = default;


template <typename Tn, typename Ta>
grafo<Tn,Ta> & grafo<Tn,Ta>::operator=( grafo<Tn,Ta> &otro){
  if (this != &otro){
    g.clear();
    copiar(otro);
  }
  return *this;
}

template <typename Tn, typename Ta>
int grafo<Tn,Ta>::size(){
  return num_nodos;
}

template <typename Tn, typename Ta>
bool grafo<Tn,Ta>::empty(){
  return num_nodos==0;
}



template <typename Tn, typename Ta>
typename grafo<Tn,Ta>::nodoIterator grafo<Tn,Ta>::nbegin(){
  return g.begin();
}


template <typename Tn, typename Ta>
typename grafo<Tn,Ta>::nodoIterator grafo<Tn,Ta>::nend(){
  return g.end();
}

template <typename Tn, typename Ta>
void grafo<Tn,Ta>::insertarNodo(Tn etq){
  //Creamos un nodo con la etiqueta y el código interno
  //y lo insertamos el nodo en la lista
  g.push_back(nodo<Tn,Ta>(etq,num_nodos));
  //Incrementamos el número de nodos del grafo
  num_nodos++;
}


template <typename Tn, typename Ta>
void grafo<Tn,Ta>::insertarArco(nodo<Tn,Ta> * origen,
                                nodo<Tn,Ta> * destino, Ta valor){
  //Insertamos el nodo destino en la lista de adyacentes de origen
  origen->insertarAdy(destino,valor);
  //Insertamos el nodo origen en la lista de incidentes de destino
  destino->insertarInc(origen,valor);
}


template <typename Tn, typename Ta>
nodo<Tn,Ta> * grafo<Tn,Ta>::buscarNodo(Tn etq){
  //Recorremos los nodos del grafo
  for (nodoIterator it = nbegin(); it != nend();    )
    //Si lo encontramos, devolvemos la dirección del nodo
    if (it->etiqueta()== etq)
	    return &(*it);
	  else
	    it++;
  return 0;
}


template <typename Tn, typename Ta>
nodo<Tn,Ta> * grafo<Tn,Ta>::buscarNodo(int i){
  int k;
  nodoIterator it;
  for (k=0,it=nbegin(); k<i; k++,it++)
    ;
  return &(*it);
}

template<typename Tn, typename Ta>
arco<Tn,Ta> * grafo<Tn,Ta>::buscarArco(nodo<Tn,Ta>* orig, nodo<Tn,Ta>* dest){
  typename nodo<Tn,Ta>::arcoIterator it;
  bool encontrado;

  for(encontrado=false, it=orig->abegin(); it!=orig->aend() && !encontrado;   )
    if (it->nodoDestino()==dest)
	    encontrado = true;
	  else
	    it++;

  return (encontrado ? &(*it) : 0);
}

  
template <typename Tn, typename Ta>
void  grafo<Tn,Ta>::borrarNodo(nodo<Tn,Ta> * n){
  nodoIterator it;
  
  for (it=nbegin(); &(*it)!=n && it!=nend(); ++it)
    ;
  
  if (it!=nend())
    borrarNodo(it);
}

template<typename Tn, typename Ta>
typename grafo<Tn,Ta>::nodoIterator
grafo<Tn,Ta>::borrarNodo(grafo<Tn,Ta>::nodoIterator it){
  typename nodo<Tn,Ta>::arcoIterator arco_it, arco_it2;
  nodo<Tn,Ta> *nodo_actual, *nodo_ady, *nodo_inc;
  typename grafo<Tn,Ta>::nodoIterator s, old;

  //Recorro la lista de arcos adyacentes para borrarla
  for (arco_it=it->abegin(); arco_it!= it->aend();     ){
    nodo_actual = arco_it->nodoOrigen();
    nodo_ady = arco_it->nodoDestino();
    //Buscamos el nodo origen en la lista de destino
    for (arco_it2 = nodo_ady->ibegin(); arco_it2->nodoOrigen()!=nodo_actual;++arco_it2)
      ;
    //Borramos el arco como adyacente y como incidente
    arco_it2 = arco_it2->nodoDestino()->borrarInc(arco_it2);
    arco_it = arco_it->nodoOrigen()->borrarAdy(arco_it);
  }

  //Recorro la lista de arcos incidentes
  for (arco_it = it->ibegin(); arco_it!= it->iend(); ){
    nodo_actual = arco_it->nodoDestino();
    nodo_inc = arco_it->nodoOrigen();
    for (arco_it2 = nodo_inc->abegin(); arco_it2->nodoDestino()!=nodo_actual; ++arco_it2)
      ;
    arco_it2 = arco_it2->nodoOrigen()->borrarAdy(arco_it2);
    arco_it = arco_it->nodoDestino()->borrarInc(arco_it);
  }

  //Ahora puedo borrar el nodo
  num_nodos--;
  old = s = g.erase(it);
  //Actualizamos el índice del resto de nodos
  for (  ; s!= nend(); ++s)
    s->ind--;
  return old;
}


template<typename Tn, typename Ta>
profundidadIterator<Tn, Ta> grafo<Tn,Ta>::pbegin(){
  profundidadIterator<Tn,Ta> k(*this);
  return k;
}

template<typename Tn, typename Ta>
profundidadIterator<Tn,Ta> grafo<Tn,Ta>::pend(){
  profundidadIterator<Tn, Ta> k;
  return k;
}



template <typename Tn,typename Ta>
class profundidadIterator {
  
private:
  nodo<Tn,Ta> * iterador;
  vector < nodo<Tn,Ta>* > porvisitar;
  stack < nodo<Tn,Ta> *> anterior;
public:
  profundidadIterator(){
    iterador = 0;
  }
  
  profundidadIterator(grafo<Tn,Ta>& G){
    typename grafo<Tn,Ta>::nodoIterator it;
    iterador = G.buscarNodo(0);
    porvisitar = vector<nodo<Tn,Ta>*>(G.size());
    for (it=G.nbegin(); it!=G.nend(); ++it)
      porvisitar[it->indice()] = &(*it);
    porvisitar[0] = 0;
    anterior = stack< nodo<Tn,Ta>* >();
    anterior.push(iterador);
  }

  nodo<Tn,Ta>  operator*(){
    return *iterador;
  }

  profundidadIterator operator++(){
    typename nodo<Tn,Ta>::arcoIterator i;
    int ind;
    bool encontrado=false;
    // cout <<"Visitado: ";
    // for (ind=0; ind< (*visitado).size(); ind++)
    //   cout <<"(" << ind << (*visitado)[ind] <<")";
    // cout << endl;
    do {
      for (i=iterador->abegin(); i!= iterador->aend() && !encontrado;   ){
        ind = i->nodoDestino()->indice();
        if (!porvisitar[ind])
          ++i;
        else
          encontrado = true;
      }

      if (encontrado) {
	      iterador = i->nodoDestino();
	      (porvisitar)[ind] = 0;
	      anterior.push(iterador);
      }
      else {
	      iterador = anterior.top();
	      anterior.pop();
      }
    } while (!anterior.empty() && !encontrado);
    		 
   
    if (!encontrado) // Todos los nodos accesibles han sido visitados
    for (ind=0; ind< (porvisitar).size()&&!encontrado; ind++)
      if ((porvisitar)[ind]){
        encontrado = true;
        iterador = (porvisitar)[ind];
        (porvisitar)[ind]=0;
        anterior.push(iterador);
      }
      if (!encontrado){ //Todos los nodos ya han sido visitados
	      iterador = 0;
	    }
    return *this;
    
  }
  
  //postincremento
  profundidadIterator operator++ ( int ){
    profundidadIterator  clon (*this);
    operator ++();
    return clon;
  }

  bool operator==(const profundidadIterator<Tn,Ta> & r){
    return iterador == r.iterador;
  }

  bool operator!=(const profundidadIterator<Tn,Ta> & r){
    return iterador != r.iterador;
  }
     
 
};

#endif
