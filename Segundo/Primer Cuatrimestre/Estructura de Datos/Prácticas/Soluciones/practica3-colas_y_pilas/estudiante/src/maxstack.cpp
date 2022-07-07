/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 */

#include <queue>
#include <iostream>
#include "maxstack.h"

using namespace std;

int MaxStack::size() const {

    return cola.size();
}

bool MaxStack::empty() const {

    return cola.empty();
}

element MaxStack::top() const{

    return cola.front();
}

void MaxStack::push(int nuevo) {

    queue<element> aux;
    element pair;
    pair.max = nuevo;
    pair.value = nuevo;

    if(size() != 0) {
        if (top().max >= pair.max)
            pair.max = top().max;
    }

    aux.push(pair);

    while(!empty()){
        aux.push(top());
        pop();
    }

    while(!aux.empty()){
        cola.push(aux.front());
        aux.pop();
    }
}

void MaxStack::pop(){

    return cola.pop();
}

ostream & operator<<(std::ostream & os, const element & pair){

    cout << pair.value << "," << pair.max;
    return os;
}
