rem run registered unit tests 32 bits
if DEFINED BUILD_WIN32 (
  cd build32
  ctest --output-on-failure --build-config Release
  cd ..
)

rem run registered unit tests 64 bits
if DEFINED BUILD_WIN64 (
  cd build64
  ctest --output-on-failure --build-config Release
  cd ..
)
