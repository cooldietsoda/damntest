#include <damntest.h>
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <string.h>

namespace {
  using namespace DamnTest;

  LogOutputCallback gLogOutputCallback = nullptr;
  void log(const char* message) {
    if (gLogOutputCallback) {
      gLogOutputCallback(message);
    } else {
      printf("%s", message);
      printf("\n");
    }
  }

  void fail() {
    log("Test failed!");
    exit(EXIT_FAILURE);
  }

  std::set<TestCaseCallbackT> gTestCases;
}

namespace DamnTest {
void assertTrue(const bool value) {
  if (!value) fail();
}

void assertFalse(const bool value) {
  if (value) fail();
}

void addTestCase(const char* caseName, TestCaseCallbackT caseCallback) {
  gTestCases.insert(caseCallback);
}
}

int main() {
  gLogOutputCallback = getLogOutputCallback();
  log("Suite: ");
  log(getTestSuiteName());
  
  putTestCases();
  log("Cases: ");
  //log(itoa(gTestCases.size()));

  preTestSuite();
  for (const auto callback: gTestCases) {
    log("Running '' test.\n");
    preTestCase();
    callback();
    postTestCase();
  }
  postTestSuite();

	log("All tests passed.");
  return 0;
}