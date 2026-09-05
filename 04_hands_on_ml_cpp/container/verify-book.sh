#!/usr/bin/env bash
set -Eeuo pipefail

mode="${1:-quick}"
case "$mode" in
  env|quick|all) ;;
  *)
    printf 'usage: verify-book [env|quick|all]\n' >&2
    exit 2
    ;;
esac

/usr/local/bin/verify-env
[[ "$mode" == env ]] && exit 0

source_root=/workspace/code
[[ -d "$source_root/build_scripts" ]] || {
  printf 'Packt checkout is missing at %s\n' "$source_root" >&2
  exit 1
}

verification_root="$(mktemp -d /workspace/state/verify-code.XXXXXX)"
case "$verification_root" in
  /workspace/state/verify-code.*) ;;
  *)
    printf 'Refusing unexpected verification path: %s\n' "$verification_root" >&2
    exit 1
    ;;
esac
cleanup() {
  rm -rf -- "$verification_root"
}
trap cleanup EXIT

tar --exclude='.git' --exclude='*/build' -C "$source_root" -cf - . \
  | tar -C "$verification_root" -xf -
cd "$verification_root/build_scripts"

run_chapter() {
  local chapter="$1"
  local source_script="./build_ch${chapter}.sh"
  local temporary_script
  local status

  [[ -f "$source_script" ]] || {
    printf 'Missing upstream build script: %s\n' "$source_script" >&2
    return 1
  }

  temporary_script="$(mktemp)"
  sed -E \
    -e 's/^[[:space:]]*mkdir[[:space:]]+build[[:space:]]*$/mkdir -p build/' \
    -e 's#^[[:space:]]*LIBS_DIR=.*$#LIBS_DIR="${BOOK_PREFIX:-/opt/book/libs}"#' \
    "$source_script" >"$temporary_script"

  printf '\nBuilding Chapter %s\n' "$chapter"
  if bash -e "$temporary_script"; then
    status=0
  else
    status=$?
  fi
  rm -f -- "$temporary_script"
  return "$status"
}

if [[ "$mode" == quick ]]; then
  run_chapter 1
  "$verification_root/Chapter01/eigen_samples/build/linalg_eigen" >/dev/null
  printf '\nChapter 1 Eigen runtime smoke test passed.\n'
  exit 0
fi

failed=()
for chapter in {1..13}; do
  if ! run_chapter "$chapter"; then
    failed+=("$chapter")
  fi
done

if ((${#failed[@]})); then
  printf '\nChapter build failures: %s\n' "${failed[*]}" >&2
  exit 1
fi
