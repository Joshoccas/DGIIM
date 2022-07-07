#include <iostream>
#include "Lista.hpp"

using namespace std;

template <class T> bool vacia(Lista<T>& l);
template <class T> int numero_elementos(const Lista<T>& l);
template <class T> void escribir(const Lista<T>& l);
template <class T> void borrar_caracter(Lista<T>&l, T c);
template <class T> Lista<T> al_reves(const Lista<T>& l);
template <class T> void escribir_minuscula(Lista<T> l);
template <class T> Posicion<T> localizar(const Lista<T>& l, T c);
template <class T> bool palindromo(const Lista<T>& l);

int main() {
  char dato;
  Lista<char> l;
  
  cout << "Escriba una frase" << endl;
  while((dato=cin.get())!='\n')
    //l.insertar(l.end(), dato);
    l.push_back(dato);
  
  cout << "La frase introducida es:" << endl;
  escribir(l);
  cout << "La frase en minúsculas:" << endl;
  escribir_minuscula(l);
  if(localizar(l,' ')==l.end())
    cout << "La frase no tiene espacios" << endl;
  else{
    cout << "La frase sin espacios:" << endl;
    Lista<char> aux(l);
    borrar_caracter(aux, ' ');
    escribir(aux);
  }
  cout << "La frase al revés: " << endl;
  escribir(al_reves(l));
  cout << (palindromo(l)? "Es " : "No es ")
  << "un palíndromo" << endl;
  return 0;
}

template <class T>
bool vacia(Lista<T>& l){
  return(l.begin()==l.end());
}

template <class T>
int numero_elementos(const Lista<T>& l){
  int n=0;
  for(Posicion<T> p=l.begin(); p!=l.end(); ++p)
    n++;
  return n;
}

template <class T>
void todo_minuscula(Lista<T>& l){
  for(Posicion<T> p=l.begin(); p!=l.end(); ++p)
    l.set(p, tolower(l.get(p)));
    //*p = tolower(*p);
}

template <class T>
void escribir(const Lista<T>& l){
  for(Posicion<T> p=l.begin(); p!=l.end(); ++p)
    //cout << l.get(p);
    cout << *p;
  cout << endl;
}

template <class T>
void escribir_minuscula(Lista<T> l){
  todo_minuscula(l);
  escribir(l);
}

template <class T>
void borrar_caracter(Lista<T>&l, T c){
  Posicion<T> p = l.begin();
  while(p != l.end())
    if(l.get(p) == c)
      p = l.borrar(p);
    else
      ++p;
}

template <class T>
Lista<T> al_reves(const Lista<T>& l){
  Lista<T> aux;
  for(Posicion<T> p=l.begin(); p!=l.end(); ++p)
    aux.insertar(aux.begin(), l.get(p));
  return aux;
}

template <class T>
Posicion<T> localizar(const Lista<T>& l, T c){
  for(Posicion<T> p=l.begin(); p!=l.end(); ++p)
    if(l.get(p)==c)
      return(p);
  return l.end();
}

template <class T>
bool palindromo(const Lista<T>& l){
  Lista<T> aux(l);
  int n = numero_elementos(l);
  if(n<2)
    return true;
  borrar_caracter(aux, ' ');
  todo_minuscula(aux);
  
  Posicion<T> p1, p2;
  p1 = aux.begin();
  p2 = aux.end();
  --p2;
  for(int i=0; i<n/2; i++){
    if(aux.get(p1) != aux.get(p2))
      return false;
    ++p1;
    --p2;
  }
  return true;
}
