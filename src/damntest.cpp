#include <damntest.h>
#include <cstdlib>

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

void log(const char* message) {
  if (!gLogOutputCallback) {
    return;
  }
  gLogOutputCallback(message);
}

void fail() {
  log("Test failed!");
  exit(-1);
}
}

namespace DamnTest {
void strcpyn(char* dest, uint8_t destSize, const char* src) {
  for (uint8_t i=0; i<destSize-1; i++) {
    if (src[i]=='\0')  {
      break;
    }

    dest[i]=src[i];
  }

  dest[destSize-1] = '\0';
}

void assertTrue(const bool value) {
  if (!value) fail();
}

void assertFalse(const bool value) {
  if (value) fail();
}

void addTestCase(const char* caseName, TestCaseCallbackT caseCallback) {
  if (gTestCasesN >= gTestCasesMax) {
    log("Cannot add more cases! Your case wouldn't be checked\n");
    return;
  }

  gTestCases[gTestCasesN].callback = caseCallback;
  strcpyn(gTestCases[gTestCasesN].name, sizeof(gTestCases[gTestCasesN].name), caseName);
  gTestCasesN++;
}
}

int main() {
  gLogOutputCallback = getLogOutputCallback();
  log("Suite: '"); log(getTestSuiteName()); log("'\n");
  
  putTestCases();
  log("Cases to be verified: \n");
  //log(itoa(gTestCases.size()));

  log("Running pre test suite...\n");
  preTestSuite();
  for (uint8_t testCaseIdx=0; testCaseIdx<gTestCasesN; testCaseIdx++) {
    log("Running pre test case...\n");
    preTestCase();
    log("Running '"); log(gTestCases[testCaseIdx].name); log("' test.\n");
    gTestCases[testCaseIdx].callback();
    log("Success!\n");
    log("Running post test case...\n");
    postTestCase();
  }
  log("Running post test suite...\n");
  postTestSuite();

	log("All tests passed.");
  return 0;
}