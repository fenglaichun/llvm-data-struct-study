#!/bin/bash
g++ `llvm-config --cxxflags` twine.cpp -c -o twine.o
g++ `llvm-config --ldflags` -o main twine.o `llvm-config --libs support` -lpthread
./main -track-memory
