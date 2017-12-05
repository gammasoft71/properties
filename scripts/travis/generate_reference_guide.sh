#!/bin/bash

set -ev

# setup git
git config --global user.email "gammasoft71@gmail.com"
git config --global user.name "gammasoft71"

# Clone properties-doc
if [ -d "build/reference_guide" ]; then rm -r -f build/reference_guide; fi
git clone https://github.com/gammasoft71/properties-doc.git build/reference_guide

# generate documentation
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF -DENABLE_COVERAGE=OFF -DCMAKE_CXX_COMPILER="g++-6"
cmake --build . --target properties.reference_guide -- -j8
cd ..

# check doxygen results and display error
if [[ -s build/reference_guide/doxygen_warnings.txt ]]; then
  echo "You must fix doxygen before submitting a pull request"
  echo ""
  cat build/reference_guide/doxygen_warnings.txt
  exit -1
fi

# Publishing documentation
cd build/reference_guide
if [[ -e doxygen_warnings.txt ]]; then rm doxygen_warnings.txt; fi
git add --all
git commit -m "Generate Reference Guide [$TRAVIS_BUILD_NUMBER]"
git push "https://${GH_TOKEN}@github.com/gammasoft71/properties-doc.git" master > /dev/null 2>&1
cd ../..
