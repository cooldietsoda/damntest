#pragma once
//#define DAMN_ASSERT(value) DamnTest::assert(value, __FILE__, __LINE__)

namespace DamnTest {
using TestCaseCallbackT = void (*)();

void assertTrue(bool value);
void assertFalse(bool value);

void addTestCase(const char* caseName, TestCaseCallbackT caseCallback);

const char* getTestSuiteName();
void exit(int status);
void puts(const char* msg);
void putTestCases();

void preTestCase();
void postTestCase();

void preTestSuite();
void postTestSuite();
}
