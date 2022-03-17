/* 
 * File:   Index.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */
#include <string>
#include <iostream>
#include <fstream>
#include "Index.h"

using namespace std;

Index::Index()  {
}

Index::Index(int onBrand) {
}

void Index::setIOnWhich(int val) {
}

int Index::size() const {
}

void Index::clear() {
}

int Index::getIOnWhich() const {
}

int Index::add(const Pair & pair) {
}

void Index::build(const EventSet & evSet, int onBrand) {
}

int Index::lower_bound(const string & key) const {
}

int Index::upper_bound(const string & key) const {
}

const Pair & Index::at(int pos) const {
}

Pair & Index::at(int pos) {
}

void Index::print()const {
}

Event getEvent(const EventSet & evSet, const Index & indx, int pos) {
}

void write(ofstream &os, const EventSet & evSet, const Index & indx) {
}

Index rawFilterIndex(const EventSet & evSet, const Index & indx, const std::string &field, const std::string &value) {
}

float sumPrice(const EventSet & evSet, const Index & indx) {
}