#!/usr/bin/env bash
set -ue

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
BUILD_DIR="$DIR/tmp"

rm -rf "$BUILD_DIR"
mkdir  "$BUILD_DIR"
cd "$BUILD_DIR"

#cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..
cmake ..
cmake  --build . 

export CTEST_OUTPUT_ON_FAILURE=1 
make test
