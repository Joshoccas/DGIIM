/*
 * @brief main ejercicio 30
 * @author HOCES CASTRO, JOSÉ ALBERTO
 */

#include<iostream>
#include "../include/bintree.h"
#include<list>

using namespace std;

void path_of_largest(bintree<int> & A, list<int> & L){
    bintree<int>::node n = A.root();
    L.push_back(n.operator*());
    queue<typename bintree<int>::node> nodos;
    if (!n.null()){
        nodos.push(n);
        bool stop = false;

        // Recorremos los nodos del árbol de la forma que nos interesa. Si alguno de los dos hijos es el
        // nodo nulo, tomamos el camino del nodo no nulo, almacenándolo en la cola de nodos y guardando
        // en la lista el valor de su etiqueta. Si ninguno de los dos es nulo, se comparan sus etiquetas
        // y se toma el camino del nodo cuya etiqueta es mayor, guardándolo en la cola de nodos para seguir
        // recorriendo los nodos que nos interesan y guardando su etiqueta en la lista. Si llegamos a un
        // nodo cuyos dos hijos son los nodos nulos, entonces significa que hemos llegado al final del
        // camino y por lo tanto, terminamos la ejecución de la función.

        while (!nodos.empty() && !stop) {
            n = nodos.front(); nodos.pop();
            if(n.left().null() && n.right().null()){
                stop = true;
            }
            else if((!n.left().null()) && n.right().null()) {
                nodos.push(n.left());
                L.push_back(n.left().operator*());
            }
            else if((n.left().null()) && !n.right().null()){
                nodos.push(n.right());
                L.push_back(n.right().operator*());
            }
            else if(n.left().operator*() < n.right().operator*()){
                nodos.push(n.right());
                L.push_back(n.right().operator*());
            }
            else{
                nodos.push(n.left());
                L.push_back(n.left().operator*());
            }
        }
    }
}

int main(){

    // Creamos el árbol del enunciado
    //             1
    //            / \
    //           4   7
    //          / \ / \
    //         8  9 11 10
    //           /   \
    //          6    14
    //               / \
    //              8   8

    bintree<int> A(1);
    A.insert_left(A.root(),4);
    A.insert_right(A.root(),7);
    A.insert_left(A.root().left(),8);
    A.insert_right(A.root().left(),9);
    A.insert_left(A.root().left().right(),6);
    A.insert_left(A.root().right(),11);
    A.insert_right(A.root().right(),10);
    A.insert_right(A.root().right().left(),14);
    A.insert_left(A.root().right().left().right(),8);
    A.insert_right(A.root().right().left().right(),8);

    list<int> L;

    path_of_largest(A,L);

    list<int>::iterator it;
    for(it = L.begin(); it != L.end(); it++){
        cout << *it << " ";
    }
    return 0;
}