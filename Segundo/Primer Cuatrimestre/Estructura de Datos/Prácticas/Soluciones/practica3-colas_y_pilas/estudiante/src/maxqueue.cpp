/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 */

#include "maxqueue.h"

using namespace std;


int MaxQueue::size() const{
    return pila.size();
}

bool MaxQueue::empty() const{
    return pila.empty();
}

element MaxQueue::front() const{
    return (pila.top());
}

void MaxQueue::push(int nuevo){

    stack<element> aux;

    for (int i = 0; !empty(); i++){
        aux.push(pila.top());
        pila.pop();
    }

    element nelem;
    nelem.value = nuevo;
    nelem.max = nuevo;
    pila.push(nelem);

    for (int i = 0; !aux.empty(); i++){
        nelem.value = aux.top().value;
        nelem.max = max(pila.top().max, nelem.value);
        pila.push(nelem);
        aux.pop();
    }
}

void MaxQueue::pop() {
    pila.pop();
}

ostream & operator<<(ostream & os, const element & pair){

    cout << pair.value << "," << pair.max;
    return os;
}