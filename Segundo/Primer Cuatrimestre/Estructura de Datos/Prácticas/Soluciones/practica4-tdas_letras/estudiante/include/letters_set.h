/**
 * @file letters_set.h
 * @brief Archivo de especificación del TDA LettersSet
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include<iostream>
#include<tuple>
#include<map>
#include<string>
using namespace std;

#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

struct LetterInfo {
    int repetitions;
    int score;
};

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */

class LettersSet{

private:

    map <char,LetterInfo> letters;
public:

    /**
     * @brief Constructor por defecto
     * Crea un LettersSet vacío
     */

    LettersSet();

    /**
     * @brief Constructor de copia
     * @param other LettersSet a copiar
     */

    LettersSet(const LettersSet & other);

    /**
     * @brief Inserta un elemento en el LettersSet
     * @param val Pareja de letra y LetterInfo asociada a insertar
     * @return Booleano que marca si se ha podido insertar la letra en el LettersSet. La letra sólo se inserta
     * correctamente si no estaba aún incluída en la colección
     */

    bool insert(const pair<char,LetterInfo> & val);

    /**
     * @brief Elimina un elemento del LettersSet
     * @param key Carácter a eliminar
     * @return Booleano que indica si se ha podido eliminar correctamente la letra del LettersSet
     */

    bool erase(const char & key);

    /**
     * @brief Limpia el contenido del LettersSet
     * @post Los elementos del LettersSet han sido eliminados
     */
    void clear();

    /**
     * @brief Consulta si el LettersSet es vacío
     * @return true si el LettersSet está vacío, falso en caso contrario
     */

    bool empty() const;

    /**
     * @brief Tamaño del LettersSet
     * @return Número de elementos en el LettersSet
     */
    unsigned int size() const;

    /**
     * @brief Calcula la puntuación dada una palabra
     * @param word String con la palabra cuya puntuación queremos calcular
     * @return Puntuación de la palabra, calculada como la suma de las puntuaciones de cada una de sus letras
     */
    int getScore(string word);

    /**
     * @brief Sobrecarga del operador de asignación
     * @param cl LettersSet a copiar
     * @return Referencia al objeto this para poder encadenar el operador
     * @post El LettersSet sobre el que se usa es idéntico al pasado como parámetro
     */
    LettersSet & operator=(const LettersSet & cl);

    /**
     * @brief Sobrecarga del operador de consulta
     * @param val Carácter a consultar
     * @return Estructura de tipo LetterInfo con la información del carácter consultado: Número de repeticiones
     * y puntuación
     */

    LetterInfo & operator[](const char & val);

    /**
     * @brief Sobrecarga del operador de salida
     * @param os Flujo de salida, donde escribir el LettersSet
     * @param cl LettersSet que se escribe
     * @return Flujo de salida con los datos escritos
     */

    friend ostream & operator <<(ostream & os, const LettersSet & cl);

    /**
     * @brief Sobrecarga del operador de entrada
     * @param is Flujo de entrada, del que leer el LettersSet
     * @param cl LettersSet en el que almacenar la información leída
     * @return Flujo de entrada vacío
     */

    friend istream & operator >>(istream & is, LettersSet & cl);
};

ostream & operator <<(ostream & os, const LettersSet & cl);

istream & operator >>(istream & is, LettersSet & cl);

#endif
