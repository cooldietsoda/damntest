#pragma once
//#define DAMN_ASSERT(value) DamnTest::assert(value, __FILE__, __LINE__)

namespace DamnTest {
using TestCaseCallbackT = void (*)();
using LogOutputCallback = void (*)(const char*);

void assertTrue(bool value);
void assertFalse(bool value);

void addTestCase(const char* caseName, TestCaseCallbackT caseCallback);

const char* getTestSuiteName();
DamnTest::LogOutputCallback getLogOutputCallback();
void putTestCases();

void preTestCase();
void postTestCase();

void preTestSuite();
void postTestSuite();
}
