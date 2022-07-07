#include <iostream>
#include <queue>

using namespace std;

/**
 * @brief Coloca todos los enteros delante del primer número par al final, dejando como frente al primer par
 * @param C cola de enteros a modificar
 * @post El orden de los elementos de la cola se ha modificado
 * @details El código consiste en usar el operador % para encontrar al primer par de la cola. Mientras que no se
 * encuentra, colocamos al final de la cola el frente actual y eliminamos ese frente. Tuve que guardar el tamaño
 * ya que si no hay ningún número par, entraba en un bucle infinito (en ese caso la cola quedaría igual que al
 * principio.
 */
void rotacion(queue<int> & C){

    int cont = 0;
    int tamanio = C.size();

    while(C.front() % 2 != 0 && cont != tamanio){

        C.push(C.front());
        C.pop();
        cont++;
    }
}
int main(){

    queue<int> C;
    cout << "Introduzca 10 enteros: ";
    int nuevo;

    for(int i = 0; i < 10; i++){
        cin >> nuevo;
        C.push(nuevo);
    }

    rotacion(C);
    int tamanio = C.size();

    for(int i = 0; i < tamanio; i++){
        cout << C.front() << " ";
        C.pop();
    }

    return 0;
}