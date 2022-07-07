//
// Created by fluque1995 on 8/9/21.
//

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <map>
#include <set>

using namespace std;

class Dictionary {
private:
  /**
   * @brief Struct to represent a character inside the tree.
   *
   * The struct contains information about the character it that node, and
   * information marking if a valid word of the dictionary finishes in
   * that character
   */
  struct char_info {
    char character;
    bool valid_word;

    /**
     * Default constructor
     */
    inline char_info() : character(0), valid_word(false) {}

    /**
     * @brief Parameters constructor
     *
     * @param character Character to be inserted
     * @param valid Marker for word validity
     */
    inline char_info(char character, bool valid=false) : character(character), valid_word(valid) {}
    inline bool operator==(const char_info &rhs) {
      return this->character == rhs.character && this->valid_word == rhs.valid_word;
    }
    inline bool operator!=(const char_info &rhs) { return !(*this == rhs); }
    inline bool operator*() { return this->character; }
    inline friend std::ostream &operator<<(std::ostream &os, const char_info& other){
      os << other.character << (other.valid_word ? "✓" : "×");
      return os;
    }
  };

  tree<char_info> words;
  typedef tree<char_info>::node node;

  /**
   * @brief Find the lower bound of a character among the children of the current node
   *
   * If the character exists among the children of the current node, that node is returned. If not,
   * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
   * than the searched one
   *
   * @param character Character to be found
   * @param current Reference node, the one whose children are going to be explored
   * @return Lower bound node for the seeked character
   */
  node findLowerBoundChildNode(char character, node current);

  /**
   * @brief Insert character as children of the current node
   *
   * This method tries to insert a new character in the tree, as a child of the current node.
   * If there already exists a node with that character, instead of inserting a new node, the
   * already existing node with the character is returned
   *
   * @param character Character to be inserted
   * @param current Reference node, the one that will be parent of the new inserted node
   * @return Node corresponding to the inserted character
   */
  node insertCharacter(char character, node current);

  /**
   * @brief Find words up to a certain depth
   *
   * Helper method to implement the recursively search of words given a length. It searches
   * for all the possible words formed using the current_word as prefix, continuing in the
   * current_node, of remaining length given by remaining_levels
   *
   * @param remaining_levels The remaining depth we have to find
   * @param current_node Node we are currently visiting, where we continue the search
   * @param current_word Prefix added to subsequent characters to form valid words
   * @return List of words at the desired depth
   */
  std::list<std::string> wordsByDepth(int remaining_levels, node current_node, std::string current_word);

  /**
   * @brief Find words that can be formed with the remaining characters
   *
   * @param characters Remaining characters that can be used to form words
   * @param current_node Current node, where the search continues
   * @param current_word Prefix added to found characters to form valid words
   * @return List of words that can be formed with the specified characters
   */
  std::list<std::string> getCoincidentWords(std::multiset<char> &characters,
					    node current_node,
					    std::string current_word);

  std::pair<int, int> getTotalUsages(node curr_node, char c);
public:

  /**
   * @brief Constructor por defecto
   *
   * Crea un Dictionary vacío
   */
  Dictionary();

  /**
   * @brief Constructor de copia
   *
   * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
   *
   * @param other Dictionary que se quiere copiar
   */
  Dictionary(const Dictionary& other);

  /**
   * @brief Destructor
   *
   * Limpia todos los elementos del Dictionary antes de borrarlo
   */
  ~Dictionary();

  /**
   *  \brief Limpia el Dictionary
   *
   *  Elimina todas las palabras contenidas en el conjunto
   */
  void clear() {this->words.clear();}

  /**
   * @brief Tamaño del diccionario
   *
   * @return Número de palabras guardadas en el diccionario
   */
  unsigned int size()const{return words.size();}

  /**
   * @brief Devuelve las palabras en el diccionario con una longitud dada
   * @param length Longitud de las palabras buscadas
   * @return Vector de palabras con la longitud desdeada
   */
  vector<string> wordsOfLength(int length);

  /**
   * @brief Indica si una palabra esta en el diccionario o no.
   *
   * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
   *
   * @param palabra: la palabra que se quiere buscar.
   * @return Booleano indicando si la palabra existe o no en el diccionario
   */
  bool exists(const string& val);

  /**
   * @brief Indica el numero de apariciones de una letra.
   *
   * Se define el número de apariciones de una letra como el número de nodos
   * del árbol en el que esa letra está repetida.
   *
   * @param c letra a buscar.
   * @return Un entero indicando el numero de apariciones.
   */
  int getOccurrences(const char c);

  /**
   * @brief Indica el numero de utilizaciones de una letra.
   *
   * Se define el número de utilizaciones de una letra como el número de veces
   * que se utiliza para formar palabras. Es decir, si un prefijo se utiliza
   * para formar dos palabras, las letras de ese prefijo se contarán dos veces
   * en este método.
   *
   * @param c letra a buscar.
   * @return Un entero indicando el numero de utilizaciones.
   */
  int getTotalUsages(const char c);

  /**
   * @brief Cuenta el total de letras de un diccionario.
   * @return Entero con el total de letras.
   */
  int getTotalLetters();

  /**
   * @brief Comprueba si el diccionario está vacio.
   * @return true si el diccionario está vacío, false en caso contrario
   */
  bool empty()const{return words.empty();}

  /**
   * @brief Elimina una palabra del diccionario
   *
   * @param val Palabra a borrar del diccionario
   *
   * @return Booleano que indica si la palabra se ha borrado del diccionario
   */
  bool erase(const string &val);

  /**
   * @brief Inserta una palabra en el diccionario
   *
   * @param val palaba a insertar en el diccionario
   * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
   * con éxito si no existía previamente en el diccionario
   */
  bool insert(const string &val);

  /**
   * @brief Sobrecarga del operador de asignación
   */
  Dictionary& operator=(const Dictionary &dic);

  /**
   * @brief Sobrecarga del operador de entrada
   *
   * Permite leer las palabras de un fichero de texto e introducirlas en el
   * diccionario
   *
   * @param is Flujo de entrada
   * @param dic Diccionario a rellenar
   * @return Flujo de entrada para poder encadenar el operador
   */
  friend istream& operator>>(istream &is, Dictionary &dic);

  /**
   * @brief Sobrecarga del operador de salida
   *
   * Permite imprimir el diccionario completo a un flujo de salida
   *
   * @param os Flujo de salida, donde imprimir el diccionario
   * @param dic Diccionario a imprimir
   * @return Flujo de salida, para poder encadenar el operador
   */
  friend ostream& operator<<(ostream &os, const Dictionary &dic);

  /**
   * @brief Recupera las palabras del Dictionary que se pueden formar con un
   * conjunto de letras
   *
   * @param available_characters Conjunto de caracteres disponibles para formar
   * palabras
   */
  vector<string> getPossibleWords(vector<char> available_characters);

  /**
   * @brief Iterator over the dictionary. It allows to retrieve all the stored words
   * in alphabetical order (it coincides with the preorder traversal of the tree)
   */
  class iterator {
  private:
    std::string curr_word;
    tree<char_info>::const_preorder_iterator iter;

    void nextWord();
  public:

    /**
     * @brief Default constructor
     */
    iterator();

    /**
     * @brief Constructor given a tree preorder iterator
     *
     * @param iter Iterator from tree where our iterator will be pointed
     */
    iterator(tree<char_info>::const_preorder_iterator iter);

    /**
     * @brief Reference operator overload
     *
     * @return Current word pointed by the iterator
     */
    std::string operator*();

    /**
     * @brief Advance iterator overload
     *
     * @return Iterator pointing to the following word
     */
    iterator &operator++();

    /**
     * @brief Comparison of equality operator overload
     *
     * @param other Iterator to compare against
     * @return true if boths iterators are equal, false otherwise
     */
    bool operator==(const iterator &other);

    /**
     * @brief Comparison of inequality operator overload
     *
     * @param other Tterator to compare against
     * @return true if iterators are different, false otherwise
     */
    bool operator!=(const iterator &other);

    friend class Dictionary;
  };

  /**
   * @brief Iterator pointing to the first word in the dictionary
   */
  iterator begin() const;

  /**
   * @brief Iterator pointing to the end of the dictionary
   */
  iterator end() const;
};

#endif //TREE_DICTIONARY_HPP
