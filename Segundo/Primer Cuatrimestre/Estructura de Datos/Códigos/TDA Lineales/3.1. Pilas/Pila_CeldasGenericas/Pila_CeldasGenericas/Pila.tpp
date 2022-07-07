template <class T>
Pila<T>::Pila(){
  primera = 0;
}

template <class T>
Pila<T>::Pila(const Pila<T>& p){
  copiar(p);
}

template <class T>
Pila<T>::~Pila(){
  liberar();
}

template <class T>
Pila<T>& Pila<T>::operator=(const Pila<T> &p){
  if(this!=&p){
    liberar();
    copiar(p);
  }
  return *this;
}

template <class T>
void Pila<T>::poner(const T &c){
  CeldaPila<T> *aux = new CeldaPila<T>;
  aux->elemento = c;
  aux->sig = primera;
  primera = aux;
}

template <class T>
void Pila<T>::quitar(){
  CeldaPila<T> *aux = primera;
  primera = primera->sig;
  delete aux;
}

template <class T>
T & Pila<T>::tope() {
  return primera->elemento;
}

template <class T>
const T & Pila<T>::tope() const{
  return primera->elemento;
}

template <class T>
bool Pila<T>::vacia() const{
  return (primera==0);
}

//Métodos privados auxiliares

template <class T>
void Pila<T>::copiar(const Pila<T> &p){
  if (p.primera==0)
    primera = 0;
  else{
    primera = new CeldaPila<T>;
    primera->elemento = p.primera->elemento;
    CeldaPila<T> *orig = p.primera,
                 *dest=primera;
    while(orig->sig!=0){
      dest->sig = new CeldaPila<T>;
      orig = orig->sig;
      dest = dest->sig;
      dest->elemento = orig->elemento;
    }
    dest->sig = 0;
  }
}

template <class T>
void Pila<T>::liberar(){
  CeldaPila<T>* aux;
  while(primera!=0){
    aux = primera;
    primera = primera->sig;
    delete aux;
  }
  primera = 0;
}
