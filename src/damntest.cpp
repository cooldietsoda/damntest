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

void fail(const char* filename = nullptr, int lineN = 0) {
  log("Test failed!\n", ELogType::eError);

  if (filename) {
    log("File: "); log(filename, ELogType::eNoPrefix); log("\n", ELogType::eNoPrefix); 
  }

  if (lineN) {
    log("Line: "); log(utils::itoa(lineN), ELogType::eNoPrefix); log("\n", ELogType::eNoPrefix);
  }

  DamnTest::exit(-1);
}
}

namespace DamnTest {
void assert(bool value, const char* filename, int lineN) {
  if (!value) {
    fail(filename, lineN);
  }
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
  if (!preTestSuite()) {
    log("Failed to complete pre test suite!", ELogType::eError);
    exit(-1);
    return -1; // Just in case...
  }

  for (uint8_t testCaseIdx=0; testCaseIdx<gTestCasesN; testCaseIdx++) {
    log("Test "); log(utils::itoa(testCaseIdx+1), ELogType::eNoPrefix); log("/", ELogType::eNoPrefix); 
    log(utils::itoa(gTestCasesN), ELogType::eNoPrefix); log(": '", ELogType::eNoPrefix);
    log(gTestCases[testCaseIdx].name, ELogType::eNoPrefix); log("'\n", ELogType::eNoPrefix);
    
    log("Running pre test case...\n");
    if (!preTestCase()) {
      log("Failed to complete pre test case!", ELogType::eError);
      exit(-1);
      return -1; // Just in case...
    }

    log("Running test...\n");
    gTestCases[testCaseIdx].callback();
    log("Success!\n");

    log("Running post test case...\n");
    if (!postTestCase()) {
      log("Failed to complete post test case!", ELogType::eError);
      exit(-1);
      return -1; // Just in case...
    }
  }

  log("Running post test suite...\n");
  if (!postTestSuite()) {
    log("Failed to complete post test suite!", ELogType::eError);
    exit(-1);
    return -1; // Just in case...
  }

	log("All tests passed!");
  return 0;
}