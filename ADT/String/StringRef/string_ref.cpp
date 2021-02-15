#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"
#include <string>
using namespace std;
using namespace llvm;
// 参考资料：https://llvm.org/docs/ProgrammersManual.html#llvm-adt-stringref-h
//           https://llvm.org/docs/ProgrammersManual.html#string-apis
// StringRef 用来表达对一个常量字符串的引用
// 优点：避免堆分配造成额外的性能损失
//       支持和string 类似的API
// 注意点: 被引用的字符串的生命周期要长于StringRef实例
//         通常存储StringRef实例是不安全的
// StringRef开销很小，在作为函数参数传递时，使用值传递
class StringRefTest {
public:
  StringRefTest() = default;
  ~StringRefTest() = default;
  bool CheckEqualOfFirstAndLast(StringRef in) {
    if (in.empty())
      return false;
    if (in.size() == 1)
      return true;
    if (in.front() == in.back()) {
      return true;
    } else {
      return false;
    }
  }
};

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "StringMap testing\n");

  raw_ostream &os = llvm::errs();

  Timer t("timer", "record running time");
  {
    TimeRegion tr(t);
    StringRefTest test;
    // case 1:
    char str1[] = "hello, world";
    StringRef strRef1(str1);
    // case 2:
    char str2[] = "hello,h";
    StringRef strRef2(str2, /*sizeof(str2)*/ 7);

    string str3 = "good luck";
    StringRef strRef3(str3);

    os << "The first and last char of " << strRef1 << " is equal? "
       << (test.CheckEqualOfFirstAndLast(strRef1) ? "yes\n" : "no\n");

    os << "The first and last char of " << strRef2 << " is equal? "
       << (test.CheckEqualOfFirstAndLast(strRef2) ? "yes\n" : "no\n");
    os << "The first and last char of " << strRef3 << " is equal? "
       << (test.CheckEqualOfFirstAndLast(strRef3) ? "yes\n" : "no\n");
  }
  return 0;
}
