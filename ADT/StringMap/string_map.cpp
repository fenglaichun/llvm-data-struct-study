#include "llvm/ADT/StringMap.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"
using namespace std;
using namespace llvm;

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "StringMap testing\n");

  raw_ostream &os = llvm::errs();

  Timer t("timer", "record running time");
  {
    TimeRegion tr(t);
    int *a = new int[1000000000];
    for (int i = 0; i < 10000; ++i) {
      StringMap<int> test;
      test["feng"] = 5;
      test["lai"] = 6;
      test["chun"] = 7;
    }
  }
  return 0;
}
