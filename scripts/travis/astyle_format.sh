#!/bin/bash

set -ev

# format code with AStyle
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON -DENABLE_COVERAGE=OFF -DCMAKE_CXX_COMPILER="g++-6"
cmake --build . --target properties.format -- -j8
cd ..

# check file changed and display error
if [[ -n $(git diff) ]]; then
  echo "You must run make format before submitting a pull request"
  echo ""
  git diff
  exit -1
fi
