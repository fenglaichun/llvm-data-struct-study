//keyword true and false may not be supported.
// demo1
class C {
  bit V = 1;
}

def X : C;
def Y : C {
  let V = 0;
  string Greeting = "Hello!";
}
//demo2 parameterized class
class FPFormat <bits<3> val> {
  bits<3> Value = val;
}
def NotFP      : FPFormat<0>;
def ZeroArgFP  : FPFormat<1>;
def OneArgFP   : FPFormat<2>;
def OneArgFPRW : FPFormat<3>;
def TwoArgFP   : FPFormat<4>;
def CompareFP  : FPFormat<5>;
def CondMovFP  : FPFormat<6>;
def SpecialFP  : FPFormat<7>;

// demo3
class ModRefVal <bits<2> val> {
  bits<2> Value = val;
}

def None   : ModRefVal<0>;
def Mod    : ModRefVal<1>;
def Ref    : ModRefVal<2>;
def ModRef : ModRefVal<3>;

class ModRefBits <ModRefVal mrv> {
  // Break the value up into its bits, which can provide a nice
  // interface to the ModRefVal values.
  bit isMod = mrv.Value{0};
  bit isRef = mrv.Value{1};
}
// Example uses.
def foo   : ModRefBits<Mod>;
def bar   : ModRefBits<Ref>;
def snork : ModRefBits<ModRef>;
// demo4
class MultiField {
  int X = 0;
  string Y = "multi y";
}
let X = 5, Y = "new multi y" in
def MultiFieldDef : MultiField;

let X = 6, Y = "new multi y" in {
  def MultiFieldDef1 : MultiField;
  def MultiFieldDef2 : MultiField;
}

// demo5 inherit two classes
class Demo5Base1<int src> {
  int val1 = src;
}
class Demo5Base2 {
  int val2 = 5;
}
//def demo5def1 : Demo5Base1<1>, Demo5Base2;
class Demo5Base<int N> : Demo5Base1<N>, Demo5Base2;
def demo5def1 : Demo5Base<1>;
