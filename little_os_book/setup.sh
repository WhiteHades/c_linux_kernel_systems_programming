#!/usr/bin/env bash
set -euo pipefail

stage2_url=https://raw.githubusercontent.com/littleosbook/littleosbook/e90faeb24c5c9fed8cde9a35974893706e81cbbf/files/stage2_eltorito
stage2_sha256=6ef07c7fc2552b63d3ceffa38a713e9ba9c88a54267fce2c93448966eaeeaff1
stage2_path=code/author/files/stage2_eltorito

if [[ -f "$stage2_path" ]]; then
  exit 0
fi

command -v curl >/dev/null || {
  echo "curl is required to fetch the pinned grub artifact." >&2
  exit 1
}

mkdir -p "${stage2_path%/*}"
mkdir -p .tmp/setup
temp_dir="$(mktemp -d .tmp/setup/stage2.XXXXXX)"
trap 'rm -rf "$temp_dir"' EXIT
curl --fail --location --retry 3 --silent --show-error \
  "$stage2_url" --output "$temp_dir/stage2_eltorito"
echo "$stage2_sha256  $temp_dir/stage2_eltorito" | sha256sum --check --strict
install -m 0444 "$temp_dir/stage2_eltorito" "$stage2_path"
