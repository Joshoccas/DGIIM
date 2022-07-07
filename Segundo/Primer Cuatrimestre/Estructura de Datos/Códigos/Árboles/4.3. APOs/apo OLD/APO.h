/* Fichero: APO.h */

#ifndef __APO_h__
#define __APO_h__

/**
  * @brief T.D.A. APO
  *
  * \b Definición: Una instancia \e a del tipo de dato abstracto \e APO sobre 
  * un dominio \e Tbase es un árbol binario con etiquetas en \e Tbase y un
  * orden parcial que consiste en que la etiqueta de un nodo es menor o igual
  * que la de sus descendientes. Para poder gestionarlo, debe existir la
  * operación \e menor (<) para el tipo \e Tbase.
  * 
  * Para poder usar el TDA APO se debe incluir el fichero
  *
  * <tt>\#include APO.h</tt>
  * 
  * El espacio requerido para el almacenamiento es @e O(n). Donde @e n es el
  * número de nodos del árbol.
  * 
  * @author Antonio Garrido
  * @author Revisado por Javier Abad
  * @date Abril 2008
  *
  */     

template <class Tbase>
class APO {
/**
  * @page repConjunto Rep del TDA APO
  *
  * @section invConjunto Invariante de la representación
  *
  * El invariante para un APO \e a es
  *
  * a.nelementos <= a.Maxelementos
  *
  * \e a.vec apunta a un bloque de memoria reservada de \e a.Maxelementos.
  *
  * \f$\forall\f$ i, j tales que 0 \f$\leq\f$ i < j < a.nelementos y 
  * (j=2*i+1 ó j=2*i+2) se cumple que a.vec[i] \f$\leq\f$ a.vec[j]
  *
  * @section faConjunto Función de abstracción
  *
  * Sea @e T un Árbol Parcialmente Ordenado sobre el tipo @e Tbase. Diremos que
  * el subárbol a partir de la posición \e i es:
  *
  * - Si 0 \f$\leq\f$ i < nelementos, el que tiene como elemento raíz el valor
  * \e T.vec[i] y como subárboles izquierda y derecha, los subárboles a partir
  * de  i*2+1  e  i*2+2. 
  *
  * - En caso contrario, (i \f$\geq\f$ nelementos), el árbol vacío.
  *
  * El árbol \e T del conjunto de valores en la representación se aplica al
  * árbol a partir de la posición 0.
  */

  private:
    /** 
      * @brief Matriz de elementos
      *
      * En el vector \e vec se almacenan los elementos del APO.
      */
    Tbase *vec;
  
    /**
      * @brief Número de elementos
      *
      * Este entero almacena el numero de elementos del APO, es decir, el APO 
      * se almacena en las posiciones desde la 0 a nelementos-1
      */
    int nelementos;
      
    /**
      * @brief Capacidad de almacenamiento
      *
      * En este entero se indica la cantidad de posiciones que hay reservadas
      * en la matriz \e vec, que obviamente tiene que ser mayor o igual a
      * \e nelementos. 
      */
    int Maxelementos;
      
    /**
      * @brief Aumenta la capacidad de almacenamiento
      * @param nelem Nuevo numero de casillas reservadas para la matriz \e vec.
      *
      * Asigna un bloque de memoria para \e nelem elementos para almacenar la 
      * matriz \e vec. Al terminar, \e vec apunta a un bloque con esa 
      * capacidad, conservando el contenido anterior y el miembro
      * \e Maxelementos vale \e nelem. Sin embargo, si \e nelem es menor o 
      * igual que Maxelementos no hace nada.
      */
    void expandir(int nelem);

  public:
    /**
      * @brief Constructor por defecto
      *
      * Reserva los recursos e inicializa el APO a vacío.
      * La operación se realiza en tiempo O(1).
      */
    APO();
      
    /**
      * @brief Constructor con tamaño
      * @param tam Número de elementos que se espera pueda llegar a tener 
      * el árbol.
      *
      * Reserva los recursos e iniciliza el APO a vacío.
      * La operación se realiza en tiempo O(tam).
      */
    APO(int tam);
      
    /**
      * @brief Constructor de copias
      * @param a APO a copiar
      *
      * Construye el APO duplicando el contenido de \e a en el APO receptor. 
      * La operación se realiza en tiempo \e O(n), donde \e n es el número de 
      * elementos de \e a.
      */
    APO (const APO<Tbase>& a);
      
    /**
      * @brief Destructor
      *
      * Libera los recursos ocupados por el APO receptor. La operación se 
      * realiza en tiempo \e O(n) donde \e n es el número de elementos del 
      * APO receptor.
      */
    ~APO();
    
    /**
      * @brief Operador de asignación
      * @param a APO a copiar
      * @return Referencia al APO receptor.
      *
      * Asigna el valor del APO duplicando el contenido de \e a en el APO 
      * receptor. La operación se realiza en tiempo \e O(n), donde \e n es el 
      * número de elementos de \e a.
      */
    APO<Tbase> & operator = (const APO<Tbase> &a);
    
    /**
      * @brief Mínimo elemento almacenado
      * @return Referencia constante al elemento que es mínimo en el APO 
      * receptor.
      * @pre El APO no está vacío
      *
      * Devuelve una referencia al menor de los elementos almacenados en el 
      * APO receptor. La operación se realiza en tiempo \e O(1).
      */
      
    const Tbase & minimo() const;
    
    /**
      * @brief Elimina el mínimo
      * @pre El APO no está vacío
      *
      * Elimina del APO receptor el menor elemento.
      * La operación se realiza en tiempo \e O(log n).
      */
      
    void borrar_minimo();
    
    /**
      * @brief Insertar un elemento
      * @param elem Nuevo elemento a insertar
      *
      * Inserta el elemento \e elem en el APO receptor.
      * La operación se realiza en tiempo \e O(log n).
      */
    void insertar (const Tbase& elem);
           
    /**
      * @brief Borra todos los elementos
      *
      * Borra todos los elementos del APO receptor. Cuando termina, el APO está
      * vacío. La operación se realiza en tiempo \e O(1).
      */
    void clear();
    
    /**
      * @brief Número de elementos
      * @return El número de elementos del APO receptor.
      *
      * La operación se realiza en tiempo \e O(1).
      */
    int size() const;
    
    /**
      * @brief Comprueba si el APO está vacío
      * @return Devuelve \e true si el número de elementos del APO receptor 
      * es cero, y \e false en caso contrario.
      *
      * La operacion se realiza en tiempo O(1).
      */
    bool empty() const;     
};

/* DEFINICIONES DE LAS FUNCIONES */

#include <cassert>


/***************************************************************/
//               FUNCIONES PRIVADAS
/***************************************************************/

template <class Tbase>
void APO<Tbase>::expandir (int nelem){
  Tbase *aux;
  int i;

  if (nelem > Maxelementos){
    aux = new Tbase[nelem];
    for (i=0; i<nelementos; i++)
      aux[i] = vec[i];
    delete[] vec;
    vec = aux;
    Maxelementos = nelem;
  }
}


/***************************************************************/
//               FUNCIONES PUBLICAS
/***************************************************************/

template <class Tbase>
APO<Tbase>::APO(){
  vec = new Tbase;   //Reservamos espacio para un elemento
  nelementos = 0;    //Inicializamos nelementos
  Maxelementos = 1;  //y Maxelementos
}

/***************************************************************/

template <class Tbase>
APO<Tbase>::APO(int tam){
  vec= new Tbase[tam];   //Reservamos espacio para tam elementos
  nelementos= 0;         //Inicializamos nelementos
  Maxelementos= tam;     //y Maxelementos
}

/***************************************************************/

template <class Tbase>
APO<Tbase>::APO (const APO<Tbase>& a){
  int i,aux;

  nelementos= a.nelementos;                  //Copiamos nelementos
  aux = (a.nelementos==0) ? 1 : nelementos;  //Tamaño del vector de datos
  vec= new Tbase[aux];                       //Reservamos espacio
  Maxelementos= aux;                         //Inicializamos Maxelementos
  for (i=0; i<nelementos; i++)               //Copiamos los datos del APO
      vec[i] = a.vec[i];
}

/***************************************************************/

template <class Tbase>
inline APO<Tbase>::~APO(){
  delete[] vec;     //Libera el vector de datos
}

/***************************************************************/

template <class Tbase>
APO<Tbase>& APO<Tbase>::operator = (const APO<Tbase> &a){
  int i;

  if (this!=&a){                   //Comprobación de rigor
    delete[] vec;                  //Liberamos el vector de datos
    vec = new Tbase[a.nelementos]; //Reservamos el nuevo vector de datos
    nelementos = a.nelementos;     //Actualizamos nelementos
    Maxelementos = a.nelementos;   //y Maxelementos

    for (i=0; i<nelementos;i ++)   //Copiamos los datos del APO
      vec[i] = a.vec[i];
  }
  return *this;  //Devolvemos la referencia al objeto *this
                 //para permitir encadenamientos (a=b=c)
}

/***************************************************************/


template <class Tbase>
inline const Tbase& APO<Tbase>::minimo() const{
  assert(nelementos>0);//Comprobamos que el APO no sea vacío
  return vec[0];       //Devolvemos el mínimo, situado en vec[0] por definición
}

/***************************************************************/

template <class Tbase>
void APO<Tbase>::borrar_minimo(){
  int pos, pos_min, ultimo;
  bool acabar;
  Tbase aux;
  
  assert(nelementos>0);        //El APO no debe ser vacío
  vec[0] = vec[nelementos-1];  //Pasamos el último elemento
                               //(hoja más a la derecha)a la posición 0
  nelementos--;                //Actualizamos nelementos
  if (nelementos>1){           //Si queda más de un elemento, debemos cribar
    ultimo = nelementos-1;                //El último elemento
    pos=0;                                //Posición de trabajo
    acabar = false;                       
    while(pos<=(ultimo-1)/2 && !acabar) { //Mientras no lleguemos a una hoja
      if (2*pos+1 == ultimo)              //Si sólo hay hijo izquierda,
        pos_min = 2*pos+1;                //seleccionamos su posición
      else if (vec[2*pos+1]<vec[2*pos+2]) //Si hay dos hijos, los comparamos
        pos_min= 2*pos+1;                 //y seleccionamos el mínimo de ellos
      else
        pos_min= 2*pos+2;
      if (vec[pos_min]<vec[pos]){         //Si el menor de los hijos es menor,
        aux= vec[pos];                    //Intercambiamos el elemento
        vec[pos]=vec[pos_min];            //que estamos cribando con el hijo
        vec[pos_min]= aux;
        pos=pos_min;                  //Actualizamos pos para seguir cribando
      }
      else
        acabar= true;                 //Si el menor de los hijo no es menor,
                                      //hemos terminado la criba
    }
  }
}
    
/***************************************************************/

template <class Tbase>
void APO<Tbase>::insertar (const Tbase& elem){
  int pos;
  Tbase aux;
  
  if (nelementos==Maxelementos)   //Si no hay espacio para más elementos,
    expandir(2*Maxelementos);     //aumentamos el tamaño de vec
 
  nelementos++;                   //Actualizamos nelementos
  pos=nelementos-1;               //Posición a la derecha de la última hoja
  vec[pos]=elem;                  //Almacenamos el elemento a insertar
  while((pos>0) && (vec[pos]<vec[(pos-1)/2])){//Mientras sea menor que el padre,
    aux= vec[pos];                            //intercambiamos con el padre
    vec[pos]=vec[(pos-1)/2];
    vec[(pos-1)/2]= aux;
    pos= (pos-1)/2;          //Actualizamos pos para seguir promocionando
                             //el elemento si es necesario
  }

}

/***************************************************************/

template <class Tbase>
inline void APO<Tbase>::clear(){
  nelementos=0;
}

/***************************************************************/

template <class Tbase>
inline int APO<Tbase>::size() const{
  return nelementos;
}

/***************************************************************/

template <class Tbase>
inline bool APO<Tbase>::empty() const{
  return nelementos==0;
}

/***************************************************************/

#endif
