#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"
#include <string>
#include <cstdint>
using namespace std;
using namespace llvm;
// 优点：
// 缺点：map中在保存元素相同的情况下，遍历map的顺序会随着插入的顺序的不同而发生变化
//       如果要得到稳定的迭代顺序，需使用std::map
// 适用场景：字符串为key的map场景
class DenseMapTest {
  void Construct() {
    // 缺省构造函数
    DenseMap<string *, int> dMap0;
  }
  void Insert() {
  }
  void Delete() {
  }
  void LookUp() {
  }
  void Traverse(const StringMap<uint16_t> &strMap, StringRef mapName) {
  }

public:
  void InterfaceTest() {
    Construct();
    Insert();
    Delete();
    LookUp();
  }

private:
  raw_ostream &os = llvm::errs();
};

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "StringMap testing\n");

  raw_ostream &os = llvm::errs();

  Timer t("timer", "record running time");
  {
    TimeRegion tr(t);
    DenseMapTest Test;
    DenseMap<unsigned short, unsigned short> TestMap;
    TestMap[0xfff] = 5;
    TestMap[0xff1] = 4;
    os << TestMap[0xfff] << "\n";
    Test.InterfaceTest();
  }
  return 0;
}
