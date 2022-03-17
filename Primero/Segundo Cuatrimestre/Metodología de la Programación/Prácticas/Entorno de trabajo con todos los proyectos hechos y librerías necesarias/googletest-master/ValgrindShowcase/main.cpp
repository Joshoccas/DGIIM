/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <string>
#include <sstream>
#include <signal.h>
using namespace std;

stringstream msg;

void handler(int signal) {
    cout << endl << msg.str();
    cout << endl << "Signal " << signal << " has been received" << endl;
    exit(1);
}

void handler2(int signal) {
    handler(signal);
}

void SafeAccess() {
    int *p = nullptr, i;

    msg.str("");
    cout << "5. SAFE ACCESS" << endl; msg << "Now, it is time to access the memory. Please reserve space for 4 integers p=new int[4]";
//    p = new int[4]; //
    if (p == nullptr) return;
    msg.str("");
    msg << "After the reservation, we can access these positions as a regular vector" << endl;
    for (i = 0; i < 4; i++) {
        p[i] = i*i;
        msg << "Position " << i << " is at memory address " << &(p[i]) << " and its value is " << p[i] << endl;
    }
    msg << "The following loop is mistaken and produces a forbiden read" << endl;

    for (i = 0; i < 5; i++) //
        msg << "Position " << i << " is at memory address " << &(p[i]) << " and its value is " << p[i] << endl;
    delete []p;
    p = nullptr;
    msg << "It might produce an error or not, but valgrind always does" << endl;
    msg << "==5250== Invalid read of size 4" << endl;
    msg << "==5250==    at 0x1094A5: SafeAccess() (main.cpp:39)" << endl;
    msg << "==5250==    by 0x109BB9: SafetyFirst() (main.cpp:84)" << endl;
    msg << "Please, adjust the end of the loop in line 39 to its right position and Run" << endl;
    if (i > 4) return;
    msg.str("");
    msg << "Well done!" << endl << "Now, if valgrind is ok, uncomment the following lines and Run" << endl;
//    msg.str("");
//    msg << endl << "The same would have happened with any write operation " << endl;
//    msg << " The following loop produces a write error." << endl;
//
//    p = new int[10];
//    for (i = 0; i < 11; i++) { //
//        if (i >= 10) {
//            cout << msg.str();
//            msg.str("");
//        }
//        p[i] = i*i;
//        msg << "Position " << i << " is at memory address " << &(p[i]) << " and its value is " << p[i] << endl;
//    }
//    delete []p;
//    msg << "It might produce an error or not, but valgrind always does. Please adjust the loop in line 56 and Run";
//    if (i > 10) return;
//    msg.str("");
//    msg << "Finally, If valgrind reports no errors, then the exercise is over" << endl;
}

void SafetyFirst() {
    int i = 314159, *p; // 

    msg.str("");
    cout << "4. SAFETY FIRST" << endl; msg  << "So the first thing to do is making pointers safe, not wild, by initializing them ALWAYS to the constant nullptr." << endl;
    msg << endl << "Please initialize the pointer p safely in line 72 and Run" << endl;
    if (p != nullptr) return;
    msg .str("");
    msg << "Well done!" << endl;
    msg << "Another safe operation is asking the operating system for memory and then use it." << endl;
    p = new int;
    msg << "This memory " << p << " is mine and outside of the stack, in the heap. But it is mine " << endl;
    *p = 14142;
    msg << "and I can change it safely " << *p << endl;
    msg << "However, before the program ends, it must be returned to the operating system. Run valgrind to confirm that there is an error in main.cpp:81" << endl;
    msg << endl << "==22367== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1" << endl
            << "==22367==    at 0x4C3217F: operator new(unsigned long) (vg_replace_malloc.c:334)" << endl
            << "==22367==    by 0x1096EE: SafetyFirst() (main.cpp:81)" << endl << endl;
    msg << "This means that the operation new in line 81 has not been freed, but it should. Then write "<<endl <<"delete p;"<<endl<<"p=nullptr;"<<endl<<"and Run" << endl;
//    delete p; //
//   p = nullptr;
    if (p != nullptr) {
        return;
    }
    if (p == nullptr) {
        msg .str("");
        msg << "Well done! Now check valgrind and, if it is ok, uncomment line 98 and Run" << endl;
//        SafeAccess();
    }
}

void ButTheMainDifferenceIs() {
    int i = 314159, *p, *other, *wild; //

    msg.str("");
    cout << "3. BUT THE MAIN DIFFERENCE IS THAT IT CAN BE USED TO ENTER THE MEMORY AT THAT POINT "<< endl;
    msg << "But in order to do that this operation must be safe" << endl;
    p = &i;
    msg << "because we are only allowed to access memory owned by me. Like this " << *p << " but not any other " << endl;
    other = &i + 10000;
    msg << "The following line is a forbidden read-access that produces a segmentation fault, comment line 112 and Run again" << endl;
    msg << "This is a forbidden read-access " << *other << endl; // comment this line
    msg.str("");
    msg << "Well done!" << endl << "Therefore a pointer like this " << other << " not initialized, is knwown as a WILD POINTER" << endl;
    msg << "It points to a random area, most likely not mine." << endl;
    msg << "However, some compilers, initialize the pointers to a relatively safe area within my own stack." << endl;
    msg << "I can access to see what is in there " << wild << " --> " << *wild << " because it is mine" << endl;
    msg << "But I should not modify that address becuase it could lead to an UNPREDICTABLE DISASTER" << endl;
    msg << "Run valgrind to check that although everything is ok, there are many errors" << endl;
    msg << "This is because variables p, other and wild are not initialized." << endl << "Then initialize them = &i in line 103 and Run" <<endl;
    if (wild != &i) return;
    msg.str("");
    msg << "Well done!" << endl << "Now, if valgrind reports no errors, then uncomment line 124" << endl;
//    SafetyFirst(); //
}

void APointerIsLikeAnyOtherData() {
    int i, *p ; //

    cout << "2. A POINTER IS LIKE ANY OTHER DATA " << endl;
    msg.str("");
    //    
    msg << "it may be shown " << p << endl;
    msg << "and modified " << p + 100 << endl;
    msg << "Run valgrind to check that although everything seems to be ok, there are many errors" << endl;
    msg << endl << "==11545== ERROR SUMMARY: XX errors from YY contexts (suppressed: 0 from 0)" << endl << endl;
    msg << "This is because variable p is not initialized. Then initialize p = &i in line 128 and Run" << endl;
    if (p != &i) return;
    msg.str("");
    msg << "Well done. If valgrind reports no errors then uncomment line 141 and Run" << endl;
    //ButTheMainDifferenceIs(); //
}

int main() {
    signal(SIGSEGV, handler);
    cout << "1. INTRODUCTION" << endl;
    msg << endl << "Follow the instructions to complete the exercise" << endl;
    msg << "Run valgrind to check that everything is ok, so you will get" << endl << " ERROR SUMMARY: 0 errors from 0 contexts" << endl;
    msg << " valgrind --leak-check=full dist/Debug/GNU-Linux/valgrindshowcase" << endl;
    /* 
      valgrind --leak-check=full dist/Debug/GNU-Linux/valgrindshowcase 
     * 
     * 
     * ==23918== Memcheck, a memory error detector                                                    
    ==23918== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==23918== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==23918== Command: dist/Debug/GNU-Linux/valgrindshowcase
    ==23918== 
    Follow the instructions to complete the exercise
    Run valgrind to check that everything is ok:
    ==23918== 
    ==23918== HEAP SUMMARY:
    ==23918==     in use at exit: 0 bytes in 0 blocks
    ==23918==   total heap usage: 2 allocs, 2 frees, 73,728 bytes allocated
    ==23918== 
    ==23918== All heap blocks were freed -- no leaks are possible
    ==23918== 
    ==23918== For counts of detected and suppressed errors, rerun with: -v
    ==23918== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
     * 
     */
    msg << "Then uncomment the call in line 173 and Run" << endl;
    //APointerIsLikeAnyOtherData();
    cout << endl << msg.str();
}
