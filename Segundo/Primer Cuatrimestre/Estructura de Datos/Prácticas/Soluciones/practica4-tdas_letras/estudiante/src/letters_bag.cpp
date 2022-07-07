/**
 * @file letters_bag.cpp
 * @brief Archivo de implementación del TDA LettersBag
 * @authors Ana Graciani Donaire, José Alberto Hoces Castro
 * @date diciembre 2021
 */

#include "letters_bag.h"

LettersBag::LettersBag(const LettersSet & letterSet){
    LettersSet aux = letterSet;
    char letter = 'A';
    while(letter <= 'Z'){
        for(int i = 0; i < aux[letter].repetitions; i++)
            letters.add(letter);
        letter+=1;
    }

}

void LettersBag::insertLetter(const char & l){
    letters.add(l);
}

char LettersBag::extractLetter(){
    return letters.get();
}

vector<char> LettersBag::extractLetters(int num){

    vector<char> result;

    for(int i = 0; i < num; i++)
        result.push_back(extractLetter());

    return result;
}

void LettersBag::clear(){
    letters.clear();
}

unsigned int LettersBag::size() const{
    return letters.size();
}

LettersBag & LettersBag::operator=(const LettersBag & other){
    if(&other != this)
        letters = other.letters;

    return *this;
}