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


TEST_F(_01_Basics, Integrated_Args_5_records)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce5);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(
[originalES(Original read from dataset)] 5 3788922744450141172
[filteredES(Events indexed)] 5 3788922744450141172
[hitsData(Report traffic)] 1 2019-10-01 00:00:00 UTC( 5.00)
[amountData(Report amount)] 1 2019-10-01 00:00:00 UTC(18.73)
);
    CALL(((string)"-input ./data/"+stestname+".dataset -events 5 -index-by UserID -report-by DateTime -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a simple test with five records only + mainargs"<<endl;
    LOAD(_expected,((string)"./tests/validation/"+stestname+"-hit.dataset").c_str());
    LOAD(_output,((string)"./data/"+stestname+"-hit2.dataset").c_str());
    ASSERT_FALSE_R(strcmp(_expected.c_str(), _output.c_str()))<<"The output file of this test with five records only is not as expected, please have a look at "<<((string)"./tests/validation/"+stestname+"-hit.dataset")<<endl;
}

TEST_F(_01_Basics, Integrated_Args_30_records)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce30);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(
[originalES(Original read from dataset)] 30 4276028894166694872
[filteredES(Events indexed)] 30 8592007267816246823
[hitsData(Report traffic)] 10 beautix( 4.00) grattol( 1.00) jas( 1.00) jessnail( 1.00) kapous( 2.00) kerasys( 1.00) masura( 2.00) runail(11.00) shary( 2.00) staleks( 5.00)
[amountData(Report amount)] 10 beautix(43.82) grattol( 6.27) jas(25.71) jessnail( 1.10) kapous( 4.51) kerasys( 1.87) masura( 3.46) runail(41.94) shary( 6.04) staleks(63.33)
);
    CALL(((string)"-input ./data/"+stestname+".dataset -events 30 -index-by Brand -report-by Brand").c_str())<<"Execution of a test with 30 records only + mainargs"<<endl;
}

TEST_F(_01_Basics, Integrated_Args_41_records)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce41);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(
[originalES(Original read from dataset)] 30 14112606467310379655
[filteredES(Events indexed)] 30 10218966595965943373
[hitsData(Report traffic)] 4 view(13.00) remove_from_cart( 5.00) cart( 1.00) purchase(11.00)
[amountData(Report amount)] 4 view(47.97) remove_from_cart(20.13) cart( 0.63) purchase(49.32)
);
    CALL(((string)"-input ./data/"+stestname+".dataset -events 30 -index-by UserID -report-by Type -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a simple test with 41 records only + mainargs"<<endl;
    LOAD(_expected,((string)"./tests/validation/"+stestname+"-hit.dataset").c_str());
    LOAD(_output,((string)"./data/"+stestname+"-hit2.dataset").c_str());
    ASSERT_FALSE_R(strcmp(_expected.c_str(), _output.c_str()))<<"The output file of this test with 41 records only is not as expected, please have a look at "<<((string)"./tests/validation/"+stestname+"-hit.dataset")<<endl;
}

TEST_F(_01_Basics, Integrated_Args_162_records)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce162);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(
[originalES(Original read from dataset)] 162 9266767888509524085
[filteredES(Events indexed)] 99 15768426163348320984
[hitsData(Report traffic)] 31 beauty-free( 1.00) blixz( 1.00) bluesky( 1.00) bpw.style(22.00) cosmoprofi( 1.00) depilflax( 1.00) domix( 1.00) entity( 1.00) estel( 3.00) f.o.x( 1.00) freedecor( 8.00) haruyama( 1.00) ingarden( 5.00) irisk( 8.00) italwax(12.00) jessnail( 1.00) konad( 1.00) kosmekka( 1.00) lamixx( 1.00) masura( 8.00) metzger( 1.00) milv( 1.00) orly( 1.00) pnb( 2.00) roubloff( 2.00) runail( 2.00) shary( 2.00) shik( 2.00) solomeya( 1.00) staleks( 5.00) uno( 1.00)
[amountData(Report amount)] 31 beauty-free( 1.89) blixz( 1.21) bluesky( 3.97) bpw.style(24.23) cosmoprofi( 7.14) depilflax( 7.14) domix( 4.57) entity( 3.40) estel(43.65) f.o.x( 4.19) freedecor( 9.83) haruyama( 3.97) ingarden( 7.34) irisk(43.25) italwax(68.98) jessnail(44.29) konad( 4.19) kosmekka(15.24) lamixx(46.49) masura(17.17) metzger( 3.73) milv( 3.49) orly( 1.98) pnb( 6.61) roubloff( 6.28) runail(10.16) shary( 7.94) shik(20.64) solomeya( 0.87) staleks(69.86) uno(10.32)
);
    CALL(((string)"-input ./data/"+stestname+".dataset -events 162 -index-by Brand -report-by Brand -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a simple test with 162 records only + mainargs"<<endl;
    LOAD(_expected,((string)"./tests/validation/"+stestname+"-hit.dataset").c_str());
    LOAD(_output,((string)"./data/"+stestname+"-hit2.dataset").c_str());
    ASSERT_FALSE_R(strcmp(_expected.c_str(), _output.c_str()))<<"The output file of this test with 162 records only is not as expected, please have a look at "<<((string)"./tests/validation/"+stestname+"-hit.dataset")<<endl;
}

TEST_F(_01_Basics, Integrated_Args_926_records)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce926);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(
[originalES(Original read from dataset)] 500 16502657669702680370
[filteredES(Events indexed)] 500 244972924156216850
[hitsData(Report traffic)] 57 (201.00) irisk(16.00) farmstay( 1.00) farmona( 3.00) kapous( 6.00) runail(45.00) masura(14.00) marathon( 7.00) strong( 6.00) pnb( 2.00) domix( 1.00) milv( 1.00) artex( 1.00) zinger( 3.00) yoko( 1.00) ingarden(27.00) uskusi( 5.00) jas( 2.00) lovely( 5.00) enigma( 1.00) max(11.00) uno(15.00) enas( 1.00) jessnail( 1.00) lianail( 1.00) osmo( 1.00) grattol( 6.00) estelare( 1.00) lowence( 4.00) kinetics( 2.00) art-visage( 2.00) provoc( 3.00) consly( 5.00) eunyul( 5.00) lebelage( 1.00) browxenna( 2.00) thuya( 8.00) italwax( 2.00) depilflax( 1.00) estel( 5.00) beauty-free( 4.00) solomeya( 1.00) oniq(16.00) kosmekka( 4.00) haruyama(12.00) i-laq( 4.00) bioaqua( 7.00) emil( 1.00) kaaral( 6.00) beautyblender( 4.00) cnd( 4.00) shik( 2.00) bpw.style( 1.00) dermal( 4.00) keen( 2.00) sunuv( 1.00) beautix( 2.00)
[amountData(Report amount)] 57 (2790.43) irisk(129.85) farmstay( 0.63) farmona(80.73) kapous(21.90) runail(63.61) masura(57.88) marathon(964.46) strong(1172.22) pnb( 7.38) domix( 4.24) milv( 3.17) artex(15.08) zinger(48.15) yoko( 7.83) ingarden(174.99) uskusi(19.05) jas(51.42) lovely(34.93) enigma( 6.90) max(579.86) uno(134.48) enas( 3.54) jessnail( 8.73) lianail( 6.33) osmo( 9.71) grattol(25.14) estelare( 3.02) lowence(69.84) kinetics(18.74) art-visage( 9.36) provoc(19.71) consly(23.50) eunyul(35.55) lebelage( 3.75) browxenna(29.68) thuya(252.06) italwax(26.04) depilflax(10.54) estel(27.45) beauty-free(18.80) solomeya( 1.75) oniq(139.68) kosmekka(128.88) haruyama(47.64) i-laq(15.88) bioaqua(54.46) emil(55.56) kaaral(59.22) beautyblender(99.04) cnd(34.28) shik(20.64) bpw.style( 0.79) dermal( 4.12) keen(19.56) sunuv(33.33) beautix(31.42)
);
    CALL(((string)"-input ./data/"+stestname+".dataset -events 500 -index-by UserID -report-by Brand -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a simple test with 500 records only + mainargs"<<endl;
    LOAD(_expected,((string)"./tests/validation/"+stestname+"-hit.dataset").c_str());
    LOAD(_output,((string)"./data/"+stestname+"-hit2.dataset").c_str());
    ASSERT_FALSE_R(strcmp(_expected.c_str(), _output.c_str()))<<"The output file of this test with 500 records only is not as expected, please have a look at "<<((string)"./tests/validation/"+stestname+"-hit.dataset")<<endl;
}

TEST_F(_03_Advanced, Integrated_Args_no_open)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce926);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(Error opening file ./datas/ECommerce926.dataset);
    CALL_FROM_FILE(((string)"-input ./datas/"+stestname+".dataset -events 500 -index-by UserID -report-by Brand -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a simple test with main args where the input file is not found"<<endl;
}

TEST_F(_03_Advanced, Integrated_Args_error_data)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce162);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(Data error in file ./data/ECommerce162.dataset);
    CALL_FROM_FILE(((string)"-input ./data/"+stestname+".dataset -events 500 -index-by UserID -report-by Brand -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a simple test with main args where the number of specified events is greater than the total number of events in the data file"<<endl;
}

TEST_F(_03_Advanced, Integrated_Args_error_missing_arg)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce162);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(Error in call);
    CALL_FROM_FILE(((string)"-events 500 -index-by UserID -report-by Brand -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a simple test with 500 records only + mainargs"<<endl;
    CALL_FROM_FILE(((string)"-input ./data/"+stestname+".dataset -index-by UserID -report-by Brand -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a test with main args where the input file is not specified"<<endl;
}

TEST_F(_03_Advanced, Integrated_Args_error_bad_arg)  {
    DEF_EXECUTION_ENVIRONMENT(ECommerce162);
    USE_MEMORY_LEAKS(__VALGRIND__);
    SET_TIMEOUT_S(15);
    EXPECTED_OUTPUT(Error in call);
    CALL_FROM_FILE(((string)"-i ./data/"+stestname+".dataset -events 500 -index-by UserID -report-by Brand -output ./data/"+stestname+"-hit2.dataset").c_str())<<"Execution of a test with main args where one of the arguments is not understood"<<endl;
}


#endif
