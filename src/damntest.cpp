#include <damntest/damntest.h>
#include <stdlib.h>
#include <set>

namespace {
  using namespace DamnTest;

  LogOutputCallback gLogOutputCallback = nullptr;
  void log(const char* message) {
    if (gLogOutputCallback) {
      gLogOutputCallback(message);
    }
  }

  std::set<TestCaseCallbackT> gTestCases;
}

namespace DamnTest {
void assertTrue(const bool value) {
  if (!value) exit(EXIT_FAILURE);
}

void assertFalse(const bool value) {
  if (value) exit(EXIT_FAILURE);
}

void addTestCase(const char* caseName, TestCaseCallbackT caseCallback) {
  gTestCases.insert(caseCallback);
}
}

int main() {
  gLogOutputCallback = getLogOutputCallback();
  log("Suite: ");
  log(getTestSuiteName());
  log("Cases: ");

  for (const auto callback: gTestCases) {
    log("Running '' test.\n");
    callback();
  }

	log("All tests passed.");
  return 0;
}