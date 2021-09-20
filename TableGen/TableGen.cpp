//===- TableGen.cpp - Top-Level TableGen implementation for LLVM ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the main function for LLVM's TableGen.
//
//===----------------------------------------------------------------------===//

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/TableGen/Main.h"
#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/SetTheory.h"

using namespace llvm;

enum ActionType {
  PrintRecords,
};

namespace llvm {
/// Storage for TimeRegionsOpt as a global so that backends aren't required to
/// include CommandLine.h
bool TimeRegions = false;
cl::opt<bool> EmitLongStrLiterals(
    "long-string-literals",
    cl::desc("when emitting large string tables, prefer string literals over "
             "comma-separated char literals. This can be a readability and "
             "compile-time performance win, but upsets some compilers"),
    cl::Hidden, cl::init(true));
} // end namespace llvm

namespace {
cl::opt<ActionType> Action(
    cl::desc("Action to perform:"),
    cl::values(
        clEnumValN(PrintRecords, "print-records",
                   "Print all records to stdout (default)")
               ));

cl::OptionCategory PrintEnumsCat("Options for -print-enums");
cl::opt<std::string> Class("class", cl::desc("Print Enum list for this class"),
                           cl::value_desc("class name"),
                           cl::cat(PrintEnumsCat));

cl::opt<bool, true>
    TimeRegionsOpt("time-regions",
                   cl::desc("Time regions of tablegens execution"),
                   cl::location(TimeRegions));

bool DemoTableGenMain(raw_ostream &OS, RecordKeeper &Records) {
  switch (Action) {
  case PrintRecords:
    OS << Records;           // No argument, dump all contents
    break;
  }

  return false;
}
}

int main(int argc, char **argv) {
  InitLLVM X(argc, argv);
  cl::ParseCommandLineOptions(argc, argv);

  return TableGenMain(argv[0], &DemoTableGenMain);
}

#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__) ||       \
    __has_feature(leak_sanitizer)

#include <sanitizer/lsan_interface.h>
// Disable LeakSanitizer for this binary as it has too many leaks that are not
// very interesting to fix. See compiler-rt/include/sanitizer/lsan_interface.h .
LLVM_ATTRIBUTE_USED int __lsan_is_turned_off() { return 1; }

#endif
