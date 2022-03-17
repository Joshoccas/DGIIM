/* 
 * File:   Pair.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students
 */
#include <string>

#include "Pair.h"

using namespace std;

Pair NULL_PAIR;

Pair::Pair()  {
    initDefault();
}

bool Pair::isEmpty() const {
}

Pair::Pair(const std::string & key, int pos) {
}

const std::string & Pair::getKey() const {
}

const int Pair::getPos() const {
}

void Pair::setKey(const std::string & key) {
}

void Pair::setPos(int pos) {
}

void Pair::set(const std::string & key, int pos) {
 
}

std::string Pair::to_string() const { /** necessary ?*/
    string result;
    result = _key + " " + std::to_string(_pos);
    return result;
}

void Pair::initDefault() {

}

bool equalKey(const Pair & left, const Pair & right) {
}
