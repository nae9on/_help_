#!/bin/bash

rm -rf build

mkdir -p build

cd build

cmake3 ..

make

./src/tutorial

cd ..

rm -rf build