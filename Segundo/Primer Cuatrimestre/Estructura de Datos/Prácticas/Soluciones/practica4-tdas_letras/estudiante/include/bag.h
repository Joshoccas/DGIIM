/**
 * @file bag.h
 * @brief Archivo de especificación e implementación del TDA Bag
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef __BAG_H__
#define __BAG_H__

/**
 *  @brief TDA abstracto Bag
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */

template <class T>
class Bag {

private:
    vector<T> v;
public:

    /**
     * @brief Constructor por defecto
     * Crea un onjeto de tipo Bag<T> vacío
     */

    Bag(){clear();}

    /**
     * @brief Constructor de copia
     * Crea una copia exacta de otro objeto de tipo Bag
     * @param other Objeto de tipo Bag<T> del que se va a realizar la copia
     */

    Bag(const Bag<T> & other){
        this = other;
    }

    /**
     * @brief Añade un elemento a la bolsa
     * @param element elemento del tipo T a añadir a la bolsa
     * @post La bolsa tiene un nuevo elemento añadido al final de la misma
     */

    void add(const T & element){
        v.push_back(element);
    }

    /**
     * @brief Extrae un elemento aleatorio de la bolsa
     * Devuelve un elemento aleatorio de la bolsa y lo elimina de la misma
     * @return Elemento de tipo T extraído de la bolsa
     * @pre La bolsa no está vacía
     * @post El elemento devuelto se ha eliminado de la bolsa
     */

    T get(){
        srand(time(NULL));
        int pos = rand()%size();
        T result = v.at(pos);
        v.at(pos) = v.back();
        v.pop_back();
        return result;
    }

    /**
     * @brief Elimina todos los elementos de la bolsa
     * Borra todos los elementos almacenados en la bolsa
     * @post La bolsa queda vacía
     */

    void clear(){
        v.clear();
    }

    /**
     * @brief Tamaño de la bolsa
     * @return Número de elementos que hay en la bolsa
     */

    unsigned int size() const{
        return v.size();
    }

    /**
     * @brief Comprueba si la bolsa está vacía
     * @return true si la bolsa está vacía, falso en caso contrario
     */

    bool empty(){
        return v.empty();
    }

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other Bag<T> a copiar
     * @return Referencia a this para poder encadenar el operador
     * @post La bolsa sobre la que se usa es idéntica a la pasado como parámetro
     */

    const Bag<T> & operator=(const Bag<T> & other){

        if(&other!=this)
            v = other.v;

        return *this;
    }

};

#endif
