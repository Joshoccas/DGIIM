#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main() {
  stack<char> p;
  queue<char> c;
  char dato;
  cout << "Escriba una frase" <<endl;
  while((dato=cin.get()) !='\n')
    if (dato != ' '){
      p.push(dato);
      c.push(dato);
    }
  bool palindromo = true;
  while(!p.empty() && palindromo){
    if(c.front() != p.top())
      palindromo = false;
    p.pop();
    c.pop();
  }
  cout << "La frase " << (palindromo ? "es" : "no es")
       << " un palíndromo" << endl;

  return 0;

  //Ejemplo de uso de transparencias de la STL
  
//  queue<string> q;
//  // Inserción de tres elmentos en la cola.
//  q.push("Tenemos "); q.push("más"); q.push("de");
//
//  // Impresión de dos elementos.
//  cout << q.front(); q.pop(); cout << q.front(); q.pop();
//
//  // Inserción de dos nuevos elementos.
//  q.push("cuatro"); q.push("elementos");
//
//  // Pasamos del elemento del frente.
//  q.pop();
//
//  // Impresión de dos elementos.
//  cout << q.front(); q.pop();
//  cout << q.front() << endl; q.pop();
//
//  // impresión del número de elementos en la cola.
//  cout << "Número de elementos: " << q.size() << endl;
}
