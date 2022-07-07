#ifndef ArbolBinario_hpp
#define ArbolBinario_hpp

#include <iostream>
#include <cassert>
using namespace std;

template <class Tbase>
class ArbolBinario {
private:
  struct nodo{
    Tbase etiqueta;
    struct nodo* izqda;
    struct nodo* drcha;
    struct nodo* padre;
  };
  struct nodo* laraiz;
public:
  /**
   @brief Tipo Nodo
   
   Este tipo nos permite manipular los nodos de un árbol. Los valores que
   puede tomar son cada uno de los nodos del árbol (para permitir referirse a
   cada uno de ellos) y un valor especial, nodonulo, que indica que no hace
   referencia a ninguno de los nodos del árbol
   Una variable de este tipo se declara:

   ArbolBinario::Nodo n;
   
   Operaciones válidas sobre este tipo:
   
   -Operador de asignación (=)
   
   -Operador de comparación de igualdad (==)
   
   -Operador de comparación de desigualdad (!=)
   */
  typedef struct nodo* Nodo;
  /**
   @brief Nodo nulo
   
   El valor del nodo nulo se puede indicar como
   */
  static const Nodo nodonulo;
  
  /**
   @brief Constructor por defecto
   
   Reserva los recursos necesarios e inicializa el árbol como un árbol
   vacío. O(1)
   */
  ArbolBinario();
  /**
   @brief Constructor de raíz
   @param e etiqueta de la raíz del nuevo árbol
   
   Reserva los recursos necesarios e inicializa el árbol con un único
   nodo raíz que tiene etiqueta e. O(1)
   */
  ArbolBinario(const Tbase & e);
  /**
   @brief Constructor de copia
   @param t árbol a copiar
   
   Reserva los recursos necesarios e inicializa el árbol duplicando el
   contenido de t. O(n), con n el número de nodos de t
   */
  ArbolBinario(const ArbolBinario<Tbase> & t);
  /**
   @brief Destructor
   
   Libera los recursos del árbol. O(n), con n el número de nodos del árbol
   */
  ~ArbolBinario();
  /**
   @brief Operador de asignación
   @param t árbol a copiar
   
   Asigna el valor del árbol duplicando el contenido de t en el árbol
   original. O(n), con n el número de nodos de t
   */
  ArbolBinario<Tbase> & operator=(const ArbolBinario<Tbase> & t);
  /**
   @brief Asigna el nodo raíz
   @param e etiqueta de la raíz
   
   Vacía el árbol y le asigna el valor de un árbol con un único nodo con
   etiqueta e. O(n), con n el número de nodos del árbol
   */
  void asigna_raiz(const Tbase & e);
  /**
   @brief Raíz del árbol
   
   Devuelve el nodo raíz, que será nodonulo si el árbol está vacío. O(1)
   */
  Nodo raiz() const;
  /**
   @brief Hijo izquierdo
   @param n nodo del que se quiere obtener el hijo izquierdo. n no es nodonulo
   @return Nodo hijo izquierdo
   
   Devuelve el nodo hijo izquierdo de n, que será nodonulo si n no tiene
   hijo izquierdo. O(1)
   */
  Nodo izquierda(const Nodo n) const;
  /**
   @brief Hijo derecho
   @param n nodo del que se quiere obtener el hijo derecho. n no es nodonulo
   @return Nodo hijo derecho
   
   Devuelve el nodo hijo derecho de n, que será nodonulo si n no tiene
   hijo derecho. O(1)
   */
  Nodo derecha(const Nodo n) const;
  /**
   @brief Nodo padre
   @param n nodo del que se quiere obtener el padre. n no es nodonulo
   @return Nodo padre
   
   Devuelve el nodo padre de n, que será nodonulo si n es la raíz del
   árbol. O(1)
   */
  Nodo padre(const Nodo n) const;
  /**
   @brief Etiqueta de un nodo
   @param n nodo del que se quiere obtener la etiqueta. n no es nodonulo
   @return Referencia a la etiqueta del nodo
   
   Devuelve una referencia a la etiqueta del nodo n. Al devolverse una
   referencia, podemos consultar o modificar su valor. O(1)
   */
  Tbase & etiqueta(const Nodo n);
  /**
   @brief Etiqueta de un nodo
   @param n nodo del que se quiere obtener la etiqueta. n no es nodonulo
   @return Referencia constante a la etiqueta del nodo
   
   Devuelve una referencia constante a la etiqueta del nodo n. Al devolverse una
   referencia constante, sólo podemos consultar su valor, no modificarlo. O(1)
   */
  const Tbase & etiqueta(const Nodo n) const;
  /**
   @brief Copia un subárbol
   @param orig árbol desde el que se realiza la copia de una rama
   @param n nodo raíz del subárbol a copiar. Es un nodo de orig y no es
   nodonulo
   
   El árbol receptor acaba siendo una copia de la rama de orig que cuelga
   de n. O(n), con n el número de nodos de la rama
   */
  void asignar_subarbol(const ArbolBinario<Tbase> & orig, const Nodo n);
  /**
   @brief Poda el subárbol izquierdo
   @param n nodo al que se podará su hijo izquierdo. No es nodonulo
   @param dest árbol que recibe la rama cortada
   
   Asigna un nuevo valor al árbol dest, de forma que contendrá los nodos
   del subárbol izquierdo del nodo n. El árbol sobre el que se opera pierde
   esa rama. O(n), con n el número de nodos de dest (ya que tenemos que
   destruir su contenido)
   */
  void podar_izquierda(Nodo n, ArbolBinario<Tbase> & dest);
  /**
   @brief Poda el subárbol derecho
   @param n nodo al que se podará su hijo derecho. No es nodonulo
   @param dest árbol que recibe la rama cortada
   
   Asigna un nuevo valor al árbol dest, de forma que contendrá los nodos
   del subárbol derecho del nodo n. El árbol sobre el que se opera pierde
   esa rama. O(n), con n el número de nodos de dest (ya que tenemos que
   destruir su contenido)
   */
  void podar_derecha(Nodo n, ArbolBinario<Tbase> & dest);
  /**
   @brief Inserta subárbol izquierdo
   @param n nodo al que se insertará la rama como hijo izquierdo. No es nodonulo
   @param rama árbol que se insertará como hijo izquierdo
   
   El árbol rama se inserta como hijo izquiedo de n. El árbol rama queda
   vacío y los nodos que colgaban como descendientes a la izquierda de n
   también se eliminan
   */
  void insertar_izquierda(Nodo n, ArbolBinario<Tbase> & rama);
  /**
   @brief Inserta subárbol derecho
   @param n nodo al que se insertará la rama como hijo derecho. No es nodonulo
   @param rama árbol que se insertará como hijo derecho
   
   El árbol rama se inserta como hijo derecho de n. El árbol rama queda
   vacío y los nodos que colgaban como descendientes a la derecha de n
   también se eliminan
   */
  void insertar_derecha(Nodo n, ArbolBinario<Tbase> & rama);
  /**
   @brief Borra todos los nodos
   
   Borra todos los elementos del árbol. Deja el árbol vacío. O(n), con n
   el número de nodos del árbol
   */
  void clear();
  /**
   @brief Número de nodos
   @return Número de elementos del árbol
   
   O(n), con n el número de nodos del árbol. @see ArbolBinario<Tbase>::contar()
   */
  int size() const;
  /**
   @brief Comprueba si es el árbol vacío
   @return devuelve true si el árbol no tiene nodos y false en caso contrario
   
   O(1)
   */
  bool vacio() const;
  /**
   @brief Operador de comparación de igualdad
   @param t árbol con el que se compara
   @return Devuelve true si los dos árboles tienen los mismos elementos y en
   la misma disposición, false en caso contrario
   
   O(n) con n, el número de nodos del árbol
   */
  bool operator==(const ArbolBinario<Tbase>& t) const;
  /**
   @brief Operador de comparación de desigualdad
   @param t árbol con el que se compara
   @return Devuelve false si los dos árboles tienen los mismos elementos y en
   la misma disposición, true en caso contrario
   
   O(n) con n, el número de nodos del árbol
   */
  bool operator!=(const ArbolBinario<Tbase>& t) const;
  /**
   @brief Operador de entrada
   @param flujo stream desde el que se lee
   @param t árbol en el que leer
   @return Devuelve una referencia al flujo para permitir el encadenamiento
   del operador
   
   Lee un árbol de flujo y lo almacena en t. El formato de entrada se
   puede consultar en la función de salida. @see ArbolBinario<Tbase>::operator<<
   */
  template <class T>
  friend istream& operator>>(istream& flujo, ArbolBinario<T> & t);
  /**
   @brief Operador de salida
   @param flujo stream en el que se escribe
   @param t árbol que escribir
   @return Devuelve una referencia al flujo para permitir el encadenamiento
   del operador
   
   Escribe un árbol en flujo siguiendo un recorrido en preorden. Si un
   nodo es nulo se escribe "x". Si el nodo no es nulo se escribe "n" seguido
   de un espacio en blanco y la etiqueta del nodo.
   @see ArbolBinario<Tbase>::escribe_arbol
   */
  template <class T>
  friend ostream& operator<<(ostream& flujo, ArbolBinario<T> & t);
  
  void Esquema(const Nodo n, string pre);

private:
  /**
   @brief Destruye el subárbol
   @param n nodo a destruir, junto con sus descendientes
   
   Libera los recursos que ocupan n y sus descendientes
   */
  void destruir(Nodo n);
  /**
   @brief Copia un subárbol
   @param dest referencia al nodo del que se cuelga la copia
   @param orig puntero a la raíz del subárbol a copiar
   
   Hace una copia del subárbol que cuelga de orig en el puntero dest
   */
  void copiar(Nodo& dest, Nodo orig);
  /**
   @brief Cuenta el número de nodos
   @param n nodo del que cuelga el subárbol que se desea contabilizar
   
   Cuenta cuántos nodos cuelgan de n, incluido el propio n
   */
  int contar(Nodo n);
  /**
   @brief Comprueba la igualdad de dos subárboles
   @param n1 nodo del que cuelga el primer subárbol a comparar
   @param n2 nodo del que cuelga el primer subárbol a comparar
   
   Comprueba si son iguales los subárboles que cuelgan de n1 y n2.
   Deberán tener los mismos nodos en las mismas posiciones y con las mismas
   etiquetas
   */
  bool son_iguales(Nodo n1, Nodo n2);
  /**
   @brief Escribe un subárbol
   @param flujo stream de salida en el que escribir
   @param n nodo del que cuelga el subárbol a escribir
   
   Escribe los nodos del subárbol en el flujo de salida siguiendo un
   recorrido en preorden. Si un nodo es nulo se escribe "x". Si el nodo no
   es nulo se escribe "n" seguido de un espacio en blanco y la etiqueta del nodo
   */
  void escribe_arbol(ostream& flujo, Nodo n) const;
  /**
   @brief Lee un subárbol
   @param flujo stream de entrada desde el que leer
   @param n referencia al nodo que contendrá el subárbol leído
   
   Lee de la entrada el contenido de un árbol en el formato descrito en
   la función de escritura. @see ArbolBinario<Tbase>::escribe_arbol
   */
  void lee_arbol(istream& flujo, Nodo& n);
};

/////////////////////////////////////
/////////////////////////////////////
//   IMPLEMENTACIÓN
/////////////////////////////////////
/////////////////////////////////////

//FUNCIONES PRIVADAS

template <class Tbase>
void ArbolBinario<Tbase>::destruir(Nodo n){
  if (n!=0){
    destruir(n->izqda);
    destruir(n->drcha);
    delete n;
  }
}

template <class Tbase>
int ArbolBinario<Tbase>::contar(Nodo n){
  if (n==0)
    return 0;
  else return 1+ contar(n->izqda) + contar(n->drcha);
}

template <class Tbase>
void ArbolBinario<Tbase>::copiar(Nodo &dest, Nodo orig){
  if (orig==0)
    dest = 0;
  else{
    dest = new nodo;
    dest->etiqueta = orig->etiqueta;
    copiar(dest->izqda, orig->izqda);
    copiar(dest->drcha, orig->drcha);
    if (dest->izqda!=0)
      dest->izqda->padre = dest;
    if (dest->drcha!=0)
      dest->drcha->padre = dest;
  }
}

template <class Tbase>
bool ArbolBinario<Tbase>::son_iguales(Nodo n1, Nodo n2){
  if(n1==0 && n2==0)
    return true;
  if(n1==0 || n2==0)
    return false;
  if(n1->etiqueta != n2->etiqueta)
    return false;
  if(!son_iguales(n1->izqda,n2->izqda))
    return false;
  if(!son_iguales(n1->drcha, n2->drcha))
    return false;
  return true;
}

template <class Tbase>
void ArbolBinario<Tbase>::escribe_arbol(ostream& flujo, Nodo n) const{
  if(n==0)
    flujo << "x ";
  else{
    flujo << "n " << n->etiqueta << " ";
    escribe_arbol(flujo, n->izqda);
    escribe_arbol(flujo, n->drcha);
  }
}

template <class Tbase>
void ArbolBinario<Tbase>::lee_arbol(istream &flujo, Nodo &n){
  char c;
  flujo >> c;
  if (c=='n'){
    n = new nodo;
    flujo >> n->etiqueta;
    lee_arbol(flujo, n->izqda);
    lee_arbol(flujo, n->drcha);
    if(n->izqda!=0)
      n->izqda->padre = n;
    if(n->drcha!=0)
      n->drcha->padre = n;
  }
  else n = 0;
}

//FUNCIONES PÚBLICAS

template <class Tbase>
ArbolBinario<Tbase>::ArbolBinario(){
  laraiz = 0;
}

template <class Tbase>
ArbolBinario<Tbase>::ArbolBinario(const Tbase & e){
  laraiz = new nodo;
  laraiz->etiqueta = e;
  laraiz->padre =
  laraiz->izqda =
  laraiz->drcha = 0;
}

template <class Tbase>
ArbolBinario<Tbase>::ArbolBinario(const ArbolBinario<Tbase>& t){
  copiar(laraiz,t.laraiz);
  if (laraiz!=0)
    laraiz->padre = 0;
}

template <class Tbase>
ArbolBinario<Tbase>::~ArbolBinario(){
  destruir(laraiz);
}

template <class Tbase>
ArbolBinario<Tbase>& ArbolBinario<Tbase>::operator=(const ArbolBinario<Tbase>& t){
  if(this!=&t){
    destruir(laraiz);
    copiar(laraiz,t.laraiz);
    if(laraiz!=0)
      laraiz->padre = 0;
  }
  return *this;
}

template <class Tbase>
void ArbolBinario<Tbase>::asigna_raiz(const Tbase &e){
  destruir(laraiz);
  laraiz = new nodo;
  laraiz->padre =
  laraiz->drcha =
  laraiz->izqda = 0;
  laraiz->etiqueta = e;
}

template <class Tbase>
typename ArbolBinario<Tbase>::Nodo ArbolBinario<Tbase>::raiz() const{
  return laraiz;
}

template <class Tbase>
typename ArbolBinario<Tbase>::Nodo ArbolBinario<Tbase>::izquierda(const Nodo n) const{
  assert(n!=0);
  return n->izqda;
}

template <class Tbase>
typename ArbolBinario<Tbase>::Nodo ArbolBinario<Tbase>::derecha(const Nodo n) const{
  assert(n!=0);
  return n->drcha;
}

template <class Tbase>
typename ArbolBinario<Tbase>::Nodo ArbolBinario<Tbase>::padre(const Nodo n) const{
  assert(n!=0);
  return n->padre;
}

template <class Tbase>
Tbase& ArbolBinario<Tbase>::etiqueta(const Nodo n) {
  assert(n!=0);
  return n->etiqueta;
}

template <class Tbase>
const Tbase& ArbolBinario<Tbase>::etiqueta(const Nodo n) const{
  assert(n!=0);
  return n->etiqueta;
}

template <class Tbase>
void ArbolBinario<Tbase>::asignar_subarbol(const ArbolBinario<Tbase> &orig, const Nodo n){
  destruir(laraiz);
  copiar(laraiz, n);
  if(laraiz!=0)
    laraiz->padre = 0;
}

template <class Tbase>
void ArbolBinario<Tbase>::podar_izquierda(Nodo n, ArbolBinario<Tbase> &dest){
  assert(n!=0);
  destruir(dest.laraiz);
  dest.laraiz = n->izqda;
  if (dest.laraiz !=0){
    dest.laraiz->padre = 0;
    n->izqda = 0;
  }
}

template <class Tbase>
void ArbolBinario<Tbase>::podar_derecha(Nodo n, ArbolBinario<Tbase> &dest){
  assert(n!=0);
  destruir(dest.laraiz);
  dest.laraiz = n->drcha;
  if (dest.laraiz !=0){
    dest.laraiz->padre = 0;
    n->drcha = 0;
  }
}

template <class Tbase>
void ArbolBinario<Tbase>::insertar_izquierda(Nodo n, ArbolBinario<Tbase> &rama){
  assert(n!=0);
  destruir(n->izqda);
  n->izqda = rama.laraiz;
  if(n->izqda!=0){
    n->izqda->padre = n;
    rama.laraiz = 0;
  }
}

template <class Tbase>
void ArbolBinario<Tbase>::insertar_derecha(Nodo n, ArbolBinario<Tbase> &rama){
  assert(n!=0);
  destruir(n->drcha);
  n->drcha = rama.laraiz;
  if(n->drcha!=0){
    n->drcha->padre = n;
    rama.laraiz = 0;
  }
}

template <class Tbase>
void ArbolBinario<Tbase>::clear(){
  destruir(laraiz);
  laraiz = 0;
}

template <class Tbase>
int ArbolBinario<Tbase>::size() const{
  return contar(laraiz);
}

template <class Tbase>
bool ArbolBinario<Tbase>::vacio() const{
  return laraiz==0;
}

template <class Tbase>
bool ArbolBinario<Tbase>::operator==(const ArbolBinario<Tbase> &t) const{
  return son_iguales(laraiz, t.laraiz);
}

template <class Tbase>
bool ArbolBinario<Tbase>::operator!=(const ArbolBinario<Tbase> &t) const{
  return !(*this==t);
}

template <class Tbase>
istream & operator>>(istream& flujo, ArbolBinario<Tbase>& t){
  t.clear(); //mio
  t.lee_arbol(flujo, t.laraiz);
  return flujo;
}

template <class Tbase>
ostream& operator<<(ostream& flujo, const ArbolBinario<Tbase>& t){
  t.escribe_arbol(flujo, t.laraiz);
  return flujo;
}

template <class Tbase>
void ArbolBinario<Tbase>::Esquema(const Nodo n, string pre){
  if (n==0)
    cout << pre << "-- x" << endl;
  else {
    cout << pre << "-- " << etiqueta(n) << endl;
    if (derecha(n)!=0 || izquierda(n)!=0) {// Si no es una hoja
      pre += "   |";
      Esquema(derecha(n), pre);
      pre.replace(pre.size()-4, 4, "    ");
      Esquema (izquierda(n), pre);
      pre.erase(pre.size()-4, 4);
    }
  }
}

template <class Tbase>
const typename ArbolBinario<Tbase>::Nodo ArbolBinario<Tbase>::nodonulo = 0;


#endif /* ArbolBinario_hpp */
