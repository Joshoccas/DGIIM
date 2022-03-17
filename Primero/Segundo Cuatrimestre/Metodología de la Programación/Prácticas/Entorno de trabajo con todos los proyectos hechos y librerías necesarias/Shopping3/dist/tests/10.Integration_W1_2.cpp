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


TEST_F(_01_Basics, Integrated_5_records)  {   
    DEF_EXECUTION_ENVIRONMENT(ECommerce5);
    EXPECTED_OUTPUT(
[originalES(Original read from dataset)] 5 3788922744450141172
[filteredES(Events indexed)] 5 3788922744450141172
[hitsData( Report traffic)] 1 2019-10-01 00:00:00 UTC( 5.00) 
[ammountData( Report ammount)] 1 2019-10-01 00:00:00 UTC(18.73) 
);
    CALL_FROM_FILE("")<<"Execution of a simple test with five records only"<<endl;
    LOAD(_expected,((string)"./tests/validation/"+stestname+"-hit.dataset").c_str()); 
    LOAD(_output,((string)"./data/"+stestname+"-hit.dataset").c_str());
    ASSERT_FALSE_R(strcmp(_expected.c_str(), _output.c_str()))<<"The output file of this test with five records only is not as expected, please have a look at "<<((string)"./tests/validation/"+stestname+"-hit.dataset")<<endl;
}

TEST_F(_01_Basics, Integrated_30_records)  {   
    DEF_EXECUTION_ENVIRONMENT(ECommerce30);
    EXPECTED_OUTPUT(
[originalES(Original read from dataset)] 30 4276028894166694872
[filteredES(Events indexed)] 30 8592007267816246823
[hitsData( Report traffic)] 10 beautix( 4.00) grattol( 1.00) jas( 1.00) jessnail( 1.00) kapous( 2.00) kerasys( 1.00) masura( 2.00) runail(11.00) shary( 2.00) staleks( 5.00) 
[ammountData( Report ammount)] 10 beautix(43.82) grattol( 6.27) jas(25.71) jessnail( 1.10) kapous( 4.51) kerasys( 1.87) masura( 3.46) runail(41.94) shary( 6.04) staleks(63.33) 
);
    CALL_FROM_FILE("")<<"Execution of a test with 30 records only"<<endl;
}



#endif