#include <damntest.h>
#include <cstdio>
#include <cstdlib>

void sampleTest1() {
  using namespace DamnTest;
  assertTrue(true);
}

void sampleTest2() {
  using namespace DamnTest;
  assertFalse(false);
}

void sampleTest3() {
  using namespace DamnTest;
  assertTrue(false);
}

void logToStd(const char* msg) {
  printf("%s", msg);
}

void exitToStd() {
  exit(-1);
}

namespace DamnTest {
const char* getTestSuiteName() {
  return "VERIFICATION";
}

DamnTest::LogOutputCallback getLogOutputCallback() {
  return &logToStd;
}

DamnTest::ExitCallbackT getExitCallback() {
  return &exitToStd;
}

void putTestCases() {
  addTestCase("sampleTest1", sampleTest1);
  addTestCase("sampleTest2", sampleTest2);
  addTestCase("sampleTest3", sampleTest3);
}

void preTestCase() {

}

void postTestCase() {

}

void preTestSuite() {

}

void postTestSuite() {

}
}