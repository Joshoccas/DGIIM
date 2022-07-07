#include <iostream>
#include <stack>
using namespace std;

int evalua(string e);

int main(){
//  stack<int> pila;
//
//  // Se introducen tres elementos en la pila.
//  pila.push(1);     pila.push(2);     pila.push(3);
//
//  // Se sacan e imprimen dos elementos.
//  cout << pila.top() << ' ';     pila.pop();
//  cout << pila.top() << ' ';     pila.pop();
//
//  // Se modifica el del tope.
//  pila.top() = 77;
//
//  // Se introducen dos nuevos elementos.
//  pila.push(4);
//  pila.push(5);
//  // Se elimina el del tope sin procesarlo.
//  pila.pop();
//  // Se sacan de la pila el resto de elementos.
//  while (!pila.empty()) {
//    cout << pila.top() << ' ';
//    pila.pop(); }
//  cout << endl;
//
//  //Segunda parte. Evaluación de una expresión postfija
//
//  string expresion = "34-2*52+3**";
//  cout << evalua(expresion) << endl;
  
  //Programa principal usado en las transparencias
  
  stack<char> p, q;
  char dato;
  
  cout << "Escriba una frase" << endl;
  while((dato=cin.get())!='\n')
    p.push(dato);
  
  cout << "La escribimos del revés" << endl;
  while(!p.empty()){
    cout << p.top();
    q.push(p.top());
    p.pop();
  }
  
  cout << endl << "La frase original era" << endl;
  while(!q.empty()){
    cout << q.top();
    q.pop();
  }
  cout << endl;
  return 0;
}

/**
 @param e expresion en postfijo (cada elemento  del vector
 se corresponde con un elemento de la expresion).
 @return  el resultado de evaluar la expresion
 */
int evalua(string e)
{
  stack<int> v;
  int i, izq,dcha;
  for (i=0; i!=e.size(); ++i) {
    // recorrido de los caracteres del string.
    if ((e[i]>='0') && (e[i]<='9'))
      v.push(e[i]-'0');
    else {
      dcha = v.top(); v.pop();
      izq = v.top(); v.pop();
      switch (e[i]) {
        case '+': v.push(izq+dcha); break;
        case '-': v.push(izq-dcha); break;
        case '*': v.push(izq*dcha); break;
        case '/': v.push(izq/dcha); break;
      } // switch
    } // else
  } // for
  return v.top();
} 
