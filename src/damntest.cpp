#include <damntest.h>

using uint8_t = unsigned char;

namespace {
using namespace DamnTest;

struct TestCase {
  TestCaseCallbackT callback;
  char name[16];
};

constexpr uint8_t cTestCasesMax = 64;
uint8_t gTestCasesN = 0;
TestCase gTestCases[cTestCasesMax];

LogOutputCallback gLogOutputCallback = nullptr;
ExitCallbackT gExitCallback = nullptr;

void log(const char* message) {
  if (!gLogOutputCallback) {
    return;
  }

  gLogOutputCallback(message);
}

void fail() {
  log("[ERROR] Test failed!");
  if (!gExitCallback) {
    log("[ERROR] Cannot find exit function callback!");
    return;
  }

  gExitCallback();
}

void strcpyn(char* dest, uint8_t destSize, const char* src) {
  for (uint8_t i=0; i<destSize-1; i++) {
    if (src[i]=='\0')  {
      break;
    }

    dest[i]=src[i];
  }

  dest[destSize-1] = '\0';
}
}

namespace DamnTest {
void assertTrue(const bool value) {
  if (!value) fail();
}

void assertFalse(const bool value) {
  if (value) fail();
}

void addTestCase(const char* caseName, TestCaseCallbackT caseCallback) {
  if (gTestCasesN >= cTestCasesMax) {
    log("[WARNING] Cannot add more cases! Your case wouldn't be checked\n");
    return;
  }

  gTestCases[gTestCasesN].callback = caseCallback;
  strcpyn(gTestCases[gTestCasesN].name, sizeof(gTestCases[gTestCasesN].name), caseName);
  gTestCasesN++;
}
}

int main() {
  gLogOutputCallback = getLogOutputCallback();
  gExitCallback = getExitCallback();

  if (!gExitCallback) {
    log("[ERROR] Cannot find exit callback! Quitting...");
    return -1;
  }

  log("[INFO] Preparing to run suite: '"); log(getTestSuiteName()); log("'\n");
  
  putTestCases();
  log("[INFO] Cases to be verified: \n");
  //log(itoa(gTestCases.size()));

  log("[INFO] Running pre test suite...\n");
  preTestSuite();
  for (uint8_t testCaseIdx=0; testCaseIdx<gTestCasesN; testCaseIdx++) {
    log("[INFO] Running pre test case...\n");
    preTestCase();
    log("[INFO] Running '"); log(gTestCases[testCaseIdx].name); log("' test.\n");
    gTestCases[testCaseIdx].callback();
    log("[INFO] Success!\n");
    log("[INFO] Running post test case...\n");
    postTestCase();
  }
  log("[INFO] Running post test suite...\n");
  postTestSuite();

	log("[INFO] All tests passed!");
  return 0;
}