/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <vector>
#include <iostream>
#include <cassert>
#include "AnsiTerminal.h"
#include "OldMPTest.h"

using namespace std;

MPSingleTest::MPSingleTest() {
    init();
}

void MPSingleTest::init() {
    this->frominput = "";
    this->idtest = "";
    this->tooutput = "";
    this->runningtest = nullptr;
}

void MPSingleTest::defTest(std::string id, test mytest) {
    this->idtest = id;
    this->runningtest = mytest;
}

void MPSingleTest::runTest(void) {
    if (this->runningtest != nullptr){
        cout << "This is test "<<this->idtest<<endl;
        (this->runningtest)();
    }
}

void MPTestTable::addTest(std::string id, test mytest) {
    MPSingleTest st;
    st.defTest(id, mytest);
    this->TestList.push_back(st);
}

void MPTestTable::runAllTests()  {
    for (int i=0; i<this->TestList.size(); i++) {
        cout << "Executing my test "<<TestList[i].getId()<<endl;
        this->TestList[i].runTest();
    }
}



