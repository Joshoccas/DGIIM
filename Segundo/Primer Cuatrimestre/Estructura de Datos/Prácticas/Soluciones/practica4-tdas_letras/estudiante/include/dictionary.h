/**
 * @file dictionary.h
 * @brief Archivo de especificación del TDA Dictionary
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include<iostream>
#include <vector>
#include<set>

using namespace std;

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

/**
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 */

class Dictionary {
private:
    set <string> words;
public:

    /**
     * @brief Constructor por defecto
     * Crea un Dictionary vacío
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     * @param other Dictionary que se quiere copiar
     * @post El Dictionary sobre el que se usa es idéntico al pasado como parámetro
     */
    Dictionary(const Dictionary & other);

    /**
     * @brief Indica si una palabra está en el diccionario o no
     * Este método comprueba si una determinada palabra se encuentra o no en el diccionario
     * @param val la palabra que se quiere buscar
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string & val) const;

    /**
     * @brief Inserta una palabra en el diccionario
     * @param val palabra a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta con éxito si no existía
     * previamente en el diccionario
     */
    bool insert(const string & val);

    /**
     * @brief Elimina una palabra del diccionario
     * @param val Palabra a borrar del diccionario
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string & val);

    /**
     * @brief Limpia el Dictionary
     * Elimina todas las palabras contenidas en el conjunto
     * @post El diccionario queda vacío
     */
    void clear();

    /**
     * @brief Comprueba si el diccionario está vacío
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const;

    /**
     * @brief Tamaño del diccionario
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const;

    /**
     * @brief Indica el número entero de apariciones de una letra
     * @param c letra a buscar
     * @return Un entero indicando el número de apariciones
     */
    int getOcurrences(const char c);

    /**
     * @brief Cuenta el total de letras en un diccionario
     * @return Entero con el total de letras
     */
    int getTotalLetters();

    /**
     * @brief Devuelve las palabras en el diccionario con una longitud dada
     * @param length Longitud de las palabras buscadas
     * @return Vector de palabras con la longitud deseada
     */
    vector<string> wordsOfLength(int length);

    /**
     * @brief TDA iterator asociado a Dictionary, señala a los elementos contenidos en él.
     *
     *
     * Permite recorrer el Dictionary con posible modificación del mismo, por lo que solo
     * se puede usar con contenedores no constantes.
     * Es mutable.
     */
    class iterator{
    private:
        set<string>::iterator it;

    public:

        /**
         * @brief Constructor sin parámetros. Crea un iterador nulo
         */
        iterator(){}

        /**
         * @brief Constructor de copia
         * @param otro iterador sobre un set de datos string a copiar
         * @post el objeto implícito es igual a otro
         */
        iterator(const set<string>::iterator& otro):it(otro){}

        /**
         * @brief Constructor de copia
         * @param otro iterador a copiar
         * @post El objeto implícito es igual a otro
         */
        iterator(const iterator& otro):it(otro.it){}
        /**
         * @brief Destructor
         */
        ~iterator(){}

        /**
         * @brief Operador de asignación
         * @param otro iterador sobre un set de datos string a copiar
         * @return puntero al objeto implícito
         */
        iterator& operator=(const set<string>::iterator& otro){it=otro;return *this;}
        /**
         * @brief Operador de asignación
         * @param otro iterador a copiar
         * @return puntero al objeto implícito
         */
        iterator& operator=(const iterator& otro){it=otro.it;return *this;}
        /**
         * @brief Obtiene el objeto al que apunta el iterador.
         * @pre El objeto implícito es distinto de end()
         * @return Elemento del diccionario al que apunta el iterador
         */
        string operator*()const{return *it;}
        /**
         * @brief Operador de preincremento
         * @pre El objeto implícito es distinto a end()
         * @return puntero al objeto implícito
         * @post El iterador apunta una posición más a la derecha
         */
        iterator& operator++(){++it;return *this;}
        /**
         * @brief Operador de predecremento
         * @pre El objeto implícito es distinto a begin()
         * @return puntero al objeto implícito
         * @post El iterador apunta una posición más a la izquierda
         */
        iterator& operator--(){--it;return *this;}
        /**
         * @brief Operador de postincremento
         * @pre El objeto implícito es distinto a end()
         * @return puntero al objeto implícito
         * @post El iterador apunta una posición más a la derecha
         */        iterator& operator++(int){it++;return *this;}
        /**
          * @brief Operador de postdecremento
          * @pre El objeto implícito es distinto a begin()
          * @return puntero al objeto implícito
          * @post El iterador apunta una posición más a la izquierda
          */
        iterator& operator--(int){it--;return *this;}
        /**
         * @brief Operador de desigualdad
         * @param otro iterador con el que se va a comparar el objeto implícito
         * @return FALSE si apuntan a la misma posición y TRUE si no es así
         */
        bool operator!=(const iterator& otro){return it != otro.it;}
        /**
         * @brief Operador de igualdad
         * @param otro iterador con el que se va a comparar el objeto implícito
         * @return TRUE si apuntan a la misma posición y FALSE si no es así
         */
        bool operator==(const iterator& otro){return it == otro.it;}
    };

    /**
     * @brief Devuelve un iterador que apunta al comienzo del diccionario
     * @return iterador apuntando al principio del set words
     */
    iterator begin(){iterator i = words.begin();return i;}

    /**
     * @brief Devuelve un iterador que apunta al final del diccionario (posición después de la última)
     * @return iterador apuntando al final del set words
     */
    iterator end(){iterator i = words.end();return i;}

    /**
     * @brief TDA const_iterator asociado a Dictionary, señala a los elementos contenidos en él.
     *
     *
     * Permite recorrer el Dictionary pero no modificarlo, por lo que se puede usar tanto con
     * Dictionary constantes como no constantes.
     * Es mutable.
     */
    class const_iterator{
    private:
        set<string>::const_iterator it;

    public:

        /**
         * @brief Constructor sin parámetros
         */
        const_iterator(){}
        /**
         * @brief Constructor de copia
         * @param otro
         */
        const_iterator(const set<string>::const_iterator& otro):it(otro){}
        /**
         * @brief Constructor de copia
         * @param otro
         */
        const_iterator(const const_iterator& otro):it(otro.it){}
        /**
         * @brief Destructor
         */
        ~const_iterator(){}
        /**
         * @brief Operador de asignación
         * @param otro iterador constante al que se va a igualar el implícito
         * @return puntero al objeto implícito
         */
        const_iterator& operator=(const set<string>::const_iterator& otro){it=otro;return *this;}
        /**
         * @brief Operador de asignación
         * @param otro iterador constante al que se va a igualar el implícito
         * @return puntero al objeto implícito
         */
        const_iterator& operator=(const const_iterator& otro){it=otro.it;return *this;}
        /**
         * @brief Obtiene el objeto al que apunta el iterador.
         * @pre El objeto implícito es distinto de end()
         * @return Elemento del diccionario al que apunta el iterador
         */
        const string operator*()const{return *it;}
        /**
         * @brief Operador de preincremento
         * @pre El objeto implícito es distinto a end()
         * @return puntero al objeto implícito
         * @post El iterador apunta una posición más a la derecha
         */
        const_iterator& operator++(){++it;return *this;}
        /**
         * @brief Operador de predecremento
         * @pre El objeto implícito es distinto a begin()
         * @return puntero al objeto implícito
         * @post El iterador apunta una posición más a la izquierda
         */
        const_iterator& operator--(){--it;return *this;}
        /**
         * @brief Operador de postincremento
         * @pre El objeto implícito es distinto a end()
         * @return puntero al objeto implícito
         * @post El iterador apunta una posición más a la derecha
         */
        const_iterator& operator++(int){it++;return *this;}
        /**
         * @brief Operador de postdecremento
         * @pre El objeto implícito es distinto a begin()
         * @return puntero al objeto implícito
         * @post El iterador apunta una posición más a la izquierda
         */
        const_iterator& operator--(int){it--;return *this;}
        /**
          * @brief Operador de desigualdad
          * @param otro iterador constante con el que se va a comparar el objeto implícito
          * @return FALSE si apuntan a la misma posición y TRUE si no es así
          */
        bool operator!=(const const_iterator& otro){return it != otro.it;}
        /**
         * @brief Operador de igualdad
         * @param otro iterador constante con el que se va a comparar el objeto implícito
         * @return TRUE si apuntan a la misma posición y FALSE si no es así
         */
        bool operator==(const const_iterator& otro){return it == otro.it;}
    };

    /**
     * @brief Devuelve un iterador constante que apunta al comienzo del diccionario
     * @return iterador constante apuntando al principio del set words
     */
    const_iterator begin() const{const_iterator i = words.begin();return i;}

    /**
     * @brief Devuelve un iterador constante que apunta al final del diccionario (posición después de la última)
     * @return iterador constante apuntando al final del set words
     */
    const_iterator end() const{const_iterator i = words.end();return i;}
};

#endif
