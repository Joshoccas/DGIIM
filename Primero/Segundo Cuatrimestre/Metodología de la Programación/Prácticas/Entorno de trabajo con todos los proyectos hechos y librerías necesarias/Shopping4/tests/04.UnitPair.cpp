#include <string>
#include "Pair.h"
#include "gtest/gtest.h"
#include "MPTests.h"

using namespace std;

TEST_F(_01_Basics, Pair_Constructors) {
    Pair p;
    SKIP_ASSERT_STREQ_R("00000000 -1",p.to_string().c_str()) << "After the creation of a new instance of Pair, it shows its default value"<<endl;

    string s="test", res;
    int i=13;
    Pair pp(s,i);
    res = s+" "+std::to_string(i);
    SKIP_ASSERT_STREQ_R(res.c_str(),pp.to_string().c_str()) << "After the creation of a new instance of Pair by using a string and an int, it shows these two same values"<<endl;
    Pair ppp(s);
    res = s+" "+std::to_string(-1);
    SKIP_ASSERT_STREQ_R(res.c_str(),ppp.to_string().c_str()) << "After the creation of a new instance of Pair by using a string and NO int, it shows the string and -1 default value"<<endl;
}

TEST_F(_01_Basics, Pair_isEmpty) {
    Pair p;
    SKIP_ASSERT_TRUE_R(p.isEmpty())<< "Any newly created instance of Pair, without specifying any arguments, is considered to be empty" << endl;
    p.set("AA",0);
    SKIP_ASSERT_FALSE_R(p.isEmpty())<< "Any instance of Pair with valid key and pos, could not be considered empty" << endl;
}



TEST_F(_01_Basics, Pair_setters) {
    string s="test", res;
    int i=13;
    Pair pp;
    pp.set(s,i);
    res = s+" "+std::to_string(i);
    SKIP_ASSERT_STREQ_R(res.c_str(),pp.to_string().c_str()) << "After the creation of a new instance of Pair and setting it by using a string and an int, it shows these two same values"<<endl;
    s = "newtest";
    pp.setKey(s);
    res = s+" "+std::to_string(i);
    SKIP_ASSERT_STREQ_R(res.c_str(),pp.to_string().c_str()) << "After the creation of a new instance of Pair and setting the key to a given string, it shows this same string"<<endl;
    i = 1000;
    res = s+" "+std::to_string(i);
    pp.setPos(i);
    SKIP_ASSERT_STREQ_R(res.c_str(),pp.to_string().c_str()) << "After the creation of a new instance of Pair and setting the value to a given number, it shows this same number"<<endl;
}

TEST_F(_01_Basics, Pair_getters) {
    string s="test", res;
    int i=13;
    Pair pp;
    pp.set(s,i);
    SKIP_ASSERT_STREQ_R(s.c_str(),pp.getKey().c_str()) << "After the creation of a new instance of Pair and setting it by using a string and an int, getKey() returns the same string"<<endl;
    SKIP_ASSERT_EQ_R(i,pp.getPos()) << "After the creation of a new instance of Pair and setting it by using a string and an int, getPost() resturns the same integer"<<endl;
    s = "newtest";
    pp.setKey(s);
    SKIP_ASSERT_STREQ_R(s.c_str(),pp.getKey().c_str()) << "After the creation of a new instance of Pair and setting the key to a given string, getKey() returns this same string"<<endl;
    i = 1000;
    pp.setPos(i);
    SKIP_ASSERT_EQ_R(i,pp.getPos()) << "After the creation of a new instance of Pair and setting the value to a given number, getPos() returns the same number"<<endl;
}
