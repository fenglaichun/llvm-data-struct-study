#!/bin/bash
g++ `llvm-config --cxxflags` string_ref.cpp -c -o string_ref.o
g++ `llvm-config --ldflags` -o main string_ref.o `llvm-config --libs support` -lpthread
./main -track-memory
