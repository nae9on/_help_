#!/bin/bash

rm -rf build

mkdir -p build

cd build

cmake3 ..

make

./tutorial

cd ..

rm -rf build
