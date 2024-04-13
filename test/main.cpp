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


namespace DamnTest {
const char* getTestSuiteName() {
  return "VERIFICATION";
}

void puts(const char* msg) {
  printf("%s", msg);
}

void exit(int status) {
  ::exit(status);
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