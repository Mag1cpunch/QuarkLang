#!/bin/bash

clang++ -g -std=c++17 -I ./src/include -o ./bin/compiler ./src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core`