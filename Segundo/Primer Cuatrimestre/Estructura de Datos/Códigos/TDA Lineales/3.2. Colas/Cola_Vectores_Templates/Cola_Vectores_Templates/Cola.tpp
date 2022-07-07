#include <cassert>

template <class T>
Cola<T>::Cola(){
  reservar(10);
  anterior = posterior = nelem = 0;
}

template <class T>
Cola<T>::Cola(const Cola<T>& c){
  reservar(c.reservados);
  copiar(c);
}

template <class T>
Cola<T>& Cola<T>::operator=(const Cola<T>& c){
  if(this!=&c){
    liberar();
    reservar(c.reservados);
    copiar(c);
  }
  return(*this);
}

template <class T>
Cola<T>::~Cola(){
  liberar();
}

template <class T>
void Cola<T>::poner(const T & valor){
  if(nelem==reservados)
    resize(2*reservados);
  datos[posterior] = valor;
  posterior = (posterior+1)%reservados;
  nelem++;
}

template <class T>
void Cola<T>::quitar(){
  assert(nelem!=0);
  anterior = (anterior+1)%reservados;
  nelem--;
  if (nelem< reservados/4)
    resize(reservados/2);
}

template <class T>
T Cola<T>::frente() const{
  assert(nelem!=0);
  return datos[anterior];
}

template <class T>
bool Cola<T>::vacia() const{
  return (nelem == 0);
}

//Métodos auxiliares privados

template <class T>
void Cola<T>::reservar(const int n){
  assert(n>0);
  reservados = n;
  datos = new T[n];
}

template <class T>
void Cola<T>::liberar(){
  delete[] datos;
  datos = 0;
  anterior = posterior = nelem = reservados = 0;
}

template <class T>
void Cola<T>::copiar(const Cola &c){
  for (int i= c.anterior; i!=c.posterior; i= (i+1)%reservados)
    datos[i] = c.datos[i];
  anterior = c.anterior;
  posterior = c.posterior;
  nelem = c.nelem;
  
}

template <class T>
void Cola<T>::resize(const int n){
  assert(n>0 && n>=nelem);
  T* aux = datos;
  int tam_aux = reservados;
  reservar(n);
  for(int i=0; i<nelem; i++)
    datos[i] = aux[(anterior+i)%tam_aux];
  anterior = 0;
  posterior = nelem;
  delete[] aux;
}

