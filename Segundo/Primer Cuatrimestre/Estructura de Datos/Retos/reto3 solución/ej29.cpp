#include<iostream>
#include<list>
#include<algorithm>

using namespace std;

/**
 * @brief Se crea una lista de listas de enteros a partir de L, siendo las listas la agrupación de ocurrencias de cada
 * uno de los distintos enteros de L en orden creciente
 * @param L lista de enteros cuyos elementos van a determinar la lista de listas de enteros
 * @post L no se modifica y se ha creado una lista de listas
 * @details El código consiste en la creación de una lista auxiliar que es una copia exacta de L para poder trabajar
 * con sus elementos, ya que L se ha pasado por referencia constante. Antes de empezar a trabajar, aprovechamos la
 * función sort de la STL para que los enteros ya estén ordenados en orden ascendente y no tener nosostros que
 * ordenarlos. Se crea la lista de listas sobre la que iremos guardando cada lista. En cada iteración del bucle,
 * contamos las repeticiones del frente de aux en la lista aux y guardamos el valor de ese frente. Usamos ese valor
 * y las repeticiones para aprovechar el constructor de listas con parámetros, y dicha lista recién creada se añade
 * al final de la lista de listas. Finalmente se eliminan todos los elementos con el valor del frente actual y
 * repetimos el proceso para el nuevo frente y se acaba cuando aux quede vacía.
 * @return resultado lista de listas de enteros
 */
list<list<int>> agrupariguales(const list<int> & L) {

    list<int> aux;
    aux = L;
    aux.sort();
    list<list<int>> resultado;
    int recurrencia;
    int elemento;

    while (!aux.empty()) {

        recurrencia = count(aux.begin(), aux.end(), aux.front());
        elemento = aux.front();
        list<int> nuevo(recurrencia, elemento);
        resultado.push_back(nuevo);
        aux.remove(elemento);
    }

    return resultado;
}

int main(){

    list<int> L1;
    int tamanio1;
    int nuevo;
    cout << "Indique el número de elementos de la lista 1:";
    cin >> tamanio1;
    cout << "Introduzca los elementos: ";
    for(int i = 0; i < tamanio1; i++){
        cin >> nuevo;
        L1.push_back(nuevo);
    }

    list<list<int>> resultado = agrupariguales(L1);

    list<list<int>>::iterator i;
    list<int>::iterator j;

    for(i = resultado.begin(); i != resultado.end(); ++i){
        for(j = (*i).begin(); j != (*i).end(); ++j)
            cout << *j << " ";

        cout << "\n";
    }

    return 0;
}