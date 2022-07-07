#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <string>
#include <utility>
#include <set>

#include "letters_set.h"
#include "dictionary.h"

using namespace std;

/**
 * @brief Clase Solver
 *
 * @details Esta clase se encarga de construir soluciones para una partida del
 * juego de las letras
 */
class Solver{
private:
  Dictionary dictionary;
  LettersSet letters_set;

public:

  /**
   * @brief Constructor con parámetros
   *
   * Crea un Solver que tiene asociado un Dictionary y un LettersSet
   */
  Solver(const Dictionary & dict, const LettersSet & letters_set);

  /**
   * @brief Construye el vector de soluciones a partir de las letras de una
   * partida
   *
   * @details Dado un conjunto de letras posibles para crear una solución, y el
   * modo de juego con el que se juega la partida, se construye un vector con
   * las mejores soluciones encontradas en función del tipo de juego planteado
   *
   * @param available_letters Vector de letras disponibles para la partida
   * @param score_game Bool indicando el tipo de partida. True indica que la
   * partida se juega a puntuación, false que se juega a longitud
   *
   * @return Par <set<string>, int>, con el conjunto de palabras que
   * constituyen las mejores soluciones (puede haber empates) y la puntuación
   * que obtienen
   */
  pair<set<string>, int> getSolutions(const vector<char> & available_letters, bool score_game);
};

#endif // __SOLVER_H__
