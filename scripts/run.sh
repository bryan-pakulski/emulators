#!/bin/bash

if [ ! -d "build/CoreLink" ]; then
    echo "build/CoreLink directory not present, please build the project first"
    exit 1
fi

cd build/CoreLink
./CoreLink