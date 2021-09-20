#!/bin/bash
g++ `llvm-config --cxxflags` TableGen.cpp -c -o TableGen.o
g++ `llvm-config --ldflags` -o main TableGen.o `llvm-config --libs support tablegen` -lpthread -ltinfo
