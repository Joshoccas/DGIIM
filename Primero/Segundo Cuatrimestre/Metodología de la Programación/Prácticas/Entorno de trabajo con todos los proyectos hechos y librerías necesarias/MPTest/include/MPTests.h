/**
 * @file MPtest.h
 * @brief Extension to Googletest to cover formatted reporting of tests
 * @author DECSAI
 */

#ifndef MP__TESTS__
#define MP__TESTS__
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <regex>
#include <cinttypes>
#include "gtest/gtest.h"

#define __PATH__ "./dist/Debug/GNU-Linux/"
#define __TIME_OUT_CALL__ "timeout --preserve-status -k "
#define __BASE__ __COUNTER__
#define FILEINPUT "./tests/validation/" + stestname + ".keyboard"
#define FILEOUTPUT "./tests/output/" + stestname + ".output"
#define FILEDIFF "./tests/output/" + stestname + ".wdiff"
#define FILEKEYBOARD "./tests/validation/" + stestname + ".keyboard"
#define FILECOUT "./tests/output/" + stestname + ".cout"
#define FILEEXPECTED "./tests/validation/" + stestname + ".expected"
#define FILEMLEAKS "./tests/output/" + stestname + ".mleaks.compact"
#define FILEMLEAKSMD "./tests/output/" + stestname + ".mleaks.simplified.md"
#define FILESTOP "./tests/output/stop.detected"
#define FILESTOPMLEAKS "./tests/output/mleaks.detected"
#define FILEREPORT_APPEND "./tests/output/TestReportAppend.md"
#define __VALGRIND__ "-valgrind"
#define __DRMEMORY__ "-drmemory"
#define __RUN_OUTPUT__ FILEOUTPUT("output")
#define MAX_STRING_OUTPUT 1000

#define EMPTYS  ""
#define SPACE " "
#define NEWLINE "\n"
#define TESTING_FLAG false


#ifdef __REPORT_ALL_TESTS__
#define FILEREPORT "./doc/markdown/TestDescription.md"
#define __defReport true
#define ASSERTNE(...) \
        ofreport
#define ASSERTEQ(...) \
        ofreport
#define ASSERTTRUE(...) \
        ofreport
#define ASSERTFALSE(...) \
        ofreport
#define ASSERTSTREQ(...) \
        ofreport
#define ASSERTSTRNE(...) \
        ofreport
#define EXPECTNE(...) \
        ofreport
#define EXPECTEQ(...) \
        ofreport
#define EXPECTSTREQ(...) \
        ofreport
#define EXPECTSTRNE(...) \
        ofreport
#else
#define FILEREPORT "./tests/TestReport.md"
#define __defReport false
#define ASSERTNE(...) ASSERT_NE(__VA_ARGS__) << idtest<< " "
#define ASSERTEQ(...) ASSERT_EQ(__VA_ARGS__) << idtest<< " "
#define ASSERTTRUE(...) ASSERT_TRUE(__VA_ARGS__) << idtest<< " "
#define ASSERTFALSE(...) ASSERT_FALSE(__VA_ARGS__) << idtest<< " "
#define ASSERTSTREQ(...) ASSERT_STREQ(__VA_ARGS__) << idtest<< " "
#define ASSERTSTRNE(...) ASSERT_STRNE(__VA_ARGS__) << idtest<< " "
#define EXPECTNE(...) EXPECT_NE(__VA_A_ARGS__) << idtest<< " "
#define EXPECTEQ(...) EXPECT_EQ(__VA_A_ARGS__) << idtest<< " "
#define EXPECTSTREQ(...) EXPECT_STREQ(__VA_A_ARGS__) << idtest<< " "
#define EXPECTSTRNE(...) EXPECT_STRNE(__VA_A_ARGS__) << idtest<< " "
#endif

class _01_Basics : public ::testing::Test {
public:

    _01_Basics() : Test() {
    }

protected:

    virtual void SetUp() {
        ofreport.open(FILEREPORT, std::ios_base::app);
    }

    virtual void TearDown() {
        ofreport.close();
    }

    std::ofstream ofreport;
    std::string idtest;
};

class _02_Intermediate : public ::testing::Test {
public:

    _02_Intermediate() : Test() {
    }

protected:

    virtual void SetUp() {
        ofreport.open(FILEREPORT, std::ios_base::app);
    }

    virtual void TearDown() {
        ofreport.close();
    }

    std::ofstream ofreport;
    std::string idtest;
};

class _03_Advanced : public ::testing::Test {
public:

    _03_Advanced() : Test() {
    }

protected:

    virtual void SetUp() {
        ofreport.open(FILEREPORT, std::ios_base::app);
    }

    virtual void TearDown() {
        ofreport.close();
    }

    std::ofstream ofreport;
    std::string idtest;
};

/////////////////////////////////////////////
// Tools
/////////////////////////////////////////////

/**
 * @brief Simmulates a breakpoint by stoping and reading a fictitious data
 */
#define BREAKPOINT(X)\
    if (X){\
        char c;\
        cout <<endl<<"Press a key: ";\
        cin>>c;\\
    }

/**
 * @brief Removes spare left spaces
 */
#define LTRIM(STRINGVAR) \
    do { \
    std::string aux="", orig=STRINGVAR; \
    bool trim=true; \
    for (int i=0; i<orig.length(); i++)  \
        if (!trim || orig[i] != SPACE[0]) { \
        aux= aux + orig[i]; \
        trim=false; } \
    STRINGVAR = aux; \
    } while(0); 

/**
 * @brief Remove spare right spaces
 */
#define RTRIM(STRINGVAR) \
    do { \
    std::string aux="", orig=STRINGVAR; \
    bool trim=true; \
    for (int i=orig.length()-1; i>=0; i--)  \
        if (!trim || orig[i] != SPACE[0]) { \
        aux = orig[i]+aux; \
        trim=false; } \
    STRINGVAR = aux; \
    } while(0); 
/**
 * @brief Remove spare middle spaces
 */
#define MTRIM(STRINGVAR) \
    do { \
    std::string aux="", orig=STRINGVAR; \
    int i=0; \
    while(i<orig.length())  \
        if (i<orig.length()-1 && orig[i] == SPACE[0] && orig[i+1] == SPACE[0]) { \
            i++;}\
        else {\
            aux= aux + orig[i++];} \
    STRINGVAR = aux; \
    } while(0); 

/**
 * @brief Recursively replaces a ssubstring by another
 */
#define REPLACE(STRINGVAR, SUBS1, SUBS2) \
    do { \
    size_t index = 0, len = ((std::string)SUBS1).length(); \
    while (true) { \
        index = STRINGVAR.find(SUBS1, index); \
        if (index == std::string::npos) break; \
         STRINGVAR.replace(index, len, SUBS2); \
         index += len;  \
     }; \
     } while(0); 

/**
 * @brief Preprocesses an output string for comparison
 */
#define CLEANUP(STRINGVAR)  \
    REPLACE(STRINGVAR,NEWLINE,SPACE); \
    REPLACE(STRINGVAR,"\t",SPACE); \
    LTRIM(STRINGVAR); \
    RTRIM(STRINGVAR); \
    MTRIM(STRINGVAR); 

/**
 * Load the whole content of a file in a single-lined string, replacing separators by spaces
 */
#define LOAD(STRINGVAR, FILENAME) \
    do { \
    std::ifstream fi(FILENAME); \
    std::stringstream ss;\
    ss << fi.rdbuf(); \
    STRINGVAR = ss.str();\
    } while(0); \
    CLEANUP(STRINGVAR);

/**
 * Save the content of a std::string into a file
 */
#define SAVE(TEXT, FILENAME) \
    do { \
    std::ofstream fo##__LINE__(FILENAME); \
    fo##__LINE__ << TEXT << std::endl; \
    } while(0);

/**
 * Appends the content of a std::string into a file
 */
#define APPEND(TEXT, FILENAME) \
    do { \
    std::ofstream fo##__LINE__(FILENAME, std::ios_base::app); \
    fo##__LINE__ << TEXT; \
    } while(0);


#define getFCounter(filecounter, i)\
    do {\
    std::string svalue;\
    LOAD(svalue, filecounter);\
    i=(int)std::stoi(svalue.c_str());\
    }while(0);

#define setFCounter(filecounter, i)\
    do {\
    std::string svalue=std::to_string(i);\
    SAVE(svalue, filecounter);\
    }while(0);

#define resetFCounter(filecounter)\
    setFCounter(filecounter, 0)\
    
#define deltaFCounter(filecounter, delta)\
    do{\
        int i;\
        getFCounter(filecounter, i);\
        i  += delta;\
        setFCounter(filecounter,i);\
    }while(0);


//#define __DEBUG__

#ifdef __DEBUG__
#define __TESTING__
#endif 

#define __TESTING__

#ifndef __RELEASE__
#define CVAL std::clog 
#define REPORT_DATA(VAR) CVAL << std::endl<< "["<<#VAR<<"] "<< VAR.reportData() << std::endl;
#define REPORT_DATA2(VAR, MSG) CVAL << std::endl<< "["<<#VAR<<"(" << MSG << ")] "<< VAR.reportData() << std::endl;
#define REPORT_TEXT(TEXT) CVAL << TEXT << std::endl;
#else
#define CVAL std::cout
#define REPORT_DATA(VAR) ;
#define REPORT_TEXT(TEXT) ;
#endif


#ifdef __TESTING__




/////////////////////////////////////////////
// FAIL / SUCCESS OF TESTS
/////////////////////////////////////////////


/**
 * @brief If the previous tests failed, then
 */
#define SKIP_IF_FAILED_BEFORE() \
    do{ \
    std::string sfail; \
    LOAD(sfail, FILESTOP);\
    if (sfail != "PASS") { \
        SKIP_TEST();\
     } \
    }while(0);

/**
 * @brief Records that a test has SUCCEDED
 */
#define PASS_TEST() \
    SAVE("PASS", FILESTOP);

/**
 * @brief Record that a test has failed
 */
#define FAIL_TEST() \
    SAVE("FAIL", FILESTOP);

/**
 * @brief If the previous tests failed, then
 */
#define SKIP_IF_MEMORY_LEAKS() \
    do{ \
    std::string sfail; \
    LOAD(sfail, FILESTOPMLEAKS);\
    if (sfail != "MEM_OK") { \
        SKIP_TEST();\
     } \
    }while(0);

/**
 * @brief Records that a test has SUCCEDED
 */
#define PASS_MEMORY_LEAKS() \
    SAVE("MEM_OK", FILESTOPMLEAKS);

/**
 * @brief Record that a test has failed
 */
#define FAIL_MEMORY_LEAKS() \
    SAVE("MEM_LEAKS", FILESTOPMLEAKS);

#define SKIP_TEST() \
    REPORT_SKIPPED_TEST();\
    GTEST_SKIP();    

/////////////////////////////////////////////
// Control the process of testing
/////////////////////////////////////////////

/**
 * @brief Must be the first thing in the test process. Warm up GoogleTest and 
 * prepares the MPTest environment
 */
#define INIT_MAIN() \
::testing::InitGoogleTest(); \
BEGIN_TESTING();\

/**
 * @brief Must be the last thing in the test process. It really launches 
 * the tests, and closes the reports
 * 
 */
#define RETURN_MAIN(X)  \
do {\
int ret= RUN_ALL_TESTS();\
END_TESTING();\
return ret;\
}while(0);


/**
 * @brief Starts the process of MPTests, including report, skip of test and execution 
 * environments
 */
#define BEGIN_TESTING() \
    system("../Scripts/getProjectName.sh");\
    ofstream ofreport;\
    resetFCounter("__nReport");\
    resetFCounter("__nTest");\
    SAVE("","__nTestname");\
    HEAD_REPORT(); \
    SAVE("",FILEREPORT_APPEND);\
    PASS_MEMORY_LEAKS();\
    PASS_TEST();

/**
 * @brief Closes the process of MPTests
 */
#define END_TESTING() \
    do {\
    std::string footnote;\
    LOAD(footnote,FILEREPORT_APPEND);\
    REPLACE(footnote, "#", "\n(!) ");\
    REPLACE(footnote, " 1.", "\n\n   *");\
    REPLACE(footnote, " a.", "\n      -");\
    APPEND(footnote,FILEREPORT);\
    } while(0);


/////////////////////////////////////////////
// Integration tests
/////////////////////////////////////////////

/**
 * Prepares the environment for every single Integration test
 */
//SKIP_IF_FAILED_BEFORE();
#define DEF_EXECUTION_ENVIRONMENT(NAME) \
    std::string stestname= #NAME; \
    long timeout=30;\
    bool breakpoint=false;\
    std::string _output, _wdiff, _expected, __PROJECT__, __BIN__; \
    char REAL_OUTPUT[MAX_STRING_OUTPUT], EXPECTED_OUTPUT[MAX_STRING_OUTPUT];\
    std::string cmdline="", binary="", leakdetector="", leakreport; \
    LOAD(__PROJECT__,"./.projectname");\
    __BIN__ = (string)(__PATH__)+ __PROJECT__;\
    cmdline=cmdline+"rm -f "+FILEOUTPUT +" " +FILECOUT+ " " +FILEEXPECTED; \
    std::system(cmdline.c_str()); \
    cmdline="";

/**
 * @brief Defines a timeout (seconds) for the execution of every integration test. By 
 * default this timeout is 30 secs.
 */
#define SET_TIMEOUT_S(NUMBER) \
     timeout = NUMBER;


/**
 * @brief Save the text as a simmulated keyboard input. It saves it into a file
 * for further processing
 */
#define FROM_KEYBOARD(TEXT) \
    SAVE(TEXT, FILEKEYBOARD );

/**
 * @brief Defines the expected outcome of the integration tests, and temporally
 * saves it into a file for further processing. The outcome is treated as sequence
 * of symbols
 */
#define EXPECTED_OUTPUT(...) \
    SAVE(#__VA_ARGS__, FILEEXPECTED );

/**
 * @brief Defines the expected outcome of the integration tests, and temporally
 * saves it into a file for further processing. The outcome is treates as a std::string
 */
#define EXPECTED_TEXT_OUTPUT(TEXT) \
    SAVE(TEXT, FILEEXPECTED );

/**
 * @brief Calls the main binary redirecting the stdin from a file with keyboard strokes.
 * It also supports main arguments
 */
#define CALL_FROM_KEYBOARD(ARGS) \
    binary = __BIN__ + " " + ARGS ; \
    DETECT_MEMORY_LEAKS(); \
    cmdline="";\
    cmdline = cmdline+ __TIME_OUT_CALL__+" "+ std::to_string(timeout).c_str()+" "+std::to_string(timeout).c_str()+" ";\
    cmdline = cmdline + binary +" < " +FILEKEYBOARD+ " 1> "+FILECOUT + " 2> " + FILEOUTPUT; \
    std::system(cmdline.c_str());\
    LOAD(_output, FILEOUTPUT); \
    SAVE(_output, FILEOUTPUT); \
    cmdline=(string)"../Scripts/getDifferenceOutputs.sh "+stestname+" > "+FILEDIFF;\
    std::system(cmdline.c_str());\
    COMPARE_OUTPUTS() 

/**
 * @brief Calls the main binary redirecting the stdin from a file with keyboard strokes
 * It also supports main arguments
 */
#define CALL_FROM_FILE(ARGS) \
    binary = __BIN__+ " " + ARGS ; \
    DETECT_MEMORY_LEAKS(); \
    cmdline="";\
    cmdline = cmdline+ __TIME_OUT_CALL__+" "+ std::to_string(timeout).c_str()+" "+std::to_string(timeout).c_str()+" ";\
    cmdline = cmdline + binary +" < " +FILEINPUT+ " 1> "+FILECOUT + " 2> " + FILEOUTPUT; \
    std::system(cmdline.c_str());\
    LOAD(_output, FILEOUTPUT); \
    SAVE(_output, FILEOUTPUT); \
    cmdline=(string)"../Scripts/getDifferenceOutputs.sh "+stestname+" > "+FILEDIFF;\
    std::system(cmdline.c_str());\
    COMPARE_OUTPUTS()

/**
 * @brief Calls the main binary with only main arguments
 */
#define CALL(ARGS) \
    binary = __BIN__ + " " + ARGS ; \
    DETECT_MEMORY_LEAKS(); \
    cmdline="";\
    cmdline = cmdline+ __TIME_OUT_CALL__+" "+ std::to_string(timeout).c_str()+" "+std::to_string(timeout).c_str()+" ";\
    cmdline = cmdline + binary +" 1> "+FILECOUT + " 2> " + FILEOUTPUT; \
    std::system(cmdline.c_str());\
    LOAD(_output, FILEOUTPUT); \
    SAVE(_output, FILEOUTPUT); \
    cmdline=(string)"../Scripts/getDifferenceOutputs.sh "+stestname+" > "+FILEDIFF;\
    std::system(cmdline.c_str());\
    COMPARE_OUTPUTS() 


/////////////////////////////////////////////
// Memory leak integration
/////////////////////////////////////////////

/**
 * Defines the use of a certain memory leak detector, either __VALGRIND__
 * or __DRMEMORY__
 */
#define USE_MEMORY_LEAKS(which) \
    leakdetector= which;\

/**
 * @brief Executes the binary within Valgrind or DrMemory, by using an external
 * script which simplifies the process and produces a unified report for both
 * Valgrind and DrMemory. If no memory leak has been requested is does nothing
 */
#define DETECT_MEMORY_LEAKS() \
    if (!__defReport) {\
        SKIP_IF_MEMORY_LEAKS();\
        if (leakdetector.length()>0){\
            cmdline=""; \
            cmdline = cmdline +"../Scripts/doCheckMemoryLeaks.sh " + leakdetector+ " "+stestname+ "  \"" + binary+"\""; \
            cout << "[ MEMCHECK ] "<<stestname<< leakdetector;\
            std::system(cmdline.c_str()); \
            cmdline="";\
            LOAD(_output, FILEMLEAKS); \
            strncpy(REAL_OUTPUT, _output.c_str(),50); \
            strcpy(EXPECTED_OUTPUT, ""); \
            SKIP_ASSERT_MEM_R(EXPECTED_OUTPUT,REAL_OUTPUT);\
        }\
    }

/**
 * @brief Checks if the previous execution has produced a memory leak and
 * reports it
 */
#define CHECK_MEMORY_LEAKS() \
    do {\
    std::string MLHead ="";\
    std::string idtest;\
    UPDATEIDTEST();\
    IDTEST(idtest);\
    LOAD(leakreport,FILEMLEAKS);\
    if(leakreport == "") {\
        cout << "\n[       OK ] "<<stestname << leakdetector << std::endl;\
        MLHead = MLHead +"| "+ idtest + "| "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+ ::testing::UnitTest::GetInstance()->current_test_info()->name()+ leakdetector+" | ";\
        APPEND(MLHead, FILEREPORT);\
        APPEND("PASSED | NO LEAKS |\n", FILEREPORT);\
        PASS_TEST();\
        PASS_MEMORY_LEAKS();\
        deltaFCounter("__nReport", (-1));\
    } else {\
        MLHead = MLHead +"| "+ idtest + "| "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+ ::testing::UnitTest::GetInstance()->current_test_info()->name()+ leakdetector+"** | ";\
        APPEND(MLHead, FILEREPORT);\
        APPEND("**FAILED** | **HAS MEMORY LEAKS** (!) |\n", FILEREPORT);\
        REPLACE(leakreport,"#[", "\n[");\
           cout << leakreport <<endl;\
        FAIL_TEST();\
        FAIL_MEMORY_LEAKS();\
        LOAD(MLHead,FILEMLEAKSMD);\
        SAVE(MLHead,FILEREPORT_APPEND);\
        GTEST_FAIL();\
     }\
     } while(0); \


/////////////////////////////////////////////
// MPTest special assertions
/////////////////////////////////////////////


/**
 * @brief Checks that the real output of the binary and the expected output matches
 * This is the basis of an integration test. If both matches, the integration test
 * succeds, otherwise, it fails
 */
#define COMPARE_OUTPUTS() \
    PASS_TEST();\
    LOAD(_wdiff, FILEDIFF); \
    REPORT_INTEGRATION_TEST(_wdiff);\
    ASSERTSTREQ("", _wdiff.c_str())

//#define ASSERT_OUTPUT() \
//    LOAD(_output, FILEOUTPUT); \
//    LOAD(_expected, FILEEXPECTED);\
//    strcpy(REAL_OUTPUT, _output.c_str()); \
//    strcpy(EXPECTED_OUTPUT, _expected.c_str()); \
//    ASSERT_INTEGRATION_CHECK_R(EXPECTED_OUTPUT,REAL_OUTPUT)


/**
 * @brief Checks if the previous test has failed, in this case, skip the following tests
 * otherwise, report the test and record its outcome
 */
#define SKIP_AND_REPORT(MESSAGE, ...) \
    SKIP_IF_FAILED_BEFORE();\
    REPORT_UNIT_TEST(MESSAGE, __VA_ARGS__);\
    if(__VA_ARGS__) {\
        PASS_TEST();\
    } else {\
        FAIL_TEST();\
    } 

/**
 * @brief Just report the test and record its outcome
 */
#define CONTINUE_AND_REPORT(MESSAGE, ...) \
 REPORT_UNIT_TEST(MESSAGE, __VA_ARGS__);\
    if(__VA_ARGS__) {\
        PASS_TEST();\
    } else {\
        FAIL_TEST();\
    } 

/**
 * @brief Checks if the previous test has failed, 
 * otherwise, report the test and record its outcome.
 * If the previous tests has failed, it does not stop the following tests
 */
#define DONT_FAIL_AND_REPORT(MESSAGE, ...) \
    SKIP_IF_FAILED_BEFORE();\
    REPORT_UNIT_TEST(MESSAGE, __VA_ARGS__);\
    if(__VA_ARGS__) {\
        PASS_TEST();\
    } else {\
        PASS_TEST();\
    } 


//
// ASSERTIONS THAT JUST REPORT . If a test fails, the next ones are executed, 
// the whole set fails
//
#define ASSERT_TRUE_R(...) \
    CONTINUE_AND_REPORT(#__VA_ARGS__ " must have been true", __VA_ARGS__);\
    ASSERTNE(false, __VA_ARGS__)

#define ASSERT_FALSE_R(...) \
    CONTINUE_AND_REPORT(#__VA_ARGS__  " must have been false", ! __VA_ARGS__);\
    ASSERTEQ(false,  __VA_ARGS__ )

#define ASSERT_EQ_R(expr1, expr2) \
    CONTINUE_AND_REPORT(#expr1 " must have been equal to " #expr2 , expr1 == expr2);\
    ASSERTEQ(expr1, expr2)

#define ASSERT_STREQ_R(expr1, expr2) \
    CONTINUE_AND_REPORT(#expr1 " must have been equal to " #expr2 , !strcmp(expr1,expr2));\
    ASSERTSTREQ(expr1, expr2)

#define ASSERT_NE_R(expr1, expr2) \
    CONTINUE_AND_REPORT(#expr1 " must have been equal to " #expr2 , expr1 != expr2);\
    ASSERTNE(expr1, expr2)

#define ASSERT_STRNE_R(expr1, expr2) \
    CONTINUE_AND_REPORT(#expr1 " must have been equal to " #expr2 , strcmp(expr1,expr2));\
    ASSERTSTRNE(expr1, expr2)

//
// Assertions that fail and report. It a test fails, the next ones are skipped 
// whole set fails
//

#define SKIP_ASSERT_TRUE_R(...) \
    SKIP_AND_REPORT(#__VA_ARGS__ " must have been true", __VA_ARGS__);\
    ASSERTNE(false, __VA_ARGS__)

#define SKIP_ASSERT_FALSE_R(...) \
    SKIP_AND_REPORT(#__VA_ARGS__  " must have been false", ! __VA_ARGS__);\
    ASSERTEQ(false,  __VA_ARGS__ )

#define SKIP_ASSERT_EQ_R(expr1, expr2) \
    SKIP_AND_REPORT(#expr1 " must have been equal to " #expr2 , expr1 == expr2);\
    ASSERTEQ(expr1, expr2)

#define SKIP_ASSERT_STREQ_R(expr1, expr2) \
    SKIP_AND_REPORT(#expr1 " must have been equal to " #expr2 , !strcmp(expr1,expr2));\
    ASSERTSTREQ(expr1, expr2)  

#define SKIP_ASSERT_STRNE_R(expr1, expr2) \
    SKIP_AND_REPORT(#expr1 " must have been equal to " #expr2 , strcmp(expr1,expr2));\
    ASSERTSTRNE(expr1, expr2)  

//
// Assertions that do not fail. If a test fail, it does not affect the whole
// set
//
#define EXPECT_TRUE_R(...) \
    DONT_FAIL_AND_REPORT(#__VA_ARGS__  " must have been true", __VA_ARGS__);\
    EXPECTNE(false, __VA_ARGS__)

#define EXPECT_FALSE_R(...) \
    DONT_FAIL_AND_REPORT(#__VA_ARGS__  " must have been false", ! __VA_ARGS__);\
    EXPECTEQ(false,  __VA_ARGS__ )

#define EXPECT_EQ_R(expr1, expr2) \
    DONT_FAIL_AND_REPORT(#expr1 " must have been equal to " #expr2 , expr1 == expr2);\
    EXPECTEQ(expr1, expr2)

#define EXPECT_STREQ_R(expr1, expr2) \
    DONT_FAIL_AND_REPORT(#expr1 " must have been equal to " #expr2 , !strcmp(expr1,expr2));\
    EXPECTSTREQ(expr1, expr2)

//
// Specially devoted to memory checks. If memory leaks appear, then 
//
#define SKIP_ASSERT_MEM_R(expr1, expr2) \
    CHECK_MEMORY_LEAKS();\
    ASSERTTRUE(strcmp(expr1, expr2)==0)

/////////////////////////////////////////////
// Reporting
/////////////////////////////////////////////

/**
 * Draws the head of the memory leak report
 */
#define HEAD_REPORT() \
    do{\
    std::string sproject;\
    LOAD(sproject,"./.projectname");\
    if (__defReport) {\
        SAVE((string)"# TESTS REPORT OF PROJECT "+sproject, FILEREPORT);\
        APPEND("\nThis is the list of tests of the project\n ", FILEREPORT);\
        APPEND("\n| ID | NAME | DESCRIPTION |\n", FILEREPORT); \
        APPEND("| :----- |:------ | :---- |\n", FILEREPORT); \
    }\
    else {\
        SAVE((string)"# OUTCOME OF TESTS FOR PROJECT "+sproject, FILEREPORT); \
        APPEND("\nAs of " __DATE__ " " __TIME__ "\n", FILEREPORT);\
        APPEND("\n| ID | NAME | RESULT | COMMENTS |\n", FILEREPORT); \
        APPEND("| :----- |:------ | :---: | :---: |\n", FILEREPORT); \
    }\
} while(0);

/**
 * @brief Draws the first columns of every row in the memory leak report
 */
//#define HEAD_REPORT_ROW() \
//    do {\
//    std::string head ="";\
//    __nReport++;\
//    head = head + "| CHECK#"+std::to_string(__nReport)+" "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ " | ";\
//    APPEND(head, FILEREPORT);\
//    }while(0);

#define UPDATEIDTEST()\
    do {\
    deltaFCounter("__nReport", (+1));\
    std::string testname, current=::testing::UnitTest::GetInstance()->current_test_info()->name();\
    LOAD(testname,"__nTestname");\
    if (testname != current){\
        SAVE(current,"__nTestname");\
        resetFCounter("__nReport");\
        deltaFCounter("__nReport", (+1));\
        deltaFCounter("__nTest", (+1));\
    }\
    } while(0);

#define IDTEST(label) \
    do {\
    int ncheck, ntest;\
    getFCounter("__nReport", ncheck);\
    getFCounter("__nTest", ntest);\
    label=std::to_string(ntest)+"::"+std::to_string(ncheck);\
    }while(0);


/**
 * @brief Report the success or failure of a test
 */
#define REPORT_UNIT_TEST(MESSAGE, ...) \
    do {\
    std::string RTHead ="";\
    UPDATEIDTEST();\
    IDTEST(idtest);\
    if (! __defReport) {\
        if(__VA_ARGS__) {\
            RTHead = RTHead + "| "+ idtest +" | "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ " | ";\
            APPEND(RTHead, FILEREPORT);\
            APPEND("PASSED | OK |\n", FILEREPORT);\
        } else {\
            RTHead = RTHead + "| "+ idtest +" | **"+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ "** | ";\
            APPEND(RTHead, FILEREPORT);\
            APPEND("**FAILED** | **" #MESSAGE "** |\n", FILEREPORT);\
        } \
    } else {\
        RTHead = RTHead + "| "+ idtest +" | "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ " | ";\
        APPEND(RTHead, FILEREPORT);\
    }\
    }while(0);

#define REPORT_INTEGRATION_TEST(MESSAGE) \
    do {\
    std::string RTHead ="";\
    UPDATEIDTEST();\
    IDTEST(idtest);\
    if (! __defReport) {\
        if(MESSAGE == "") {\
            RTHead = RTHead + "| "+ idtest +" | "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ " | ";\
            APPEND(RTHead, FILEREPORT);\
            APPEND("PASSED | OK |\n", FILEREPORT);\
        } else {\
            std::string msg;\
            RTHead = RTHead + "| "+ idtest +" | **"+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ "** | ";\
            APPEND(RTHead, FILEREPORT);\
            msg=(string)"**FAILED** | **"+MESSAGE +"** |\n";\
            APPEND(msg, FILEREPORT);\
        } \
    } else {\
        RTHead = RTHead + "| "+ idtest +" | "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ " | ";\
        APPEND(RTHead, FILEREPORT);\
    }\
    }while(0);

#define REPORT_SKIPPED_TEST() \
    do {\
    std::string STHead ="";\
    std::string idtest;\
    UPDATEIDTEST();\
    IDTEST(idtest);\
    STHead = STHead + "| "+ idtest + "| **"+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ "** | ";\
    APPEND(STHead, FILEREPORT);\
    APPEND("**SKIPPED** | **The previous test failed** |\n", FILEREPORT);\
    }while(0);



#else
#define TESTING_FLAG true
#define INIT_MAIN() ;
#define RETURN_MAIN(X)  return X;
#endif

#define MAIN_BODY() \
INIT_MAIN(); \
if(TESTING_FLAG)

#endif

/*
     #define FILEREPORT "./doc/markdown/TestDescription.md"
    #define __defReport true
    #define ASSERTNE(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define ASSERTEQ(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define ASSERTTRUE(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define ASSERTFALSE(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define ASSERTSTREQ(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define ASSERTSTRNE(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define EXPECTNE(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define EXPECTEQ(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define EXPECTSTREQ(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
    #define EXPECTSTRNE(...) \
        ofstream ofreport(FILEREPORT, std::ios_base::app);\
        ofreport
 */
