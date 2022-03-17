/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 */

#include <fstream>
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
    
    _events = nullptr;
    _nEvents = 0;
    _capacity = 0;
}

int EventSet::size() const{
    
    return(_nEvents);
}


void EventSet::clear(){
    
    _nEvents = 0;
}

int EventSet::add(const Event & e){
    
    int success = 1;
    
    if(_capacity != _nEvents){
        
        _events[_nEvents] = e;
        _nEvents++;
    }
    else{
        reallocate(_capacity+1);
        _events[_nEvents] = e;
        _nEvents++;
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
    
    if(field != "DateTime"){
    
        for(int i = 0; i < es.size(); i++){

            if(es.at(i).getField(field) == value)
                events.add(es.at(i));
        }
    
    }
    
    else{
        
        for(int i = 0; i < es.size(); i++){
            
            DateTime fecha(value);
            
            if(fecha.sameDay(es.at(i).getDateTime()))
                events.add((es.at(i)));
        }
    }
    return(events);
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values){
    
    n_values = 0;
    
    
    if(field != "DateTime"){
        
    
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
        
    else{
        
        for(int i = 0; i < es.size(); i++){

            bool repetido = false;
        
            for(int j = 0; (j < n_values) && !repetido; j++){
                
                DateTime fecha(values[j]);

                if(fecha.sameDay(es.at(i).getDateTime()))
                    repetido = true;
            }

            
            if(!repetido){
                
                string fecha = es.at(i).getDateTime().to_string();
                
                fecha.at(11) = '0';
                fecha.at(12) = '0';
                fecha.at(14) = '0';
                fecha.at(15) = '0';
                fecha.at(17) = '0';
                fecha.at(18) = '0';
                
                values[n_values] = fecha;
                n_values++;
            }
        }
    }
}

float sumPrice(const EventSet & evSet){
    
    float price = 0;
    
    for(int i = 0; i < evSet.size(); i++)
        price+= evSet.at(i).getPrice();
    
    return(price);
}

void EventSet::write(ofstream &os) const {
    
    string cadena;
    
    for(int i=0; i < _nEvents; i++)
        cadena += at(i).to_string() + " ";
    
    os << cadena;
}
bool EventSet::read(ifstream &is, int nelements) {
    
    Event e;
    bool res = true;
    
    // Limpiar el EventSet
    
    clear();
    
    for(int i=0; (i < nelements)&&res; i++){
        e.read(is);
    
        if(is){
            add(e);
        } else
            res = false;
    }
    
    
    
    return(res);
}
    
void EventSet::reallocate(unsigned size){
    
    
    while(_capacity < size){
        _capacity = 2*_capacity+1;
    }
    
    Event *aux = new Event[_capacity];
    
    for(int i = 0; i < _nEvents; i++)
        aux[i] = _events[i];
    
    delete[] _events;
    _events = aux;
    aux = nullptr;
}
    
void EventSet::deallocate(){
    
    if(_events != nullptr){
        
        delete[] _events;
        _events = nullptr;
        _capacity = 0;
        _nEvents = 0;
    }
}	
    
void EventSet::copy(const EventSet &orig){
    
    deallocate();
    reallocate(orig.size());
    _nEvents = orig.size();
    
    for(int i = 0; i < _nEvents; i++){
        _events[i] = orig.at(i);
    }
}

EventSet::EventSet(const EventSet &orig){
    
    _events = nullptr;
    _capacity = 0;
    _nEvents = 0;
    
    copy(orig);
}

EventSet::~EventSet(){
    
    deallocate();
}

EventSet & EventSet::operator=(const EventSet & one){
    
    if(&one != this)
        copy(one);
    
    return *this;
}