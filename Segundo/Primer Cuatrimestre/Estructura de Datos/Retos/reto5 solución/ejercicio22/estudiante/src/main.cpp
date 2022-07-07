/*
 * @brief main ejercicio 22
 * @author HOCES CASTRO, JOSÉ ALBERTO
 */

#include "../include/bintree.h"
#include<iostream>

using namespace std;

bool es_inferior(bintree<int> & ab1, bintree<int> & ab2){

    // Comprobamos que ambos árboles tienen la misma ramificación recorriendo ambos y poniendo
    // todas sus etiquetas a 1

    bool es_inferior = true;
    bintree<int> aux1(ab1);
    bintree<int> aux2(ab2);

    bintree<int>::level_iterator it3;
    bintree<int>::level_iterator it4;

    it3 = aux1.begin_level();
    it4 = aux2.begin_level();
    bool parada = false;

    while(!parada) {
        it3.operator*() = 1;
        it4.operator*() = 1;
        ++it3;
        ++it4;
        if(it3 == ab1.end_level() || it4 == ab2.end_level())
            parada = true;
    }

    // Si los árboles auxiliares de etiquetas a 1 coinciden, procedemos a comparar con iteradores por nivel los
    // árboles pasados como argumentos a la función

    if(aux1 == aux2) {

        bintree<int>::level_iterator it1;
        bintree<int>::level_iterator it2;

        parada = false;

        it1 = ab1.begin_level();
        it2 = ab2.begin_level();

        while (!parada) {
            if (it1.operator*() >= it2.operator*()) {
                parada = true;
                es_inferior = false;
            }
            ++it1;
            ++it2;
            if (it1 == ab1.end_level() || it2 == ab2.end_level())
                parada = true;
        }
    }
    else
        es_inferior = false;

    return es_inferior;
}

int main(){

    // Creamos dos árboles
    //              4
    //             / \
    //            3   8
    //               / \
    //              3   1

    bintree<int> ab1(4);
    ab1.insert_left(ab1.root(),3);
    ab1.insert_right(ab1.root(),8);
    ab1.insert_left(ab1.root().right(),3);
    ab1.insert_right(ab1.root().right(),1);

    //              5
    //             / \
    //            4   9
    //               / \
    //              11 17

    bintree<int> ab2(5);
    ab2.insert_left(ab2.root(),4);
    ab2.insert_right(ab2.root(),9);
    ab2.insert_left(ab2.root().right(),11);
    ab2.insert_right(ab2.root().right(),17);

    // Este caso concreto daría true, aunque he probado varias casuísticas
    // cambiando algunas etiquetas de ambos árboles

    bool resultado = es_inferior(ab1,ab2);

    if(resultado)
        cout << "El primer árbol es inferior al segundo";
    else
        cout << "El primer árbol no es inferior al segundo";

    return 0;
}
