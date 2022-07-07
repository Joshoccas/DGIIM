/**
 * @file letters_bag.h
 * @brief Archivo de especificación del TDA LettersBag
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include "letters_set.h"
#include "bag.h"

#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__

/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

class LettersBag {
private:
    Bag <char> letters;
public:

    /**
     * @brief Constructor dado un LettersSet
     * Dado un LetterSet como argumento, este constructor debe rellenar la LettersBag con las letras que contiene el
     * LettersSet, introduciendo cada letra el número de veces indicado por el campo LetterInfo::repetitions
     * @param letterSet TDA LettersSet a parsear
     */

    LettersBag(const LettersSet & letterSet);

    /**
     * @brief Introduce una letra en la bolsa
     * @param l letra a añadir a la LettersBag
     * @post La bolsa de letras tiene una nueva letra situada al final de su vector de letras miembro
     */

    void insertLetter(const char & l);

    /**
     * @brief Extrae una letra aleatoria de la bolsa, eliminándola del conjunto
     * @return char representa la letra extraída
     * @post La bolsa de letras ya no posee la letra extraída
     */

    char extractLetter();

    /**
     * @brief Extrae un conjunto de letras de la LettersBag, eliminandolas del conjunto
     * @param num Número de letras a extraer
     * @return Lista con las letras extraídas aleatoriamente
     * @post La bolsa de letras ya no posee las letras que componen la lista devuelta
     */

    vector<char> extractLetters(int num);

    /**
     * @brief Vacía la LettersBag
     * Elimina todo el contenido de la LettersBag
     * @post La LettersBag queda vacía
     */

    void clear();

    /**
     * @brief Tamaño de la bolsa
     * @return int con el tamaño de la bolsa
     */

    unsigned int size() const;

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other LettersBag a copiar
     * @return Referencia a this de esta forma el operador puede ser encadenado
     * @post La LettersBag sobre la que se usa es idéntica a la pasada como parámetro
     */

    LettersBag & operator=(const LettersBag & other);


};

#endif
