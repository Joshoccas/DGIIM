/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string>
#include "DateTime.h"
#include "Event.h"
#include "gtest/gtest.h"
#include "MPTests.h"

using namespace std;

#define TODAY "2021-02-04 16:59:00 UTC"
#define ANYEVENT "2021-02-04 17:57:00 UTC,view,1,2,3,4,5.000000,6,7"

TEST_F(_01_Basics, Event_ConstructorBase) {
    Event e;
    SKIP_ASSERT_STREQ_R(e.to_string().c_str(), EVENT_DEFAULT.c_str())<< "A newly created instance of Event gives the default event"<<endl;
    ASSERT_TRUE(e.isEmpty()) << "A newly created instance of Event is consdered empty"<<endl;
    Event e2(ANYEVENT);
    SKIP_ASSERT_STREQ_R(e2.to_string().c_str(),ANYEVENT)<< "A newly create instance of Event, initializaed with a string. gives the same string"<<endl;
    ASSERT_FALSE(e2.isEmpty()) << "Setting the productid of an event to a good value X gives X"<<endl;
}

TEST_F(_01_Basics, Event_Setters_getters) {
    Event e;
    std::string es=EVENT_DEFAULT;
    
    e.setDateTime(TODAY);
    SKIP_ASSERT_STREQ_R(e.getDateTime().to_string().c_str(),TODAY) << "Setting the datetime of an event to TODAY gives TODAY"<<endl;

    std::string s="purchase";
    e.setType(s);
    SKIP_ASSERT_STREQ_R(e.getType().c_str(),s.c_str()) << "Setting the type of an event to a good value X gives X"<<endl;
    
    s="CCCC";
    e.setProductID(s);
    SKIP_ASSERT_STREQ_R(e.getProductID().c_str(),s.c_str()) << "Setting the productid of an event to a good value X gives X"<<endl;
    
    s="CCCC";
    e.setCategoryID(s);
    SKIP_ASSERT_STREQ_R(e.getCategoryID().c_str(),s.c_str()) << "Setting the categoryID of an event to a good value X gives X"<<endl;
    
    s="CCCC";
    e.setCategoryCode(s);
    SKIP_ASSERT_STREQ_R(e.getCategoryCode().c_str(),s.c_str()) << "Setting the category code of an event to a good value X gives X"<<endl;
    
    
    s="CCCC";
    e.setBrand(s);
    SKIP_ASSERT_STREQ_R(e.getBrand().c_str(),s.c_str()) << "Setting the brand of an event to a good value X gives X"<<endl;
    
    double d=3.1415;
    e.setPrice(d);
    SKIP_ASSERT_EQ_R(e.getPrice(),d) << "Setting the price of an event to a good value X gives X"<<endl;
    
}    
    
TEST_F(_02_Intermediate, Event_getField) {
    Event e;
    SKIP_ASSERT_STREQ_R(e.getDateTime().to_string().c_str(),e.getField("DateTime").c_str())<<"getField(\"DateTime\") on any Event, must be equal to getDateTime()" << endl;
    SKIP_ASSERT_STREQ_R("-1.000000", e.getField("Price").c_str())<< "In any row, querying the Event for field \"Price\" will produce the same string than getDateTime"<<endl;
    SKIP_ASSERT_STREQ_R(EMPTY_FIELD, e.getField("UserID").c_str())<< "In any case, querying the Event for field \"UserID\" will produce the same string than the former getUserID()"<<endl;
    SKIP_ASSERT_STRNE_R("", e.getField("UserID").c_str())<< "In any row, querying the EventS a mandatory field cannot give an empty string"<<endl;
    SKIP_ASSERT_STREQ_R("", e.getField("Brand").c_str())<< "In any row, querying  an optional field will produce the same string than the former event added to the EvenSet"<<endl;
}

TEST_F(_03_Advanced, Event_setType_Bad_Values) {
    Event e(ANYEVENT);
    std::string es=EVENT_DEFAULT;
    
    std::string s="CCCC";
    e.setType(s);
    SKIP_ASSERT_STREQ_R("view", e.getType().c_str()) << "Setting the type of an event to a good value X gives X"<<endl;
    SKIP_ASSERT_FALSE_R(e.isEmpty()) << "Setting the type of an event to a good value X gives X"<<endl;
    
    
}    
TEST_F(_03_Advanced, Event_Others_Bad_Values) {
    Event e(ANYEVENT);
    std::string es=EVENT_DEFAULT,s;
      
    s="";
    e.setProductID(s);
    SKIP_ASSERT_STREQ_R(e.getProductID().c_str(),EMPTY_FIELD) << "Setting the productid of an event to a good value X gives X"<<endl;
    SKIP_ASSERT_TRUE_R(e.isEmpty()) << "Setting the productid of an event to a good value X gives X"<<endl;
    
    double d=-3.1415;
    e.setPrice(d);
    SKIP_ASSERT_EQ_R(e.getPrice(),-1) << "Setting the productid of an event to a good value X gives X"<<endl;
    
}    

