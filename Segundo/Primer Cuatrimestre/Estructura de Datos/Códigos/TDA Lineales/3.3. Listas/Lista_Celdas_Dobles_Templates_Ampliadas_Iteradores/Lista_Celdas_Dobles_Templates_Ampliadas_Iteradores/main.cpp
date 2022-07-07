#include <iostream>
#include "Lista.hpp"

using namespace std;

template <class T> void todo_minuscula(Lista<T>& l);
template <class T> ostream& operator<<(ostream & flujo, const Lista<T>& l);
template <class T> void escribir_minuscula(const Lista<T> &l);
template <class T> typename Lista<T>::iterator localizar(const Lista<T>& l, const T &c);
template <class T> bool palindromo(const Lista<T>& l);

int main() {
  char dato;
  Lista<char> l;
  
  cout << "Escriba una frase" << endl;
  while((dato=cin.get())!='\n')
    //l.insertar(l.end(), dato);
    l.push_back(dato);
  
  cout << "La frase introducida es:" << endl;
  cout << l;
  cout << "La frase en minúsculas:" << endl;
  escribir_minuscula(l);
  if(localizar(l,' ')==l.end())
    cout << "La frase no tiene espacios" << endl;
  else{
    cout << "La frase sin espacios:" << endl;
    Lista<char> aux(l);
    aux.remove(' ');
    cout << aux;
  }
  cout << "La frase al revés: " << endl;
  Lista<char> al_reves(l);
  al_reves.reverse();
  cout << al_reves;
  cout << (palindromo(l)? "Es " : "No es ")
  << "un palíndromo" << endl;
  return 0;
}

template <class T>
void todo_minuscula(Lista<T>& l){
  for(typename Lista<T>::iterator it=l.begin(); it!=l.end(); ++it)
    //l.set(it, tolower(l.get(it)));
    *it = tolower(*it);
}

template <class T>
ostream& operator<<(ostream & flujo, const Lista<T>& l){
  for(typename Lista<T>::const_iterator it=l.cbegin(); it!=l.cend(); ++it)
    //cout << l.get(p);
    cout << *it;
  cout << endl;
  return flujo;
}

template <class T>
void escribir_minuscula(const Lista<T> &l){
  Lista<T> copia(l);
  todo_minuscula(copia);
  cout << l;
}

template <class T>
typename Lista<T>::iterator localizar(const Lista<T>& l, const T &c){
  for(typename Lista<T>::iterator it=l.begin(); it!=l.end(); ++it)
    if(*it == c)
      return(it);
  return l.end();
}

template <class T>
bool palindromo(const Lista<T>& l){
  Lista<T> aux(l);
  int n = l.size();
  if(n<2)
    return true;
  aux.remove(' ');
  todo_minuscula(aux);
  
  typename Lista<T>::const_iterator p1, p2;
  p1 = aux.cbegin();
  p2 = aux.cend();
  --p2;
  for(int i=0; i<n/2; i++){
    if(*p1 != *p2)
      return false;
    ++p1;
    --p2;
  }
  return true;
}
