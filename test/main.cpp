#include <damntest.h>
#include <cstdio>

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

void log(const char* msg) {
  printf("%s", msg);
}

namespace DamnTest {
const char* getTestSuiteName() {
  return "VERIFICATION";
}

DamnTest::LogOutputCallback getLogOutputCallback() {
  return &log;
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