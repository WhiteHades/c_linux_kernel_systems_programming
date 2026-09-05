#!/usr/bin/env bash
set -euo pipefail

state=/workspace/.state
build_dir="$state/build"
export CCACHE_DIR="$state/ccache"

usage() {
  cat <<'EOF'
usage: study.sh build SOURCE [SOURCE...]
       study.sh run SOURCE [SOURCE...] [-- PROGRAM-ARG...]
       study.sh verify
       study.sh shell
EOF
}

source_path() {
  local path=$1
  if [[ -f "/workspace/$path" ]]; then
    printf '/workspace/%s\n' "$path"
  elif [[ -f "/workspace/code/$path" ]]; then
    printf '/workspace/code/%s\n' "$path"
  elif [[ -f "/workspace/exercises/$path" ]]; then
    printf '/workspace/exercises/%s\n' "$path"
  else
    printf 'source not found: %s\n' "$path" >&2
    exit 2
  fi
}

relative_path() {
  local path=$1
  if [[ "$path" == /workspace/code/* ]]; then
    printf 'code/%s\n' "${path#/workspace/code/}"
  elif [[ "$path" == /workspace/exercises/* ]]; then
    printf 'exercises/%s\n' "${path#/workspace/exercises/}"
  else
    printf '%s\n' "${path#/workspace/}"
  fi
}

build_source() {
  local first=$1
  shift
  local first_path
  first_path=$(source_path "$first")
  [[ "$first_path" == *.cpp ]] || {
    printf 'source must end in .cpp: %s\n' "$first" >&2
    exit 2
  }

  local first_relative target
  first_relative=$(relative_path "$first_path")
  target=${first_relative%.cpp}
  local output="$build_dir/$target"
  local object_dir="$build_dir/objects"
  local source_paths=("$first_path")
  local extra
  for extra in "$@"; do
    source_paths+=("$(source_path "$extra")")
  done

  local objects=()
  local source relative object
  for source in "${source_paths[@]}"; do
    relative=$(relative_path "$source")
    object="$object_dir/${relative%.cpp}.o"
    mkdir -p "$(dirname "$object")"
    ccache g++ -std=c++23 -Wall -Wextra -Wpedantic -g -c "$source" -o "$object"
    objects+=("$object")
  done
  mkdir -p "$(dirname "$output")"
  g++ "${objects[@]}" -o "$output"
  printf '%s\n' "$output"
}

run_source() {
  local source=$1
  shift
  local sources=("$source")
  while [[ $# -gt 0 && "$1" != -- ]]; do
    sources+=("$1")
    shift
  done
  [[ ${1:-} != -- ]] || shift

  local executable
  if [[ "$source" == *.cpp ]]; then
    executable=$(build_source "${sources[@]}")
  elif ((${#sources[@]} > 1)); then
    printf 'multiple sources must end in .cpp: %s\n' "$source" >&2
    exit 2
  elif [[ -x "/workspace/$source" ]]; then
    executable="/workspace/$source"
  elif [[ -x "/workspace/code/$source" ]]; then
    executable="/workspace/code/$source"
  elif [[ -x "/workspace/exercises/$source" ]]; then
    executable="/workspace/exercises/$source"
  else
    printf 'executable not found: %s\n' "$source" >&2
    exit 2
  fi
  exec "$executable" "$@"
}

case "${1:-}" in
  build)
    shift
    [[ $# -gt 0 ]] || { usage >&2; exit 2; }
    build_source "$@" >/dev/null
    ;;
  run)
    shift
    [[ $# -gt 0 ]] || { usage >&2; exit 2; }
    run_source "$@"
    ;;
  verify)
    mkdir -p "$build_dir"
    hello=$(build_source code/chapter_01/hello.cpp)
    println=$(build_source code/chapter_01/hello_println.cpp)
    [[ "$("$hello")" == 'Hello, world!' ]]
    [[ "$("$println")" == 'Hello, world!' ]]
    printf 'C++23 examples passed.\n'
    ;;
  shell)
    exec bash
    ;;
  *)
    usage >&2
    exit 2
    ;;
esac
