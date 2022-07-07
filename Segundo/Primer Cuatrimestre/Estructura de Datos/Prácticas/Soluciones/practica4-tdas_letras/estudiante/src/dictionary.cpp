/**
 * @file dictionary.cpp
 * @brief Archivo de implementación del TDA Dictionary
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include "dictionary.h"

Dictionary::Dictionary(){
    clear();
}

Dictionary::Dictionary(const Dictionary & other){
    words = other.words;
}

bool Dictionary::exists(const string & val) const{
    bool exists = false;
    Dictionary::const_iterator it;

    for(it = begin(); (it != end()) && !exists; ++it){
        if(*it == val)
            exists = true;
    }

    return exists;
}

bool Dictionary::insert(const string &val){
    return words.insert(val).second;
}

bool Dictionary::erase(const string &val){
    return words.erase(val);
}

void Dictionary::clear(){
    words.clear();
}

bool Dictionary::empty() const{
    return words.empty();
}

unsigned int Dictionary::size() const{
    return words.size();
}

int Dictionary::getOcurrences(const char c){
    int ocurrences = 0;
    Dictionary::iterator it;

    for(it = begin(); it != end(); ++it){
        for(int j = 0; j < (*it).length(); j++){
            if((*it).at(j) == tolower(c))
                ocurrences++;
        }
    }

    return ocurrences;
}

int Dictionary::getTotalLetters(){
    Dictionary::iterator it;
    int totalletters = 0;

    for(it = begin(); it != end(); ++it){
        totalletters += (*it).length();
    }

    return totalletters;
}

vector<string> Dictionary::wordsOfLength(int length){
    vector<string> result;

    Dictionary::iterator it;

    for(it = begin(); it != end(); ++it){
        if((*it).length() == length)
            result.push_back(*it);
    }

    return result;
}