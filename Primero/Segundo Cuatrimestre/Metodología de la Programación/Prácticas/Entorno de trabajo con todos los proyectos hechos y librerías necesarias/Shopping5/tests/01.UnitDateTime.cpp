/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string>
#include "DateTime.h"
#include "gtest/gtest.h"
#include "MPTests.h"

using namespace std;

#define TODAY "2021-02-04 16:59:00 UTC"

TEST_F(_01_Basics, DateTime_Constructors) {
    DateTime c;
    SKIP_ASSERT_STREQ_R(c.to_string().c_str(), DATETIME_DEFAULT)<< "A newly create instance of DateTime gives the default date" <<endl;
    std::string date=TODAY;
    DateTime d(date);
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(), date.c_str())<< "A newly created instance of DateTime by using a string gives the same string" <<endl;
}

TEST_F(_01_Basics, DateTime_getters) {
    DateTime c(DATETIME_DEFAULT);
    SKIP_ASSERT_EQ_R(1971, c.year())<<"The year of the default datetime must be 2021"<<endl;
    SKIP_ASSERT_EQ_R(1, c.month())<<"The month of the default datetime must be 1"<<endl;
    SKIP_ASSERT_EQ_R(1,c.day())<<"The day of the default datetime must be 1"<<endl;
    SKIP_ASSERT_EQ_R(0,c.hour())<<"The hour of the default datetime must be 0"<<endl;
    SKIP_ASSERT_EQ_R(0,c.min())<<"The minutes of the default datetime must be 0"<<endl;
    SKIP_ASSERT_EQ_R(0,c.sec())<<"The seconds of the default datetime must be 0"<<endl;    
}

TEST_F(_01_Basics, DateTime_set) {
    DateTime c;
    std::string date=TODAY;
    DateTime d;
    d.set(date);
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(), date.c_str())<< "Setting an instance of DateTime with a valid string gives the same date" << endl;
}

TEST_F(_01_Basics, DateTime_sameDay) {
    DateTime dt1, dt2, dt3;
    std::string date=TODAY;
    dt2.set(date);
    dt3.set(dt1.to_string());
    SKIP_ASSERT_TRUE_R(dt1.sameDay(dt3)) << "Two DateTimes with different initializations give different sameDay" << endl;
    SKIP_ASSERT_FALSE_R(dt1.sameDay(dt2))<< "When a DateTime is used to initialized a seecond DateTime, both must be sameDay"<<endl;
}

TEST_F(_02_Intermediate, DateTime_isBefore) {
    DateTime defaultd;
    std::string date=TODAY;
    DateTime today;
    today.set("2021-02-04 16:59:00 UTC");
    bool what;
    SKIP_ASSERT_FALSE_R(defaultd.isBefore(defaultd)) << "A DateTime cannot be before itself"<<endl;
    SKIP_ASSERT_TRUE_R(defaultd.isBefore(today)) << "Default date is before  today"<<endl;
    SKIP_ASSERT_FALSE_R(today.isBefore(defaultd)) << "Today is not before the  Default date"<<endl;

}

TEST_F(_02_Intermediate, DateTime_weekDay) {
    std::string date=TODAY;
    DateTime d(date);
    SKIP_ASSERT_EQ_R(4, d.weekDay())<< "Today must be Thursday"<<endl;
    date[9]++;
    d.set(date);
    SKIP_ASSERT_EQ_R(5, d.weekDay())<< "Tomorrow is Friday"<<endl;
    date[9]-=2;
    d.set(date);
    SKIP_ASSERT_EQ_R(3, d.weekDay())<< "Yesterday was Wednesday"<<endl;    
}

TEST_F(_03_Advanced, DateTime_BadValues) {
    DateTime d;

    d.set("2021-22-04 18:00:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;

    d.set("2021-02-34 18:00:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;

    d.set("2021-02-04 28:00:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;

    d.set("2021-02-04 18:60:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;
    
    d.set("2021-02-04 18:00:60");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;

    d.set("2021-09-31 18:00:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;

    d.set("2021-04-31 18:00:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;

    d.set("2021-06-31 18:00:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;
    
    d.set("2021-11-31 18:00:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a bad date or time gives the default datetime"<<endl;

    d.set("2021-1-1 18:00:00");
    SKIP_ASSERT_STREQ_R(d.to_string().c_str(),DATETIME_DEFAULT)<<"Setting a date with the incorrect format throws an exception"<<endl;

}    

int main() {
    
    MAIN_BODY() {
    }
    RETURN_MAIN(0);
}
