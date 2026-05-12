#!/bin/bash
mkdir -p bin

if ! command -v gcc &>/dev/null; then
  read -p "gcc not found. Install MinGW64 toolchain and SDL2 via pacman? [y/N] " choice
  if [[ "$choice" =~ ^[Yy]$ ]]; then
    pacman -S --needed mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf
    exec "$0"
  else
    echo "Aborted."
    exit 1
  fi
fi

gcc test.c ../../src/uniframework.c \
  -I/mingw64/include/SDL2 \
  -L/mingw64/lib \
  -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf \
  -o bin/test.exe

if [ $? -ne 0 ]; then
  read -p "Build failed. Install SDL2 dependencies via pacman? [y/N] " choice
  if [[ "$choice" =~ ^[Yy]$ ]]; then
    pacman -S --needed mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf
    exec "$0"
  else
    echo "Aborted."
    exit 1
  fi
fi

ldd bin/test.exe | grep -i mingw | awk '{print $3}' | xargs -I{} cp {} bin/
cp -r assets bin/