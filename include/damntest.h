#pragma once
/**
 * @brief Handy macro which automatically insert source filename
 * and line number before calling an assert
 * @see assert
 */
#define DAMN_ASSERT(value) DamnTest::assert(value, __FILE__, __LINE__)

namespace DamnTest {
using TestCaseCallbackT = void (*)();

/**
 * @brief Checks value and terminates program if it's false
 * @param value - input value
 * @param filename - source filename (optionally)
 * @param lineN - source line (optionally)
 */
void assert(bool value, const char* filename = nullptr, int lineN = 0);

/**
 * @brief Add test case to the execution list
 * @param caseName - name of a test case. String should be available entire execution time.  
 * @param caseCallback - callback which will be called to start a test.
 */
void addTestCase(const char* caseName, TestCaseCallbackT caseCallback);

/**
 * @brief Getter for a name of test suite
 * Must be defined by user!
 * @return String that represents test suite name
 */
const char* getTestSuiteName();

/**
 * @brief Immediately stops execution of a program.
 * Could be implemented by redirecting to std::exit(int)
 * Must be defined by user!
 * @param status - integer status
 */
void exit(int status);

/**
 * @brief Writes string to stdout.
 * Could be implemented by redirecting to std::puts(const char*)
 * Must be defined by user!
 * @param msg - string to output
 */
void puts(const char* msg);

/**
 * @brief Registers all test cases to be 
 * validated for a given test suite
 * Must be defined by user!
 */
void putTestCases();

/**
 * @brief Routine to execute before every test case
 * @return true - on success
 * @return false - if any error occurred. Testing will be immediately stopped.
 */
bool preTestCase();

/**
 * @brief Routine to execute after every test case
 * @return true - on success
 * @return false - if any error occurred. Testing will be immediately stopped.
 */
bool postTestCase();

/**
 * @brief Routine to execute before running test suite
 * @return true - on success
 * @return false - if any error occurred. Testing will be immediately stopped.
 */
bool preTestSuite();

/**
 * @brief Routine to execute after running test suite
 * @return true - on success
 * @return false - if any error occurred. Testing will be immediately stopped.
 */
bool postTestSuite();
}
