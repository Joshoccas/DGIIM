#include <iostream>
#include <queue>

using namespace std;

/**
 * @brief Elimina de la cola aquellos enteros que no estén en orden creciente
 * @param Q cola a modificar
 * @post La cola Q queda modificada con todos sus elementos ordenados de forma creciente
 * @details El código se basa en el uso de una cola auxiliar sobre la que vamos metiendo
 * los enteros de la cola Q de forma selectiva. El frente de Q se introduce y se establece
 * como el máximo de la cola auxiliar. Para el resto de elementos de Q, se comprueba si
 * son mayores que el máximo guardado. En caso de serlo, se actualiza el máximo, se
 * introduce dicho elemento y se elimina de Q. Así hasta que Q quede vacía y finalmente
 * hacemos un swap entre la cola Q y la cola aux para que el resultado quede guardado en Q.
 */
void creciente(queue<int> &Q){

    queue<int> aux;

    aux.push(Q.front());
    Q.pop();
    int max = aux.front();

    while(!Q.empty()){
        if(Q.front() >= max){
            aux.push(Q.front());
            max = Q.front();
            Q.pop();
        }

        else
            Q.pop();
    }

    Q.swap(aux);
}

int main(){

    queue<int> C;
    cout << "Introduzca 10 enteros: ";
    int nuevo;

    for(int i = 0; i < 10; i++){
        cin >> nuevo;
        C.push(nuevo);
    }

    creciente(C);
    int tamanio = C.size();

    for(int i = 0; i < tamanio; i++){
        cout << C.front() << " ";
        C.pop();
    }

    return 0;
}