/**
 * @file Event.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */

#include <string>
#include "Event.h"
using namespace std;

Event NULL_EVENT = Event();

Event::Event(){
    
    initDefault();
}

void Event::initDefault(){
    
    setEvent(EVENT_DEFAULT);
}

Event::Event(const string &line){
    
    setEvent(line);
}

DateTime Event::getDateTime() const{
    
    return(_dateTime);
}

string Event::getType() const{
    
    return(_type);
}

string Event::getProductID() const{
    
    return(_prod_id);
}

string Event::getCategoryID() const{
    
    return(_cat_id);
}

string Event::getCategoryCode() const{
    
    return(_cat_cod);
}

string Event::getBrand() const{
    
    return(_brand);
}

double Event::getPrice() const{
    
    return(_price);
}

string Event::getUserID() const{
    
    return(_user_id);
}

string Event::getSession() const{
    
    return(_session);
}

void Event::setDateTime(const string &time){
    
    _dateTime.set(time);
}

void Event::setType(const std::string  &type){
    
    bool is_correct = false;
    
    for(int i = 0; (i < 4) & !is_correct; i++){
        
        if(type == VALID_TYPES[i]){
            is_correct = true;
            _type = type;
        }
    }
    
    if(!is_correct)
        _type = VALID_TYPES[0];
}

void Event::setProductID(const std::string  &prod_id){
    
    if(prod_id == "")
        _prod_id = EMPTY_FIELD;
    
    else
        _prod_id = prod_id;
 }

void Event::setCategoryID(const std::string  &cat_id){
    
    _cat_id = cat_id;
}

void Event::setCategoryCode(const std::string  &cat_cod){
    
    _cat_cod = cat_cod;
}

void Event::setBrand(const std::string  &brand){
    
    _brand = brand;
}

void Event::setPrice(double price){
    
    if(price < 0)
        _price = -1;
    
    else
        _price = price;
}

void Event::setUserID(const std::string  &user_id){
    
    if(user_id == "")
        _user_id = EMPTY_FIELD;
    
    else
        _user_id = user_id;
}

void Event::setSession(const std::string  &session){
    
    if(session == "")
        _session = EMPTY_FIELD;
    
    else
        _session = session;
}

void Event::setEvent(const std::string &line){
    
    string campos_a_rellenar[10];
    int j = 0;
    
    for(int i = 0; i < line.length(); i++){
        
        if(line.at(i) != ',')
            campos_a_rellenar[j].push_back(line.at(i));
        
        else
            j++;
    }
    
    setDateTime(campos_a_rellenar[0]);
    setType(campos_a_rellenar[1]);
    setProductID(campos_a_rellenar[2]);
    setCategoryID(campos_a_rellenar[3]);
    setCategoryCode(campos_a_rellenar[4]);
    setBrand(campos_a_rellenar[5]);
    setPrice(stod(campos_a_rellenar[6]));
    setUserID(campos_a_rellenar[7]);
    setSession(campos_a_rellenar[8]);
}

bool Event::isEmpty() const{
    
    bool is_empty = false;
    
    if((_prod_id == EMPTY_FIELD)||(_user_id == EMPTY_FIELD)||
            (_session == EMPTY_FIELD)||
            (_dateTime.to_string() == DATETIME_DEFAULT)
            || (_price < 0))
        
        is_empty = true;
    
    return(is_empty);
}

string Event::to_string() const {
    string salida;
    salida += _dateTime.to_string();
    salida += "," + _type;
    salida += "," + _prod_id;
    salida += "," + _cat_id;
    salida += "," + _cat_cod;
    salida += "," + _brand;
    salida += "," + std::to_string(_price);
    salida += "," + _user_id;
    salida += "," + _session;
    return salida;
}

std::string Event::getField(const std::string &field) const{
    
    string result = "";
    
    if(field == "DateTime")
        result = _dateTime.to_string();
    else if(field == "Type")
        result = _type;
    else if(field == "ProductID")
        result = _prod_id;
    else if(field == "CategoryID")
        result = _cat_id;
    else if(field == "Brand")
        result = _brand;
    else if(field == "Price")
        result = std::to_string(_price);
    else if(field == "UserID")
        result = _user_id;
    else if(field == "Session")
        result = _session;
    
    return(result);
}