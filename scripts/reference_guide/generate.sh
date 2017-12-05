#!/usr/bin/env sh

# Clone switch-doc
if [ -d "build/ReferenceGuide" ]; then rm -r -f build/reference_guide; fi
git clone https://github.com/gammasoft71/properties-doc build/ReferenceGuide

# Generating documentation
cd build
cmake --build . --target properties.reference_guide
cd ..

# Publishing documentation
cd build/reference_guide
git add --all
git commit -m "Generate Reference Guide"
git push
