#!/bin/bash

BUILD_DIR=build/

if [ -d "$BUILD_DIR" ]; then
    cd ${BUILD_DIR}
else
    mkdir ${BUILD_DIR}
    cd ${BUILD_DIR}
fi

echo "Using working directory: $(pwd)"

CXX=g++-4.8 cmake ..

make