#!/bin/bash

mkdir -p bin
gcc test.c ../../win/uniframework.c \
-I/mingw64/include/SDL2 \
-L/mingw64/lib \
-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf \
-o bin/test.exe
ldd bin/test.exe | grep -i mingw | awk '{print $3}' | xargs -I{} cp {} bin/
cp -r assets bin/