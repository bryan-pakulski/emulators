#!/bin/bash
if [ ! -d "build" ]; then
    echo "build directory not present, please build the project with cmake first"
    exit 1
fi

mkdir -p build/CoreLink
mkdir -p build/CoreLink/cores

if [ -f build/src/CoreLink/CoreLink ]; then
  mv build/src/CoreLink/CoreLink build/CoreLink/
fi

cp -ruv data build/CoreLink/

find build/src/Cores -type f -name "*.so" -exec sh -c 'cp "$0" "build/CoreLink/cores/$(basename "$0" .so).ecore"' {} \;

tar -czf CoreLink.tar.gz -C build/CoreLink .