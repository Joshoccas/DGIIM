#include <iostream>
#include "Lista.hpp"

using namespace std;

template <typename T> bool vacia(Lista<T>& l);
template <typename T> int numero_elementos(const Lista<T>& l);
template <typename T> void escribir(const Lista<T>& l);
template <typename T> void borrar_elemento(Lista<T>&l, T c);
template <typename T> Lista<T> al_reves(const Lista<T>& l);
template <typename T> Posicion localizar(const Lista<T>& l, T c);
//Funciones específicas para listas de char
void todo_minuscula(Lista<char>& l);
void escribir_minuscula(const Lista<char> &l);
bool palindromo(const Lista<char>& l);

int main() {
  char dato;
  Lista<char> l;
  
  cout << "Escriba una frase" << endl;
  while((dato=cin.get())!='\n')
    l.insertar(l.end(), dato);
  
  cout << "La frase introducida es:" << endl;
  escribir(l);
  cout << "La frase en minúsculas:" << endl;
  escribir_minuscula(l);
  if(localizar(l,' ')==l.end())
    cout << "La frase no tiene espacios" << endl;
  else{
    cout << "La frase sin espacios:" << endl;
    Lista<char> aux(l);
    borrar_elemento(aux, ' ');
    escribir(aux);
  }
  cout << "La frase al revés: " << endl;
  escribir(al_reves(l));
  cout << (palindromo(l)? "Es " : "No es ") << "un palíndromo" << endl;
  return 0;
}

template <typename T>
bool vacia(Lista<T>& l){
  return(l.begin()==l.end());
}

template <typename T>
int numero_elementos(const Lista<T>& l){
  int n=0;
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    n++;
  return n;
}

void todo_minuscula(Lista<char>& l){
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    l.set(p, tolower(l.get(p)));
}

template <typename T>
void escribir(const Lista<T>& l){
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    cout << l.get(p);
  cout << endl;
}

void escribir_minuscula(const Lista<char> &l){
  Lista<char> l2(l);
  todo_minuscula(l2);
  escribir(l2);
}

template <typename T>
void borrar_elemento(Lista<T>&l, T c){
  Posicion p = l.begin();
  while(p != l.end())
    if(l.get(p) == c)
      p = l.borrar(p);
    else
      ++p;
}

template <typename T>
Lista<T> al_reves(const Lista<T>& l){
  Lista<T> aux;
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    aux.insertar(aux.begin(), l.get(p));
  return aux;
}

template <typename T>
Posicion localizar(const Lista<T>& l, T c){
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    if(l.get(p)==c)
      return(p);
  return l.end();
}

bool palindromo(const Lista<char>& l){
  bool es_palindromo = true;
  Lista<char> aux(l);
  int n = numero_elementos(l);
  if(n>=2){
    borrar_elemento(aux, ' ');
    todo_minuscula(aux);
  
    Posicion p1, p2;
    p1 = aux.begin();
    p2 = aux.end();
    p2--;
    for(int i=0; i<n/2 && es_palindromo; i++){
      if(aux.get(p1) != aux.get(p2))
        es_palindromo = false;
      p1++;
      p2--;
    }
  }
  return es_palindromo;
}
