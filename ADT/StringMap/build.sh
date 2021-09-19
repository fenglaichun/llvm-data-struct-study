#!/bin/bash
g++ `llvm-config --cxxflags` string_map.cpp -c -o string_map.o
g++ `llvm-config --ldflags` -o main string_map.o `llvm-config --libs support` -lpthread -ltinfo
./main -track-memory
