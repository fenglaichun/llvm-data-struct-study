#include "llvm/ADT/Twine.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"
#include <string>
using namespace std;
using namespace llvm;
// 参考资料：https://llvm.org/docs/ProgrammersManual.html#llvm-adt-twine-h
//
// Twine 主要用来进行字符串的连接
// 优点：并不真正的创建一个对象存储连接字符串，从而提高性能，
//       即便是连接了一个整形数字，也无需创建一个临时的string对象保存中间结果。
// 原理：通过在栈上创建Twine类型的实例，内部以二叉树结构存储，
//       在使用的时候再先序遍历得到一个连接字符串
//
// 应用场景: 以常量引用的方式作为函数的参数
class TwineTest {
public:
  TwineTest() = default;
  ~TwineTest() = default;
  void Test(raw_ostream &os) {
    char str1[] = "the first code ";
    char c = '=';
    unsigned i = 100;
    string str2 = " scores\n";
    StringRef strRef1(str2);
    const Twine twine1(str1);
    const Twine twine2 =
        twine1 + /*explicit constructor*/ Twine(c) + " " + Twine(i) + strRef1;
    twine2.print(os);
  }
};

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "StringMap testing\n");

  raw_ostream &os = llvm::errs();

  Timer t("timer", "record running time");
  {
    TimeRegion tr(t);
    TwineTest test;
    test.Test(os);
  }
  return 0;
}
