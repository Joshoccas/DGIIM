/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 */


#include <unordered_map>
#include "EventSet.h"

using namespace std;


/**
 * @brief Give string[] and a string, it searches for string within string[]
 * @param array     The set of strings to llok for
 * @param n_array   The size of string[]
 * @param name      The string that is being seeked
 * @return          The position of the first occurrence of string within string[]
 *  -1 if the string does not belong to string[]
 */
int findString(const string array[], int n_array, const string & name){
}

std::string EventSet::to_string() const{
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

EventSet::EventSet(){
    
    _nEvents = 0;
}

int EventSet::size() const{
    
    return(_nEvents);
}


void EventSet::clear(){
    
    _nEvents = 0;
}

int EventSet::add(const Event & e){
    
    int success = 0;
    
    if(_nEvents < MAXEVENT){
        
        _events[_nEvents] = e;
        _nEvents++;
        success = 1;
    }
    
    return(success);
}

int EventSet::add(const std::string& line){
    
    return(add(Event(line)));
}

const Event & EventSet::at(int pos) const{
    
    if((pos >= 0) && (pos < _nEvents))
        return(_events[pos]);
    else
        return(NULL_EVENT);
}


EventSet rawFilterEvents(const EventSet& es, const std::string &field, const std::string &value){
    
    EventSet events;
    
    for(int i = 0; i < es.size(); i++){
        
        if(es.at(i).getField(field) == value)
            events.add(es.at(i));
    }
    
    return(events);
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values){
    
    n_values = 0;
    
    for(int i = 0; i < es.size(); i++){
        
        bool repetido = false;
        
        for(int j = 0; (j < n_values) && !repetido; j++){
            
            if(es.at(i).getField(field) == values[j])
                repetido = true;
        }
        
        if(!repetido){
            values[n_values] = es.at(i).getField(field);
            n_values++;
        }
    }
}

float sumPrice(const EventSet & evSet){
    
    float price = 0;
    
    for(int i = 0; i < evSet.size(); i++)
        price+= evSet.at(i).getPrice();
    
    return(price);
}

