#!/bin/bash

set -ev

# cppcheck analyse
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON -DENABLE_COVERAGE=OFF -DCMAKE_CXX_COMPILER="g++-6"
cmake --build . --target properties.check -- -j8
cd ..
