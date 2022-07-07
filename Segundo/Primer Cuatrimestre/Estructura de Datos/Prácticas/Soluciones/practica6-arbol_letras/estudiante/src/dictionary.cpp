//
// Created by fluque1995 on 8/9/21.
//

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

std::list<std::string>
Dictionary::wordsByDepth(int remaining_levels, Dictionary::node current_node, std::string current_word) {
  std::list<std::string> result;

  if (current_node.is_null()){
    return result;
  }
  if (remaining_levels == 0 && (*current_node).valid_word) {
    result.push_back(current_word);

  } else if (remaining_levels > 0) {
    current_node = current_node.left_child();

    while (!current_node.is_null()){
      std::list<std::string> current_result = this->wordsByDepth(remaining_levels - 1,
								 current_node,
								 current_word + (*current_node).character);
      // This method appends a list at the end of another one
      result.splice(result.end(), current_result);
      current_node = current_node.right_sibling();
    }
  }

  return result;
}

std::list<std::string> Dictionary::getCoincidentWords(std::multiset<char> &characters,
						      Dictionary::node current_node,
                                                      std::string current_word) {
  std::list <std::string> result;

  if (current_node.is_null()){
    return result;
  }
  if ((*current_node).valid_word){
    result.push_back(current_word);
  }
  current_node = current_node.left_child();

  while (!current_node.is_null()){
    std::multiset<char>::iterator curr_char_it = characters.find((*current_node).character);
    if (curr_char_it != characters.end()){
      char curr_char = *curr_char_it;
      characters.erase(curr_char_it);
      std::list<std::string> current_result = this->getCoincidentWords(
								       characters,
								       current_node,
								       current_word + curr_char);
      result.splice(result.end(), current_result);
      characters.insert(curr_char);
    }
    current_node = current_node.right_sibling();
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

std::vector<std::string> Dictionary::wordsOfLength(int length) {
  std::list<std::string> words = this->wordsByDepth(
						    length,
						    this->words.get_root(),
						    std::string());
  return std::vector<std::string>(words.begin(), words.end());
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->findLowerBoundChildNode(word[i], current);
    if ((*current).character != word[i]) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (int i = 0; i < val.size(); ++i){
    current = this->findLowerBoundChildNode(val[i], current);
    if ((*current).character != val[i]) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    return true;
  }
  return false;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }
  (*current).valid_word = true;

  return true;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
  }
  return *this;
}

std::vector <std::string> Dictionary::getPossibleWords(std::vector<char> available_characters){
  std::multiset<char> chars;
  for (auto letter: available_characters){
    chars.insert(tolower(letter));
  }
  std::list<std::string> words = getCoincidentWords(chars,
						    this->words.get_root(),
						    std::string());
  return std::vector<std::string> {words.begin(), words.end()};
}


///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}

std::istream& operator>>(std::istream &is, Dictionary &dict){
  std::string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                      Letters Occurrences and usages                       //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){
}

int Dictionary::getTotalUsages(const char c){
}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){
}

int Dictionary::getTotalLetters(){return this->words.size();}


///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

void Dictionary::iterator::nextWord(){
}

Dictionary::iterator::iterator() {}

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter) {
}

std::string Dictionary::iterator::operator*() {
}

Dictionary::iterator &Dictionary::iterator::operator++() {
}

bool Dictionary::iterator::operator==(const iterator &other) {
}

bool Dictionary::iterator::operator!=(const iterator &other) {
}

Dictionary::iterator Dictionary::begin() const {
}

Dictionary::iterator Dictionary::end() const {
}
