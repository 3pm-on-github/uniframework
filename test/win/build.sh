#!/bin/bash

gcc test.c ../../win/uniframework.c \
-I/mingw64/include/SDL2 \
-L/mingw64/lib \
-lmingw32 -lSDL2main -lSDL2
cp ../../win/lib/SDL2.dll .