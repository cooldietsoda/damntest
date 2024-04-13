#include <damntest.h>
#include "utils.h"
#include "common.h"

namespace {
using namespace DamnTest;

struct TestCase {
  TestCaseCallbackT callback;
  char name[16];
};

constexpr uint8_t cTestCasesMax = TESTS_N;
uint8_t gTestCasesN = 0;
TestCase gTestCases[cTestCasesMax];

enum class ELogType {
  eInfo, eWarning, eError, eNoPrefix
};

void log(const char* message, ELogType type = ELogType::eInfo) {
  switch (type) {
    case ELogType::eInfo: DamnTest::puts("[INFO]: "); break;
    case ELogType::eWarning: DamnTest::puts("[WARNING]: "); break;
    case ELogType::eError: DamnTest::puts("[ERROR]: "); break;
    case ELogType::eNoPrefix:
    default: break;
  }

  DamnTest::puts(message);
}

void fail() {
  log("Test failed!\n", ELogType::eError);
  DamnTest::exit(-1);
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
    log("Cannot add more cases! Your case wouldn't be checked\n", ELogType::eWarning);
    return;
  }

  gTestCases[gTestCasesN].callback = caseCallback;
  utils::strcpyn(gTestCases[gTestCasesN].name, sizeof(gTestCases[gTestCasesN].name), caseName);
  gTestCasesN++;
}
}

int main() {
  log("Preparing to run suite: '"); log(getTestSuiteName(), ELogType::eNoPrefix); log("'\n", ELogType::eNoPrefix);
  
  putTestCases();
  log("Cases to be verified: "); log(utils::itoa(gTestCasesN), ELogType::eNoPrefix); log("\n", ELogType::eNoPrefix);

  log("Running pre test suite...\n");
  preTestSuite();

  for (uint8_t testCaseIdx=0; testCaseIdx<gTestCasesN; testCaseIdx++) {
    log("Test "); log(utils::itoa(testCaseIdx+1), ELogType::eNoPrefix); log("/", ELogType::eNoPrefix); 
    log(utils::itoa(gTestCasesN), ELogType::eNoPrefix); log(": '", ELogType::eNoPrefix);
    log(gTestCases[testCaseIdx].name, ELogType::eNoPrefix); log("'\n", ELogType::eNoPrefix);
    log("Running pre test case...\n");
    preTestCase();
    log("Running test...\n");
    gTestCases[testCaseIdx].callback();
    log("Success!\n");
    log("Running post test case...\n");
    postTestCase();
  }

  log("Running post test suite...\n");
  postTestSuite();

	log("All tests passed!");
  return 0;
}