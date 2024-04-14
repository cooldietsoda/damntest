#!/bin/sh
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --target install
rm -r ./*
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target install
ls -la ../install/lib