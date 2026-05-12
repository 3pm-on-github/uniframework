#!/bin/bash
set -e

APP_NAME="test" # Please modify this to match the actual internal name
DISPLAY_NAME="Test Game" #Please modify this to match the actual name to show to viewers
APPDIR="build/AppDir"
BIN_DIR="$APPDIR/usr/bin"
SHARE_DIR="$APPDIR/usr/share/$APP_NAME"

mkdir -p "$BIN_DIR"
mkdir -p "$SHARE_DIR"

if ! command -v gcc &>/dev/null; then
  echo "gcc not found."
  echo "Install: gcc pkg-config libsdl2-dev libsdl2-ttf-dev"
  exit 1
fi

if ! command -v pkg-config &>/dev/null; then
  echo "pkg-config not found."
  echo "Install: pkg-config"
  exit 1
fi

if ! pkg-config --exists sdl2 SDL2_ttf; then
  echo "SDL2 or SDL2_ttf development files not found."
  echo "Install: libsdl2-dev libsdl2-ttf-dev"
  exit 1
fi

echo "Building Linux binary..."

gcc test.c ../../linux/uniframework.c \
  $(pkg-config --cflags sdl2 SDL2_ttf) \
  $(pkg-config --libs sdl2 SDL2_ttf) \
  -o "$BIN_DIR/$APP_NAME"

echo "Copying assets..."

cp -r assets "$SHARE_DIR/"
cp defaultfont.otf "$SHARE_DIR/"

cat > "$APPDIR/AppRun" <<EOF
#!/bin/bash
HERE="\$(dirname "\$(readlink -f "\$0")")"

export APPDIR="\$HERE"
export ASSET_DIR="\$HERE/usr/share/$APP_NAME/assets"

exec "\$HERE/usr/bin/$APP_NAME" "\$@"
EOF

chmod +x "$APPDIR/AppRun"

cat > "$APPDIR/$APP_NAME.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=$DISPLAY_NAME
Exec=$APP_NAME
Icon=$APP_NAME
EOF

# Optional placeholder icon, only if you already have one
if [ -f "assets/$APP_NAME.png" ]; then
  cp "assets/$APP_NAME.png" "$APPDIR/$APP_NAME.png"
fi

echo "AppDir created at: $APPDIR"

if command -v appimagetool &>/dev/null; then
  echo "Building AppImage..."
  appimagetool "$APPDIR"
else
  echo "appimagetool not found."
  echo "Install/download appimagetool, then run:"
  echo "  appimagetool $APPDIR"
fi