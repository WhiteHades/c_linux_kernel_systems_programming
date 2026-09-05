#!/usr/bin/env bash
set -euo pipefail

code=/workspace/code
build_dir=/workspace/.state/build
make_dir=/workspace/.state/modern-c
export CCACHE_DIR=/workspace/.state/ccache

usage() {
  cat <<'EOF'
usage: study.sh build [make-target|SOURCE.c]
       study.sh run [executable|SOURCE.c] [PROGRAM-ARG...]
       study.sh verify
       study.sh shell
EOF
}

source_path() {
  local path=$1
  if [[ -f "/workspace/$path" ]]; then
    printf '/workspace/%s\n' "$path"
  elif [[ -f "$code/$path" ]]; then
    printf '%s/%s\n' "$code" "$path"
  elif [[ -f "/workspace/exercises/$path" ]]; then
    printf '/workspace/exercises/%s\n' "$path"
  else
    printf 'source not found: %s\n' "$path" >&2
    exit 2
  fi
}

relative_path() {
  local path=$1
  if [[ "$path" == "$code/"* ]]; then
    printf '%s\n' "${path#"$code"/}"
  elif [[ "$path" == /workspace/exercises/* ]]; then
    printf 'exercises/%s\n' "${path#/workspace/exercises/}"
  else
    printf '%s\n' "${path#/workspace/}"
  fi
}

compile_source() {
  local path=$1
  local source
  source=$(source_path "$path")
  [[ "$source" == *.c ]] || {
    printf 'source must end in .c: %s\n' "$path" >&2
    exit 2
  }
  local relative stem object output
  relative=$(relative_path "$source")
  stem=${relative%.c}
  object="$build_dir/$stem.o"
  output="$build_dir/$stem"
  mkdir -p "$(dirname "$object")"
  ccache cc -std=c23 -Wall -Wextra -g -c "$source" -o "$object"
  cc "$object" -o "$output" -lm
  printf '%s\n' "$output"
}

make_code() {
  local -a inputs=("$code"/*.c "$code"/*.h "$code"/Makefile)
  mkdir -p "$make_dir"
  cp -p -- "${inputs[@]}" "$make_dir/"
  make -C "$make_dir" CC='ccache cc' CCC='ccache cc' "$@"
}

run_program() {
  local target=$1
  shift
  local executable
  if [[ "$target" == *.c ]]; then
    executable=$(compile_source "$target")
  elif [[ -x "/workspace/$target" ]]; then
    executable="/workspace/$target"
  elif [[ -x "$make_dir/$target" ]]; then
    executable="$make_dir/$target"
  elif [[ -x "$code/$target" ]]; then
    executable="$code/$target"
  elif [[ -x "/workspace/exercises/$target" ]]; then
    executable="/workspace/exercises/$target"
  else
    printf 'executable not found: %s\n' "$target" >&2
    exit 2
  fi
  exec "$executable" "$@"
}

case "${1:-}" in
  build)
    target=${2:-getting-started}
    if [[ "$target" == *.c ]]; then
      compile_source "$target" >/dev/null
    else
      [[ "$target" == all ]] && target=binaries
      make_code "$target"
    fi
    ;;
  run)
    shift
    [[ $# -gt 0 ]] || { usage >&2; exit 2; }
    run_program "$@"
    ;;
  verify)
    output=$(compile_source code/getting-started.c)
    result=$("$output")
    [[ "$result" == *'element 0 is 9'* ]]
    [[ "$result" == *'element 4 is 3e+25'* ]]
    printf 'C23 starter example passed.\n'
    ;;
  shell)
    exec bash
    ;;
  *)
    usage >&2
    exit 2
    ;;
esac
