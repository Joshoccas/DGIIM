/**
 * @file letters_set.cpp
 * @brief Archivo de implementación del TDA LettersSet
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include "letters_set.h"

LettersSet::LettersSet(){
    clear();
}

LettersSet::LettersSet(const LettersSet & other){
    letters = other.letters;
}

bool LettersSet::insert(const pair<char,LetterInfo> & val){
    return letters.insert(val).second;
}

bool LettersSet::erase(const char & key){
    return letters.erase(key);
}

void LettersSet::clear(){
    letters.clear();
}

bool LettersSet::empty() const{
    return letters.empty();
}

unsigned int LettersSet::size() const{
    return letters.size();
}

int LettersSet::getScore(string word){

    int score = 0;

    for(int i = 0; i < word.length(); i++){

        score+=letters.find(toupper(word.at(i)))->second.score;
    }

    return score;
}

LettersSet & LettersSet::operator=(const LettersSet & cl){
    if(&cl != this)
        letters = cl.letters;

    return *this;
}

LetterInfo & LettersSet::operator[](const char & val){

    return letters[val];
}

ostream & operator <<(ostream & os, const LettersSet & cl){

    cout << "Letra " << "Cantidad " << "Puntos";

    map<char,LetterInfo>::const_iterator it;

    for(it = cl.letters.begin(); it != cl.letters.end(); ++it) {
        cout << it->first << "\t" << it->second.repetitions  << "\t" << it->second.score;
        cout << endl;
    }

    return os;
}

istream & operator >>(istream & is, LettersSet & cl){

    string cad;
    getline(is,cad);
    LetterInfo aux;
    char letra;

    while(is){
        is >> letra;
        is >> aux.repetitions;
        is >> aux.score;
        pair<char,LetterInfo> pair(letra,aux);
        cl.insert(pair);
    }

    return is;
}