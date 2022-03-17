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


TEST_F(_03_Advanced, Integrated_5_records)  {   
    DEF_EXECUTION_ENVIRONMENT(ECommerce5);
    EXPECTED_OUTPUT(
[eventS] 5 3788922744450141172
[purchaseSet] 0 6142509188972423790
[weeklyData] 7 5207999667161363639
[brandData] 0 3673012429007182808
[usersData] 0 6816849871933241109
);
    CALL_FROM_FILE("")<<"Simple test with five records only and no purchase"<<endl;
}

TEST_F(_03_Advanced, Integrated_49_records)  {   
    DEF_EXECUTION_ENVIRONMENT(ECommerce49);
    EXPECTED_OUTPUT(
[eventS] 49 7584936352554356154
[purchaseSet] 6 12003309466084639515
[weeklyData] 7 4868870355578892091
[brandData] 2 11188336870243159239
[usersData] 1 11654485409030856567
);
    CALL_FROM_FILE("")<<"Simple test with 49 records only with 6 purchases"<<endl;
}

TEST_F(_03_Advanced, Integrated_200_records)  {   
    DEF_EXECUTION_ENVIRONMENT(ECommerce_all_all_200);
    EXPECTED_OUTPUT(
[eventS] 200 7763302290924706323
[purchaseSet] 10 10835834335209909704
[weeklyData] 7 12999128784493908204
[brandData] 8 16176373717986376521
[usersData] 10 1054626476552412303
);
    CALL_FROM_FILE("")<<"Simple test with 200 records and 10 purchases"<<endl;
}

TEST_F(_03_Advanced, Integrated_500_records)  {   
    DEF_EXECUTION_ENVIRONMENT(ECommerce_all_all_500);
    USE_MEMORY_LEAKS(__VALGRIND__);
    EXPECTED_OUTPUT(
[eventS] 500 3011270673589162824
[purchaseSet] 30 5235127575259468424
[weeklyData] 7 144838431866189873
[brandData] 18 7957517975282959316
[usersData] 30 8756464028927728129);
    CALL_FROM_FILE("")<<"Simple test with 500 records and 30 purchases"<<endl;
}

TEST_F(_03_Advanced, Integrated_300_records)  {   
    DEF_EXECUTION_ENVIRONMENT(ECommerce_all_all_300);
    USE_MEMORY_LEAKS(__VALGRIND__);
    EXPECTED_OUTPUT(
[eventS] 300 17922222056063335357
[purchaseSet] 300 17922222056063335357
[weeklyData] 7 6774440025561285159
[brandData] 53 745941407701560619     
[usersData] 206 231870025905306929
);
    CALL_FROM_FILE("")<<"Simple test with 300 records and 300 purchases"<<endl;
}


#endif