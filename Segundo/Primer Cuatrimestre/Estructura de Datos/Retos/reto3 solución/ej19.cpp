#include <iostream>
#include <stack>

using namespace std;
/**
 * @brief Elimina de la pila las ocurrencias consecutivas
 * @param p pila de enteros a modificar
 * @post El tamaño de la pila disminuye
 * @details El código consiste en insertar el tope de la pila en la auxiliar, eliminarlo de la actual y empezar a
 * compararlo con el nuevo tope de la pila actual. Si son iguales, el tope de la pila actual no se copia en la
 * actual y simplemente se elimina. Se continúa hasta encontrar un tope de la actual que no coincida con el de la
 * auxiliar, se añade a esta y se elimina de la actual. Se sigue el mismo proceso hasta recorrer toda la pila actual
 * y finalmente se hace un swap entre la auxiliar y la actual para lograr la modificación sobre la actual.
 */
void transformarpila(stack<int> & p){

    stack<int> aux;
    int tamanio = p.size();

    for(int i = 0; i < tamanio; i++){
        if(aux.empty()){
            aux.push(p.top());
            p.pop();
        }
        else{
            if(aux.top() == p.top())
                p.pop();
            else{
                aux.push(p.top());
                p.pop();
            }
        }
    }

    // Finalmente devolvemos los elementos a la pila original, ya que si hiciésemos un swap directamente, habríamos
    // eliminado las ocurrencias pero habríamos invertido el orden de los elementos de la pila

    tamanio = aux.size();

    for(int i = 0; i < tamanio; i++){
        p.push(aux.top());
        aux.pop();
    }
}
int main() {
    // Hemos de tener en cuenta que por la estructura de la pila, los enteros quedarán en el orden inverso al
    // introducido. POr ejemplo si se meten 1 3 3 4 5 6, la pila quedaría como 6 5 4 3 3 1, y tras aplicar la
    // función quedaría como 6 5 4 3 1

    cout << "Introduzca 10 enteros en la pila: ";
    stack<int> P;
    int nuevo;

    for(int i = 0; i < 10; i++){
        cin >> nuevo;
        P.push(nuevo);
    }

    transformarpila(P);
    int tamanio = P.size();

    for(int i = 0; i < tamanio; i++){
        cout << P.top() << " ";
        P.pop();
    }
    return 0;
}
