/**
 * @file MPtest.h
 * @brief Extension to Googletest to cover formatted reporting of tests
 * @author DECSAI
  */

#ifndef MP__TESTS__
#define MP__TESTS__


//#define __DEBUG__

#ifdef __DEBUG__
#define __TESTING__
#endif 

#define __TESTING__

#ifndef __RELEASE__
#define CVAL std::clog 
#define REPORT_DATA(VAR) CVAL << std::endl<< "["<<#VAR<<"] "<< VAR.reportData() << std::endl;
#define REPORT_TEXT(TEXT) CVAL << TEXT << std::endl;
#else
#define CVAL std::cout
#define REPORT_DATA(VAR) ;
#define REPORT_TEXT(TEXT) ;
#endif


#ifdef __TESTING__


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <regex>
#define __PATH__ "./dist/Debug/GNU-Linux/"
#define __TIME_OUT_CALL__ "timeout --preserve-status -k "
#define __BASE__ __COUNTER__
#define FILEINPUT "./tests/validation/" + stestname + ".keyboard"
#define FILEOUTPUT "./tests/output/" + stestname + ".output"
#define FILEKEYBOARD "./tests/validation/" + stestname + ".keyboard"
#define FILECOUT "./tests/output/" + stestname + ".cout"
#define FILEEXPECTED "./tests/validation/" + stestname + ".expected"
#define FILEMLEAKS "./tests/output/" + stestname + ".mleaks.compact"
#define FILEMLEAKSMD "./tests/output/" + stestname + ".mleaks.simplified.md"
#define FILESTOP "./tests/output/stop.detected"
#define FILESTOPMLEAKS "./tests/output/mleaks.detected"
#define FILEREPORT "./tests/TestReport.md"
#define FILEREPORT_APPEND "./tests/output/TestReportAppend.md"
#define __VALGRIND__ "-valgrind"
#define __DRMEMORY__ "-drmemory"
#define __RUN_OUTPUT__ FILEOUTPUT("output")
#define MAX_STRING_OUTPUT 1000

#define EMPTYS  ""
#define SPACE " "
#define NEWLINE "\n"
#define TESTING_FLAG false

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
    LTRIM(STRINGVAR); \
    RTRIM(STRINGVAR); \
    REPLACE(STRINGVAR,"  "," ")

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


/////////////////////////////////////////////
// FAIL / SUCCESS OF TESTS
/////////////////////////////////////////////


/**
 * @brief If the previous tests failed, then
 */
#define CHECK_FAILED_TEST() \
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
    #define CHECK_MEMORY_LEAKS() \
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
    HEAD_REPORT() \
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
#define DEF_EXECUTION_ENVIRONMENT(NAME) \
    CHECK_FAILED_TEST();\
    std::string stestname= #NAME; \
    long timeout=30;\
    bool breakpoint=false;\
    std::string _output, _expected, __PROJECT__, __BIN__; \
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
    ASSERT_OUTPUT() 

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
    ASSERT_OUTPUT()

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
    ASSERT_OUTPUT() 


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
    CHECK_MEMORY_LEAKS();\
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
    }

/**
 * @brief Checks if the previous execution has produced a memory leak and
 * reports it
 */
#define HAS_MEMORY_LEAKS() \
    do {\
    std::string head ="";\
    LOAD(leakreport,FILEMLEAKS);\
    if(leakreport == "") {\
        cout << "\n[       OK ] "<<stestname << leakdetector << std::endl;\
        head = head + "| "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+ ::testing::UnitTest::GetInstance()->current_test_info()->name()+ leakdetector+" | ";\
        APPEND(head, FILEREPORT);\
        APPEND("PASSED | NO LEAKS |\n", FILEREPORT);\
        PASS_TEST();\
        PASS_MEMORY_LEAKS();\
    } else {\
        head = head + "| **"+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+ ::testing::UnitTest::GetInstance()->current_test_info()->name()+ leakdetector+"** | ";\
        APPEND(head, FILEREPORT);\
        APPEND("**FAILED** | **HAS MEMORY LEAKS** (!) |\n", FILEREPORT);\
        REPLACE(leakreport,"#[", "\n[");\
           cout << leakreport <<endl;\
        FAIL_TEST();\
        FAIL_MEMORY_LEAKS();\
        LOAD(head,FILEMLEAKSMD);\
        SAVE(head,FILEREPORT_APPEND);\
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
#define ASSERT_OUTPUT() \
    LOAD(_output, FILEOUTPUT); \
    LOAD(_expected, FILEEXPECTED);\
    strcpy(REAL_OUTPUT, _output.c_str()); \
    strcpy(EXPECTED_OUTPUT, _expected.c_str()); \
    SKIP_ASSERT_STREQ_R(EXPECTED_OUTPUT,REAL_OUTPUT)


/**
 * @brief Checks if the previous test has failed, in this case, skip the following tests
 * otherwise, report the test and record its outcome
 */
#define FAIL_AND_REPORT(MESSAGE, ...) \
    CHECK_FAILED_TEST();\
    REPORT_TEST(MESSAGE, __VA_ARGS__);\
    if(__VA_ARGS__) {\
        PASS_TEST();\
    } else {\
        FAIL_TEST();\
    } 

/**
 * @brief Just report the test and record its outcome
 */
#define CONTINUE_JUST_REPORT(MESSAGE, ...) \
    REPORT_TEST(MESSAGE, __VA_ARGS__);\
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
    CHECK_FAILED_TEST();\
    REPORT_TEST(MESSAGE, __VA_ARGS__);\
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
    CONTINUE_JUST_REPORT(#__VA_ARGS__ " must have been true", __VA_ARGS__);\
    ASSERT_TRUE(__VA_ARGS__)

#define ASSERT_FALSE_R(...) \
    CONTINUE_JUST_REPORT(#__VA_ARGS__  " must have been false", ! __VA_ARGS__);\
    ASSERT_FALSE(  __VA_ARGS__ )

#define ASSERT_EQ_R(expr1, expr2) \
    CONTINUE_JUST_REPORT(#expr1 " must have been equal to " #expr2 , expr1 == expr2);\
    ASSERT_EQ(expr1, expr2)

#define ASSERT_STREQ_R(expr1, expr2) \
    CONTINUE_JUST_REPORT(#expr1 " must have been equal to " #expr2 , !strcmp(expr1,expr2));\
    ASSERT_STREQ(expr1, expr2)

//
// Assertions that fail and report. It a test fails, the next ones are skipped 
// whole set fails
//
#define SKIP_ASSERT_TRUE_R(...) \
    FAIL_AND_REPORT(#__VA_ARGS__ " must have been true", __VA_ARGS__);\
    ASSERT_TRUE(__VA_ARGS__)

#define SKIP_ASSERT_FALSE_R(...) \
    FAIL_AND_REPORT(#__VA_ARGS__  " must have been false", ! __VA_ARGS__);\
    ASSERT_FALSE(  __VA_ARGS__ )

#define SKIP_ASSERT_EQ_R(expr1, expr2) \
    FAIL_AND_REPORT(#expr1 " must have been equal to " #expr2 , expr1 == expr2);\
    ASSERT_EQ(expr1, expr2)

#define SKIP_ASSERT_STREQ_R(expr1, expr2) \
    FAIL_AND_REPORT(#expr1 " must have been equal to " #expr2 , !strcmp(expr1,expr2));\
    ASSERT_STREQ(expr1, expr2)

//
// Assertions that do not fail. If a test fail, it does not affect the whole
// set
//
#define EXPECT_TRUE_R(...) \
    DONT_FAIL_AND_REPORT(#__VA_ARGS__  " must have been true", __VA_ARGS__);\
    EXPECT_TRUE( __VA_ARGS__ )

#define EXPECT_FALSE_R(...) \
    DONT_FAIL_AND_REPORT(#__VA_ARGS__  " must have been false", ! __VA_ARGS__);\
    EXPECT_FALSE( __VA_ARGS__ )

#define EXPECT_EQ_R(expr1, expr2) \
    DONT_FAIL_AND_REPORT(#expr1 " must have been equal to " #expr2 , expr1 == expr2);\
    EXPECT_EQ(expr1, expr2)

#define EXPECT_STREQ_R(expr1, expr2) \
    DONT_FAIL_AND_REPORT(#expr1 " must have been equal to " #expr2 , !strcmp(expr1,expr2));\
    EXPECT_STREQ(expr1, expr2)

//
// Specially devoted to memory checks. If memory leaks appear, then 
//
#define SKIP_ASSERT_MEM_R(expr1, expr2) \
    HAS_MEMORY_LEAKS();\
    ASSERT_TRUE(strcmp(expr1, expr2)==0)

/////////////////////////////////////////////
// Reporting
/////////////////////////////////////////////

/**
 * Draws the head of the memory leak report
 */
#define HEAD_REPORT() \
    SAVE("# TEST REPORT " __DATE__ " " __TIME__ "\n", FILEREPORT); \
    APPEND("| TEST | RESULT | COMMENTS |\n", FILEREPORT); \
    APPEND("| :------ | :---: | :---: |\n", FILEREPORT); 

/**
 * @brief Draws the first columns of every row in the memory leak report
 */
#define HEAD_REPORT_ROW() \
    do {\
    std::string head ="";\
    head = head + "| "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ " | ";\
    APPEND(head, FILEREPORT);\
    }while(0);

/**
 * @brief Report the success or failure of a test
 */
#define REPORT_TEST(MESSAGE, ...) \
    do {\
    std::string head ="";\
    if(__VA_ARGS__) {\
        head = head + "| "+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ " | ";\
        APPEND(head, FILEREPORT);\
        APPEND("PASSED | OK |\n", FILEREPORT);\
    } else {\
        head = head + "| **"+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ "** | ";\
        APPEND(head, FILEREPORT);\
        APPEND("**FAILED** | **" #MESSAGE "** |\n", FILEREPORT);\
    } \
    }while(0);

#define REPORT_SKIPPED_TEST() \
    do {\
    std::string head ="";\
    head = head + "| **"+::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name()+"."+::testing::UnitTest::GetInstance()->current_test_info()->name()+ "** | ";\
    APPEND(head, FILEREPORT);\
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

