#include <utility>
#include <string>
#include <set>

#include "solver.h"

using namespace std;

Solver::Solver(const Dictionary & dict, const LettersSet & letters_set){
  this->dictionary = dict;
  this->letters_set = letters_set;
}

pair<set<string>, int> Solver::getSolutions(const vector<char> & available_letters,
					    bool score_game){
  set<string> best_results;
  int score = 0;

  auto results = this->dictionary.getPossibleWords(available_letters);

  if (score_game) {
    for (auto word: results) {
      int curr_score = this->letters_set.getScore(word);
      if (curr_score == score) {
	best_results.insert(word);
      } else if (curr_score > score) {
	best_results.clear();
	score = curr_score;
	best_results.insert(word);
      }
    }
  } else {
    for (auto word: results) {
      int curr_score = word.size();
      if (curr_score == score) {
	best_results.insert(word);
      } else if (curr_score > score) {
	best_results.clear();
	score = curr_score;
	best_results.insert(word);
      }
    }
  }
  return pair<set<string>, int> (best_results, score);
}
