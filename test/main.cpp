#include <damntest.h>

void sampleTest() {
  using namespace DamnTest;
  assertTrue(false);
}

namespace DamnTest {
const char* getTestSuiteName() {
  return "VERIFICATION";
}

DamnTest::LogOutputCallback getLogOutputCallback() {
  return nullptr;
}

void putTestCases() {
  addTestCase("sampleTest", sampleTest);
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