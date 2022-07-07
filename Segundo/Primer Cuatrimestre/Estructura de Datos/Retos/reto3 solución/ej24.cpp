#include<iostream>
#include<list>

using namespace std;

/**
 * @brief Los elementos de L1 se van intercalando en los de L2 de final a principio de L2
 * @param L1 lista de enteros cuyos elementos se intercalan en los de la segunda
 * @param L2 lista de enteros en la que se intercalan sus elementos con los de la primera
 * @post L1 queda vacía y L2 ha sido modificada
 * @details El código consiste en usar una lista auxiliar sobre la que se van intercalando
 * los elementos de L1 y L2 de la forma indicada y finalmente hacer un swap con L2, ya que
 * es en la que se nos ha pedido almacenar el resultado. Primero se comprueba que ninguna de
 * las listas sea vacía, porque en ese caso no se haría nada. Tras la comprobación, se
 * comienza insertando el último elemento de L2, ya que se van intercalando de final a principio
 * (entonces usamos push_back) y eliminamos con pop_back, y justo después insertamos el frente
 * de L1 y también lo eliminamos. Si en algún momento alguna de las dos listas queda vacía, se
 * insertan consecutivamos el resto de elementos de la que sí tiene elementos aún.
 */
void postintercalar(list<int> & L1, list<int> & L2){

    if(!L1.empty() && !L2.empty()){

        list<int> aux;

        while(!L2.empty() && !L1.empty()){
            aux.push_front(L2.back());
            L2.pop_back();
            aux.push_front(L1.front());
            L1.pop_front();
        }

        if(!L1.empty()){
            while(!L1.empty()){
                aux.push_front(L1.front());
                L1.pop_front();
            }
        }

        else{
            while(!L2.empty()){
                aux.push_front(L2.back());
                L2.pop_back();
            }
        }

        L2.swap(aux);
    }
}

int main(){

    list<int> L1;
    list<int> L2;
    int tamanio1;
    int tamanio2;
    int nuevo;

    cout << "Indique el número de elementos de la lista 1:";
    cin >> tamanio1;
    cout << "Introduzca los elementos: ";
    for(int i = 0; i < tamanio1; i++){
        cin >> nuevo;
        L1.push_back(nuevo);
    }

    cout << "Indique el número de elementos de la lista 2:";
    cin >> tamanio2;
    cout << "Introduzca los elementos: ";
    for(int i = 0; i < tamanio2; i++){
        cin >> nuevo;
        L2.push_back(nuevo);
    }

    postintercalar(L1,L2);
    list<int>::iterator i;
    for(i = L2.begin(); i != L2.end(); ++i){
        cout << *i << " ";
    }
    return 0;
}

