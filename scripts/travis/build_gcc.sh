#!/bin/bash

set -ev

# generate and build properties
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON -DCMAKE_CXX_COMPILER="g++-6"
cmake --build . -- -j8
cd ..

# run registered unit tests
cd build
ctest --output-on-failure --build-config Release
cd ..
