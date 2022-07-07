ç#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dictionary.h"
#include "letters_bag.h"
#include "letters_set.h"
#include "solver.h"

using namespace std;

int main(int argc, char *argv[])
{
  srand(time(NULL));
  if(argc != 5){
    cerr << "Número de parámetros incorrecto. Los parametros son: " << endl;
    cerr << "1.- El fichero con las letras" << endl;
    cerr << "2.- El fichero con el diccionario" << endl;
    cerr << "3.- Tipo de puntuación usada en la partida (L para longitud, P para puntuación)" << endl;
    cerr << "4.- El número de letras que se utilizarán en la partida" << endl;
    return 1;
  }

  ifstream letters_file(argv[1]);
  ifstream dict_file(argv[2]);

  int n_letters = atoi(argv[4]);
  bool score_game;
  if (argv[3][0] == 'L') {
    score_game = false;
  } else if (argv[3][0] == 'P') {
    score_game = true;
  } else {
    cerr << "El parámetro asociado al tipo de juego puede tomar los valores L o C, se ha recibido ";
    cerr << argv[3] << endl;
    return 1;
  }

  if(!letters_file){
    cerr << "No puedo abrir el fichero " << argv[1] << endl;
    return 0;
  }

  if(!dict_file){
    cerr << "No puedo abrir el fichero " << argv[2] << endl;
    return 0;
  }

  Dictionary dictionary;
  dict_file >> dictionary;

  LettersSet letters_set;
  letters_file >> letters_set;

  LettersBag letters_bag(letters_set);

  Solver solver(dictionary, letters_set);

  vector<char> letters = letters_bag.extractLetters(n_letters);

  cout << "LETRAS DISPONIBLES: " << endl;
  for (auto letter: letters){
    cout << (char) letter << " " ;
  }
  cout << endl;
  auto solutions = solver.getSolutions(letters, score_game);

  cout << "SOLUCIONES:" << endl;
  for (auto word: solutions.first){
    cout << word << endl;
  }

  cout << "PUNTUACION:" << endl << solutions.second << endl;

  return 0;
}
