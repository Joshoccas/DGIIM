/**
 * @file pila_max.cpp
 * @brief  Archivo de implementación del programa pila con máximo
 */

#include <stack>
#include <queue>
#include <iostream>

using namespace std;

int main(int argc, char ** argv){
//    stack<int> pila;
//    for (int i=1; i<argc; i++)
//        pila.push(atoi(argv[i]));
//    while(!pila.empty()){
//        cout << pila.top() << endl;
//        pila.pop();
//    }
    queue<char *> cola;
    for(int i=1; i<argc; i++)
        cola.push(argv[i]);
    while(!cola.empty()){
        cout << cola.front() << endl;
        cola.pop();
    }
}