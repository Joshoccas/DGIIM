/**
 * @file DateTime.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */

#include <iostream>
#include <sstream>
#include "DateTime.h"
using namespace std;

/**
 * @brief auxiliary function to check if the date and the time are in correct 
 * format, taking into account, leap year etc.
 * @param year input
 * @param month input
 * @param day input
 * @param hour input
 * @param min input
 * @param sec input
 * @return true if is correct, false if not
 */
bool isCorrect(int year, int month, int day, int hour, int min, int sec);
/**
 * @brief split the first field in 6 components of the data time.
 * Please consider using string::substr(int, int)[https://en.cppreference.com/w/cpp/string/basic_string/substr] to cut the line
 * into the appropriate substrings and then convert it into integer values with 
 * the function stoi(string) [https://en.cppreference.com/w/cpp/string/basic_string/stol]
 * ~~~~
 *      YYYY-MM-dd hh:mm:ss UTC 
 *      +----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 *  * @param line input string
 * @param y output int
 * @param m output int
 * @param d output int
 * @param h output int
 * @param mn output int
 * @param s output int
 */
void split(const std::string &line, int &y, int  &m, int  &d, int  &h, int &mn, int &s);

DateTime::DateTime(){
    
    initDefault();
}

void DateTime::initDefault(){
    
    set(DATETIME_DEFAULT);
}


bool isCorrect(int year, int month, int day, int hour, int min, int sec){
    
    bool is_correct = false;
    bool hour_correct = ((hour >= 0) && (hour <= 23)) &&
    ((min >= 0) && (min <= 59)) && ((sec >= 0) && (sec <= 59));
    bool month_correct = ((month > 0) && (month <= 12));
    
    if(hour_correct){
        
        if(month_correct){
            
            if((month == 1)||(month == 3)||(month == 5)||(month == 7)
                    ||(month == 8)||(month == 10)||(month == 12)){
                
                if((day > 0) && (day <= 31))
                    is_correct = true;
            }
            
            else if((month == 4)||(month == 6)||(month == 9)||(month == 11)){
                
                if((day > 0) && (day <= 30))
                    is_correct = true;
            }
            
            else if(month == 2){
                
                if((year%4 == 0)&&((year%100 != 0)||(year%400 != 0))){
                    
                    if((day > 0) && (day <= 29))
                        is_correct = true;
                }
                
                else{
                    
                    if((day > 0) && (day <= 28))
                        is_correct = true;
                }
            }
        }
    }
    
    return(is_correct);
}

void split(const std::string &line, int &y, int  &m, int  &d, int  &h, int &mn, int &s){
    
    try{
        y = stoi(line.substr(0,4));
        m = stoi(line.substr(5,2));
        d = stoi(line.substr(8,2));
        h = stoi(line.substr(11,2));
        mn = stoi(line.substr(14,2));
        s = stoi(line.substr(17,2));
    }
    catch(const std::invalid_argument &e)
    {
        split(DATETIME_DEFAULT, y, m, d, h, mn, s);
    }
}

void DateTime::set(const std::string  &line){
    
    int y, m, d, h, mn, s;
    
    split(line, y, m, d, h, mn, s);
    
    if(isCorrect(y, m, d, h, mn, s)){
        
        _year = y;
        _month = m;
        _day = d;
        _hour = h;
        _min = mn;
        _sec = s;
    }
    
    else
        initDefault();
}


DateTime::DateTime(const std::string  &date){
    
    set(date);
}

int DateTime::year() const{
    
    return(_year);
}

int DateTime::month() const{
    
    return(_month);
}

int DateTime::day() const{
    
    return(_day);
}

int DateTime::hour() const{
    
    return(_hour);
}

int DateTime::min() const{
    
    return(_min);
}

int DateTime::sec() const{
    
    return(_sec);
}

bool DateTime::isBefore(const DateTime  &one) const{
    
    return(to_string() < one.to_string());
}

int DateTime::weekDay() const{
    
    int a = (14 - _month)/12;
    int y = _year - a;
    int m = _month + 12*a - 2;
    
    int day = (_day + y + y/4 - y/100 + y/400 + (31*m)/12) % 7;
    
    return(day);
}

string DateTime::to_string() const {
    
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}