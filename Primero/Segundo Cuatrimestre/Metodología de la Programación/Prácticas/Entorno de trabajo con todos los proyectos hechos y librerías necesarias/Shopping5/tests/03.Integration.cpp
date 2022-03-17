/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "MPTests.h"

#ifdef __INTEGRATION__
using namespace std;


TEST_F(_01_Basics, Integration_ECommerce5)  {
    
    DEF_EXECUTION_ENVIRONMENT(ECommerce5);
    EXPECTED_OUTPUT(
Activity found: SUNDAY(0) MONDAY(0) TUESDAY(5) WEDNESDAY(0) THURSDAY(0) FRIDAY(0) SATURDAY(0) 
Records read: 5
Valid records: 5
Max activity: 5
Day of Max activity: TUESDAY
);
    CALL_FROM_FILE("")<<"Simple test with five (5) records only"<<endl;
}

TEST_F(_01_Basics, Integration_EMPTY)  {
    DEF_EXECUTION_ENVIRONMENT(EMPTY);
    FROM_KEYBOARD("0")
    EXPECTED_OUTPUT(
Activity found: SUNDAY(0) MONDAY(0) TUESDAY(0) WEDNESDAY(0) THURSDAY(0) FRIDAY(0) SATURDAY(0) 
Records read: 0
Valid records: 0
Max activity: 0
Day of Max activity: SUNDAY
);
    CALL_FROM_KEYBOARD( "")<<"Simple tet with an empty set of records" << endl;
}

TEST_F(_01_Basics, Integration_ECommerce49)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce49);
    EXPECTED_OUTPUT(
Activity found: SUNDAY(0) MONDAY(0) TUESDAY(49) WEDNESDAY(0) THURSDAY(0) FRIDAY(0) SATURDAY(0) 
Records read: 49
Valid records: 49
Max activity: 49
Day of Max activity: TUESDAY

);
    CALL_FROM_FILE( "")<<"Test with 49 records"<<endl;
}

TEST_F(_01_Basics, Integration_ECommerce_2019_Q4_200)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce_2019_Q4_200);
    EXPECTED_OUTPUT(
Activity found: SUNDAY(25) MONDAY(36) TUESDAY(32) WEDNESDAY(32) THURSDAY(25) FRIDAY(32) SATURDAY(18) 
Records read: 200
Valid records: 200
Max activity: 36
Day of Max activity: MONDAY
    );
    CALL_FROM_FILE( "")<<"Test with 200 records of 2019-Q4"<<endl;
}

TEST_F(_01_Basics, Integration_ECommerce_all_all_200)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce_all_all_200);
    EXPECTED_OUTPUT(
Activity found: SUNDAY(30) MONDAY(25) TUESDAY(29) WEDNESDAY(37) THURSDAY(33) FRIDAY(24) SATURDAY(22) 
Records read: 200
Valid records: 200
Max activity: 37
Day of Max activity: WEDNESDAY
    );
    CALL_FROM_FILE( "")<<"Test with 200 records amongst all available years"<<endl;
}

#endif