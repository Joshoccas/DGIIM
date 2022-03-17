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
    
    _onBrand = 0;
    _nEntries = 0;
}

Index::Index(int onBrand) {
    
    setIOnWhich(onBrand);
    _nEntries = 0;
}

void Index::setIOnWhich(int val) {
    
    _onBrand = val;
}

int Index::size() const {
    
    return(_nEntries);
}

void Index::clear() {
    
    _nEntries = 0;
}

int Index::getIOnWhich() const {
    
    return(_onBrand);
}

int Index::add(const Pair & pair) {
    
    int success = 0;
    
    if((!pair.isEmpty())&&(_nEntries < MAXEVENT)){
        
        success = 1;
        
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
}

int Index::lower_bound(const string & key) const {
    
    bool sigo = true;
    int pos = 0;
    
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