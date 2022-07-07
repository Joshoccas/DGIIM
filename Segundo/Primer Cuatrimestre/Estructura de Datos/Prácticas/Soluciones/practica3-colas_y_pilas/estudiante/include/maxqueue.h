/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 */

#include <iostream>
#include <stack>

using namespace std;

/**
 * @brief Estructura que representa un elemento de la cola/pila con máximo. Formada por el valor del elemento y el
 * máximo del contenedor en el momento de consulta del elemento
 * @pre max >= value
 */
struct element {
    int value = 0;
    int max = 0;
};

/**
 * @brief T.D.A MaxQueue
 *
 * Una instancia del tipo de dato abstracto MaxQueue nos permite almacenar y manipular una secuencia de
 * estructuras del tipo element.
 *
 * El TDA MaxQueue proporciona distintas herramientas para insertar, eliminar y consultar los elementos
 * en la cola sin perder nunca de vista el mayor valor contenido en cada momento.
 *
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date Noviembre 2021
 *
 */

class MaxQueue {

private:
    /**
     * @brief Contenedor base que utilizamos para implementar la cola con máximo.
     */
    stack<element> pila;

public:

    /**
     * @brief Devuelve el tamaño actual de la cola con máximo
     * @return Número de elementos en la cola
     * @post El objeto implícito no se modificada
     */
    int size() const;

    /**
     * @brief Comprueba si la cola está o no vacía
     * @return true, si el objeto tiene 0 elementos
     * @return false, si el objeto tiene al menos 1 elemento
     * @post El objeto implícito no se modifica
     */
    bool empty() const;

    /**
     * @brief Devuelve el elemento situado al frente de la cola (first in, por ser una estructura FIFO)
     * @return struct element en la primera posición de la cola (frente)
     * @post El objeto implícito no se modifica
     */
    element front() const;

    /**
     * @brief Inserta un nuevo elemento al final de la cola actualizando el máximo en los demás elementos
     * @param nuevo número a insertar en la cola
     * @post El objeto implícito se ha modificado
     * @post El tamaño de la cola aumenta en 1
     */
    void push(int nuevo);

    /**
     * @brief Elimina ("saca") el primer elemento de la cola (front).
     * @post El objeto implícito se ha modificado
     * @post El tamaño de la cola disminuye en 1
     */
    void pop();

    //friend ostream & operator<<(ostream & os, const element & pair);
};
/**
 * @brief Sobrecarga del operador <<. Imprime por pantalla el valor y el max de una estructura element.
 */
ostream & operator<<(ostream & os, const element & pair);