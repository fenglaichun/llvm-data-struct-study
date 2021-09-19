#!/bin/bash
g++ `llvm-config --cxxflags` dense_map.cpp -c -o dense_map.o
g++ `llvm-config --ldflags` -o main dense_map.o `llvm-config --libs support` -lpthread -ltinfo
./main -track-memory
