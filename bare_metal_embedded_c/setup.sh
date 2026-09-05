#!/usr/bin/env bash
set -euo pipefail

source_revision=d96e846918317159f090c7c54ba13b680634e2df
source_url="https://github.com/PacktPublishing/Bare-Metal-Embedded-C-Programming/archive/${source_revision}.tar.gz"

compatibility_fix() {
  while IFS= read -r -d '' makefile; do
    sed -i \
      -e 's/^load[[:space:]]*:/load:/' \
      -e 's/^\([[:space:]]*\)del[[:space:]]*-/\1rm -/' \
      -e 's/[[:space:]]-fcyclomatic-complexity//g' \
      "$makefile"
  done < <(find code -type f \( -name Makefile -o -name makefile -o -name '*.mk' -o -name '*.d' \) -print0)
  while IFS= read -r -d '' makefile; do
    sed -i -E \
      -e 's|[A-Za-z]:[/\\][^"[:space:]]*[/\\]tempWorkspace[/\\]Chapter1[/\\]1_FirstProject[/\\]|../|g' \
      -e 's|[A-Za-z]:[/\\][^"[:space:]]*[/\\]tempWorkspace[/\\]Chapter2[/\\]2_RegisterManipulation-old[/\\]|../|g' \
      -e 's|[A-Za-z]:[/\\][^"[:space:]]*[/\\]tempWorkspace[/\\][^/\\"]+[/\\]|../|g' \
      "$makefile"
    sed -i -E ':a; s|(\.\./[^[:space:]"\\]*)\\|\1/|g; ta' "$makefile"
  done < <(find code -type f \( -name Makefile -o -name makefile -o -name '*.mk' -o -name '*.d' \) -print0)
}

if [[ -f code/Chapter5/4_Makefiles/Makefile ]]; then
  compatibility_fix
  exit 0
fi

command -v curl >/dev/null || {
  echo "curl is required to fetch the pinned author source." >&2
  exit 1
}
command -v tar >/dev/null || {
  echo "tar is required to unpack the pinned author source." >&2
  exit 1
}

mkdir -p code
mkdir -p .tmp/setup
temp_dir="$(mktemp -d .tmp/setup/source.XXXXXX)"
trap 'rm -rf "$temp_dir"' EXIT
curl --fail --location --retry 3 --silent --show-error \
  "$source_url" --output "$temp_dir/source.tar.gz"
tar -xzf "$temp_dir/source.tar.gz" -C "$temp_dir"
source_dir="$(find "$temp_dir" -mindepth 1 -maxdepth 1 -type d -print -quit)"
test -n "$source_dir"
if [[ -f "$source_dir/README.md" ]]; then
  mv "$source_dir/README.md" "$source_dir/README.upstream.md"
fi
cp -a -n "$source_dir/." code/
compatibility_fix
