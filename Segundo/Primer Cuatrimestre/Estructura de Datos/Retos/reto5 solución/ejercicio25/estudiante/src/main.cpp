/*
 * @brief main ejercicio 25
 * @author HOCES CASTRO, JOSÉ ALBERTO
 */

#include "../include/bintree.h"
#include<list>
#include<iostream>

using namespace std;

bintree<int>:: node cont_hijos(const bintree<int> &A, list<int> & L) {
    queue<typename bintree<int>::node> nodos;

    // Vamos almacenando en una cola los nodos del árbol y nos deshacemos de los que ya
    // hemos analizado. Si se recorren todos los nodos, quedando esta cola vacía, es porque
    // no se ha encontrado ningún nodo cuyos hijos sean los de la lista de dos enteros.
    // Si no llega al final es porque sí se ha encontrado un nodo que cumpla lo que queremos,
    // el cual se devuelve por la función. Si no lo encuentra, devuelve el nodo nulo.

    bintree<int>::node n = A.root();
    if (!n.null()){
        nodos.push(n);
        bool found = false;
        while (!nodos.empty() && !found) {
            n = nodos.front(); nodos.pop();
            if(((!n.left().null()) && (!n.right().null()) &&
            n.left().operator*() == L.front()) && (n.right().operator*() == L.back()) )
                found = true;
            else {
                if (!n.left().null()) nodos.push(n.left());
                if (!n.right().null())
                    nodos.push(n.right());
            }
        }

        if(!found)
            n = 0;
    }

    return n;
}


int main(){

    // Creamos el árbol
    //        10
    //       /  \
    //     21    8
    //          / \
    //         6  11
    //            / \
    //           14  15

    bintree<int> A(10);
    A.insert_left(A.root(),21);
    A.insert_right(A.root(),8);
    A.insert_left(A.root().right(),6);
    A.insert_right(A.root().right(),11);
    A.insert_left(A.root().right().right(),14);
    A.insert_right(A.root().right().right(),15);

    int myints1[] = {21,8};
    list<int> list1 (myints1,myints1+sizeof(myints1)/sizeof(int));
    cout << "El nodo padre de la lista {21,8} es: " << cont_hijos(A,list1).operator*() << "\n";

    int myints2[] = {14,15};
    list<int> list2 (myints2,myints2+sizeof(myints2)/sizeof(int));
    cout << "El nodo padre de la lista {14,15} es: " << cont_hijos(A,list2).operator*() << "\n";;

    int myints3[] = {11,6};
    list<int> list3 (myints3,myints3+sizeof(myints3)/sizeof(int));
    cout << "El nodo padre de la lista {11,6} es: " << cont_hijos(A,list3).operator*() << "\n";;

    int myints4[] = {6,9};
    list<int> list4 (myints4,myints4+sizeof(myints4)/sizeof(int));
    cout << "El nodo padre de la lista {6,9} es: " << cont_hijos(A,list4).operator*() << "\n";;

    return 0;
}
