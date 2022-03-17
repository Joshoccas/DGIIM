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
    
    _entries = nullptr;
    _onBrand = 0;
    _nEntries = 0;
    _capacity = 0;
}

Index::Index(int onBrand) {
    
    _entries = nullptr;
    setIOnWhich(onBrand);
    _nEntries = 0;
    _capacity = 0;
}

void Index::setIOnWhich(int val) {
    
    _onBrand = val;
}

int Index::size() const {
    
    return(_nEntries);
}

void Index::clear() {
    
    deallocate();
}

int Index::getIOnWhich() const {
    
    return(_onBrand);
}

int Index::add(const Pair & pair) {
    
    int success = 1;
    
    if((!pair.isEmpty())&&(_capacity != _nEntries)){
        
        int pos = upper_bound(pair.getKey());
        
        for(int i=_nEntries; i > pos; i--){
            
            _entries[i]=_entries[i-1];
        }
        
        _entries[pos] = pair;
        _nEntries++;
    }
    else if((!pair.isEmpty())&&(_capacity == _nEntries)){
        
        reallocate(_capacity+1);
        
        int pos = upper_bound(pair.getKey());
        
        for(int i=_nEntries; i > pos; i--){
            
            _entries[i]=_entries[i-1];
        }
        
        _entries[pos] = pair;
        _nEntries++;
    }
    
    return(success);
}

void Index::build(const EventSet & evSet, int onBrand) {
    
    clear();
    setIOnWhich(onBrand);
    
    if(_onBrand == 0){
        
        for(int i=0; i < evSet.size(); i++){
            
            if(evSet.at(i).getUserID() != ""){
                Pair to_add(evSet.at(i).getUserID(),i);
                add(to_add);
            }
        }
    }
    
    else if(_onBrand == 1){
        for(int i=0; i < evSet.size(); i++){
            
            if(evSet.at(i).getBrand() != ""){
                Pair to_add(evSet.at(i).getBrand(),i);
                add(to_add);
            }                
        }
    }
    
    else if(_onBrand == 2){
        for(int i=0; i < evSet.size(); i++){
            
            if(evSet.at(i).getSession() != ""){
                Pair to_add(evSet.at(i).getSession(),i);
                add(to_add);
            }                
        }
    }
}

int Index::lower_bound(const string & key) const {
    
    bool sigo = true;
    int pos = _nEntries;
    
    for(int i=0; (i < _nEntries) && sigo; i++){
        
        if(_entries[i].getKey() >= key){
            pos = i;
            sigo = false;
        }
    }
    
    return(pos);
}

int Index::upper_bound(const string & key) const {
    
    bool sigo = true;
    int pos = _nEntries;
    
    for(int i=0; (i < _nEntries) && sigo; i++){
        
        if(_entries[i].getKey() > key){
            pos = i;
            sigo = false;
        }
    }
    
    return(pos);
}

const Pair & Index::at(int pos) const {
    
    return(_entries[pos]);
}

Pair & Index::at(int pos) {
    
    return(_entries[pos]);
}

void Index::print()const {
}

Event getEvent(const EventSet & evSet, const Index & indx, int pos) {
    
    return(evSet.at(indx.at(pos).getPos()));
}

void write(ofstream &os, const EventSet & evSet, const Index & indx) {
    
    for(int i=0;i < indx.size(); i++){
        os << getEvent(evSet, indx, i).to_string();
    }
}

Index rawFilterIndex(const EventSet & evSet, const Index & indx, const std::string &field, const std::string &value) {
    
    Index subindex(indx.getIOnWhich());
    
    for(int i = 0; i < indx.size(); i++){
        
        if(evSet.at(indx.at(i).getPos()).getField(field) == value)
            subindex.add(indx.at(i));
    }
    
    return(subindex);
}

float sumPrice(const EventSet & evSet, const Index & indx) {
    
    float price = 0;
    
    for(int i = 0; i < indx.size(); i++)
        price+= getEvent(evSet, indx, i).getPrice();
    
    return(price);
}

void Index::reallocate(unsigned size){
    
    if(_capacity < size){
        
        while(_capacity < size){
        _capacity = 2*_capacity+1;
        }
    
        Pair *aux = new Pair[_capacity];

        for(int i = 0; i < _nEntries; i++)
            aux[i] = _entries[i];

        delete[] _entries;
        _entries = aux;
        aux = nullptr;
    }
}
void Index::deallocate(){
    
    if(_entries != nullptr){
        
        delete[] _entries;
        _entries = nullptr;
        _nEntries = 0;
        _capacity = 0;
        _onBrand = 0;
    }
}
void Index::copy(const Index &orig){
    
    deallocate();
    reallocate(orig.size());
    _nEntries = orig.size();
    _onBrand = orig.getIOnWhich();
    
    for(int i = 0; i < _nEntries; i++){
        _entries[i] = orig.at(i);
    }
}

Index::Index(const Index &orig){
    
    _entries = nullptr;
    _capacity = 0;
    _nEntries = 0;
    _onBrand = 0;
    
    copy(orig);
}

Index::~Index(){
    
    deallocate();
}

Index & Index::operator=(const Index & one){
    
    if(&one != this)
        copy(one);
    
    return *this;
}