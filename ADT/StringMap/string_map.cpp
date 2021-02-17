#include "llvm/ADT/StringMap.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdint>
using namespace std;
using namespace llvm;
// 优点：
// 缺点：map中在保存元素相同的情况下，遍历map的顺序会随着插入的顺序的不同而发生变化
//       如果要得到稳定的迭代顺序，需使用std::map
// 适用场景：字符串为key的map场景
class StringMapTest {
  void Construct() {
    // 缺省构造函数
    StringMap<uint16_t> map1;
    map1["hello"] = 1;
    map1["world"] = 2;
    Traverse(map1, "map1");
    // 使用初始化列表进行构造
    StringMap<uint16_t> map2 = {{"red", 1}, {"green", 2}, {"blue", 3}};
    Traverse(map2, "map2");
  }
  void Insert() {
    StringMap<uint16_t> insertMap;
    insertMap["llvm"] = 1;
    insertMap["gcc"] = 2;
    // insert pair<StringRef, ValueTy>
    insertMap.insert(std::make_pair("c++", 3));
    auto ret = insertMap.insert(std::make_pair("llvm", 2));
    if (ret.second) {
      os << "llvm is new key in insertMap\n";
    } else {
      os << "llvm has been inserted in insertMap\n";
    }
    ret = insertMap.insert(std::make_pair("python", 2));
    if (ret.second) {
      os << "python is new key in insertMap\n";
    } else {
      os << "python has been inserted in insertMap\n";
    }
    Traverse(insertMap, "insertMap");
  }
  void Delete() {
    StringMap<uint16_t> colorMap = {{"red", 1}, {"green", 2}};
    colorMap["purple"] = 4;
    colorMap["blue"] = 3;
    os << "color map before deleted\n";
    Traverse(colorMap, "colorMap");
    colorMap.erase("green");
    os << "color map after deleted\n";
    Traverse(colorMap, "colorMap");

    StringMap<uint16_t> colorMapClone = {
        {"purple", 4}, {"blue", 3}, {"green", 2}, {"red", 1}};
    Traverse(colorMapClone, "colorMapClone");
  }
  void LookUp() {
    StringMap<uint16_t> colorMap = {{"red", 1}, {"green", 2}, {"blue", 3}};
    if (colorMap.find("red") != colorMap.end()) {
      os << "red is in colorMap\n";
    } else {
      os << "red is not in colorMap\n";
    }

    if (colorMap.find("purple") != colorMap.end()) {
      os << "purple is in colorMap\n";
    } else {
      os << "purple is not in colorMap\n";
    }
  }
  void Traverse(const StringMap<uint16_t> &strMap, StringRef mapName) {
    // 打印map1, 获取key和value的方式和std::map存在差异
    os << mapName << "\n";
    for (auto it = strMap.begin(); it != strMap.end(); ++it) {
      os << "key: " << it->getKey() << " value: " << it->second << "\n";
    }
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
    StringMapTest Test;
    Test.InterfaceTest();
  }
  return 0;
}
