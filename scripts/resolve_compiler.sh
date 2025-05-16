#!/usr/bin/env bash

# Resolve the appropriate compiler based on the target platform.

set -e

TARGET="$1"

if [[ -z "$TARGET" ]]; then
  echo "Usage: $0 <target>" >&2
  exit 1
fi

case "$TARGET" in
  linux-x86_64)
    echo "g++"
    ;;
  linux-aarch64)
    echo "aarch64-linux-gnu-g++"
    ;;
  windows-x86_64)
    echo "x86_64-w64-mingw32-g++"
    ;;
  *)
    echo "❌ Unknown target: $TARGET" >&2
    exit 1
    ;;
esac
