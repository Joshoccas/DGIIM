#include <iostream>
#include <list>

using namespace std;

template <class T>
typename list<T>::iterator localizar(list<T> l, const T &c);
ostream& operator<<(ostream & flujo, const list<char>& l);
void escribir_minuscula(list<char> l);
bool palindromo(const list<char>& l);

int main() {
  char dato;
  list<char> l, aux;
  
  cout << "Escriba una frase" << endl;
  while((dato=cin.get())!='\n')
    l.insert(l.end(), dato); //l.emplace_back(dato);
  
  cout << "La frase introducida es:" << endl;
  cout << l;
  cout << "La frase en minúsculas:" << endl;
  escribir_minuscula(l);
  if(localizar(l,' ')==l.end())
    cout << "La frase no tiene espacios" << endl;
  else{
    cout << "La frase sin espacios:" << endl;
    aux = l;
    aux.remove(' ');
    cout << aux;
  }
  cout << "La frase al revés: " << endl;
  aux = l;
  aux.reverse();
  cout << aux;
  cout << (palindromo(l) ? "Es " : "No es ") << "un palíndromo" << endl;
  list<char>::iterator it;
  it = localizar(l, ' ');
  return 0;
}

void todo_minuscula(list<char>& l){
  list<char>::iterator p;
  for(p=l.begin(); p!=l.end(); p++)
    *p = tolower(*p);
}

ostream& operator<<(ostream & flujo, const list<char>& l){
  list<char>::const_iterator p;
  for(p=l.cbegin(); p!=l.cend(); p++)
    flujo << *p;
  flujo << endl;
  return flujo;
}

void escribir_minuscula(list<char> l){
  todo_minuscula(l);
  cout << l;
}

template <class T>
typename list<T>::iterator localizar(list<T> l, const T &c){
  typename list<T>::iterator p;
  for(p=l.begin(); p!=l.end(); p++)
    if(*p==c)
      return(p);
  return l.end();
}

bool palindromo(const list<char>& l){
  list<char> aux(l);
  int n = l.size();
  if(n<2)
    return true;
  aux.remove(' ');
  todo_minuscula(aux);
  
  list<char>::const_iterator p1, p2;
  p1 = aux.begin();
  p2 = aux.end();
  --p2;
  for(int i=0; i<n/2; i++){
    if(*p1 != *p2)
      return false;
    ++p1;
    --p2;
  }
  return true;
}
