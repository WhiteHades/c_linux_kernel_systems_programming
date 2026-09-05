#!/usr/bin/env bash
set -euo pipefail

root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)
code="$root/code"
revision=4a840f70f69c6ddd17cfef4f6964f8e1bcd8c3d4
repository=https://github.com/munificent/craftinginterpreters.git

if [[ ! -f "$code/Makefile" || ! -f "$code/tool/pubspec.yaml" ]]; then
  [[ ! -e "$code" ]] || { printf 'code exists but is incomplete: %s\n' "$code" >&2; exit 1; }
  git clone --filter=blob:none --no-checkout "$repository" "$code"
  git -C "$code" checkout --detach "$revision"
fi

exec bash "$root/../scripts/book-container.sh" setup local/crafting-interpreters:16
