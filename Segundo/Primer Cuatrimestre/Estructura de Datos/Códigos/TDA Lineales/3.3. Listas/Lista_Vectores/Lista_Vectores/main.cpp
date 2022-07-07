#include <iostream>
#include "Lista.hpp"

using namespace std;

bool vacia(Lista& l);
int numero_elementos(const Lista& l);
void escribir(const Lista& l);
void borrar_caracter(Lista&l, char c);
Lista al_reves(const Lista& l);
void escribir_minuscula(const Lista &l);
Posicion localizar(const Lista& l, char c);
bool palindromo(const Lista& l);

int main() {
  char dato;
  Lista l;
  
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
    Lista aux(l);
    borrar_caracter(aux, ' ');
    escribir(aux);
  }
  cout << "La frase al revés: " << endl;
  escribir(al_reves(l));
  cout << (palindromo(l)? "Es " : "No es ") << "un palíndromo" << endl;
  return 0;
}

bool vacia(Lista& l){
  return(l.begin()==l.end());
}

int numero_elementos(const Lista& l){
  int n=0;
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    n++;
  return n;
}

void todo_minuscula(Lista& l){
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    l.set(p, tolower(l.get(p)));
}

void escribir(const Lista& l){
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    cout << l.get(p);
  cout << endl;
}

void escribir_minuscula(const Lista &l){
  Lista l2(l);
  todo_minuscula(l2);
  escribir(l2);
}

void borrar_caracter(Lista&l, char c){
  Posicion p = l.begin();
  while(p != l.end())
    if(l.get(p) == c)
      p = l.borrar(p);
    else
      ++p;
}

Lista al_reves(const Lista& l){
  Lista aux;
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    aux.insertar(aux.begin(), l.get(p));
  return aux;
}

Posicion localizar(const Lista& l, char c){
  for(Posicion p=l.begin(); p!=l.end(); ++p)
    if(l.get(p)==c)
      return(p);
  return l.end();
}

bool palindromo(const Lista& l){
  bool es_palindromo = true;
  Lista aux(l);
  int n = numero_elementos(l);
  if(n>=2){
    borrar_caracter(aux, ' ');
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
