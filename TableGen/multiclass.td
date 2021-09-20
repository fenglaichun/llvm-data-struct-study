class Base0 {
  string str0 = "str0";
}

class Base1 {
  string str1 = "str1";
}

class Base2 {
  string str2 = "str2";
}
multiclass MultiDemo0 {
  def One : Base0;
  def Two : Base1;
  def Three : Base2;
}

multiclass MultiDemo1 {
  def : Base0;
  def : Base1;
  def : Base2;
}

// the name of the result record is MultiDef0One, MultiDef0Two, MultiDefThree
defm MultiDef0 : MultiDemo0;
// the name of the result record is annoymous.
defm MultiDef1 : MultiDemo1;
// the name of the result record is annoymous and tablegen make sure they are unique.
defm : MultiDemo1;


// check the rule for dag type.
// Inst
def ops;
def GPR;
def Imm;
class inst <int opc, string asmstr, dag operandlist>;

multiclass ri_inst <int opc, string asmstr> {
  def _rr : inst<opc, !strconcat(asmstr, " $dst, $src1, $src2"),
                   (ops GPR:$dst, GPR:$src1, GPR:$src2)>;
  def _ri : inst<opc, !strconcat(asmstr, " $dst, $src1, $src2"),
                   (ops GPR:$dst, GPR:$src1, Imm:$src2)>;
}

// Define records for each instruction in the RR and RI formats.
defm ADD : ri_inst<0b111, "add">;
defm SUB : ri_inst<0b101, "sub">;
defm MUL : ri_inst<0b100, "mul">;

// multiclass inherit
class Instruction <bits<4> opc, string Name> {
  bits<4> opcode = opc;
  string name = Name;
}

multiclass basic_r <bits<4> opc> {
  def rr : Instruction<opc, "rr">;
  def rm : Instruction<opc, "rm">;
}

multiclass basic_s <bits<4> opc> {
  defm SS : basic_r<opc>;
  defm SD : basic_r<opc>;
  def X : Instruction<opc, "x">;
}

multiclass basic_p <bits<4> opc> {
  defm PS : basic_r<opc>;
  defm PD : basic_r<opc>;
  def Y : Instruction<opc, "y">;
}

defm ADD : basic_s<0xf>, basic_p<0xf>;

// mixed multiclass and regular class
// The rule is that the regular classes must be listed after the multiclass, and 
// there must be at least one multiclass.
class XD {
  bits<4> Prefix = 11;
}
class XS {
  bits<4> Prefix = 12;
}
class I <bits<4> op> {
  bits<4> opcode = op;
}

multiclass R {
  def rr : I<4>;
  def rm : I<2>;
}

multiclass Y {
  defm SS : R, XD;    // First multiclass R, then regular class XD.
  defm SD : R, XS;
}

defm Instr : Y;
