/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <gtest/gtest.h>
#include "MPTests.h"

#ifdef __INTEGRATION__

using namespace std;


TEST_F(_03_Advanced, PrimerCaso)  {
    DEF_EXECUTION_ENVIRONMENT(PrimerCaso);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(
[recommendations(Top recommendations)] 6 haruyama( 0.0843) ingarden( 0.1128) markell( 0.3028) nitrimax( 0.2017) roubloff( 0.1396) veraclara( 0.1588) 																																																				
            );
    CALL(((string)"-input ./data/"+stestname+
            ".dataset -events 20 -K 100 -type cart").c_str())<<"Execution of a simple test with five records only + mainargs"<<endl;
}

TEST_F(_03_Advanced, SegundoCaso)  {
    DEF_EXECUTION_ENVIRONMENT(SegundoCaso);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(
[recommendations(Top recommendations)] 10 almea( 0.1279) beauty-free( 0.1153) biofollica( 0.0695) deoproce( 0.0958) estrade( 0.0986) likato( 0.0886) missha( 0.1032) profhenna( 0.1079) roubloff( 0.1216) ypsed( 0.0718) 																																																				
            );
    CALL(((string)"-input ./data/"+stestname+
            ".dataset -events 400 -K 100 -type cart").c_str())<<"Execution of a simple test with five records only + mainargs"<<endl;
}


#endif