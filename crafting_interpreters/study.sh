#!/usr/bin/env bash
set -euo pipefail

code=/workspace/code
state=/workspace/.state
export CCACHE_DIR="$state/ccache"

usage() {
  cat <<'EOF'
usage: study.sh build [all|jlox|clox]
       study.sh run [jlox|clox] [PROGRAM-ARG...]
       study.sh test [test|test_all|test_jlox|test_clox|test_java|test_c]
       study.sh chapters
       study.sh verify
       study.sh shell
EOF
}

ensure_packages() {
  mkdir -p "$code/tool/.dart_tool"
  cp /opt/crafting-tool/tool/.dart_tool/package_config.json \
    "$code/tool/.dart_tool/package_config.json"
}

make_code() {
  ensure_packages
  make -C "$code" CC='ccache cc' "$@"
}

build_all() {
  case "${1:-all}" in
    all) build_learner_clox >/dev/null; build_learner_jlox >/dev/null ;;
    clox) build_learner_clox >/dev/null ;;
    jlox) build_learner_jlox >/dev/null ;;
    *) printf 'unknown build target: %s\n' "$1" >&2; exit 2 ;;
  esac
}

build_learner_jlox() {
  local source_dir=/workspace/exercises/jlox
  [[ -d "$source_dir" ]] || {
    printf 'create %s and write the jlox files from the book there\n' "$source_dir" >&2
    exit 2
  }

  local sources=()
  mapfile -t sources < <(find "$source_dir" -type f -name '*.java' -print | sort)
  ((${#sources[@]} > 0)) || {
    printf 'no jlox java files found in %s\n' "$source_dir" >&2
    exit 2
  }

  local output="$state/build/jlox"
  mkdir -p "$output"
  javac -Werror -d "$output" "${sources[@]}"
  printf '%s\n' "$output"
}

build_learner_clox() {
  local source_dir=/workspace/exercises/clox
  [[ -d "$source_dir" ]] || {
    printf 'create %s and write the clox files from the book there\n' "$source_dir" >&2
    exit 2
  }

  local sources=()
  mapfile -t sources < <(find "$source_dir" -type f -name '*.c' -print | sort)
  ((${#sources[@]} > 0)) || {
    printf 'no clox c files found in %s\n' "$source_dir" >&2
    exit 2
  }

  local output="$state/build/clox"
  local object_dir="$state/build/clox-objects"
  local objects=()
  local source relative object
  for source in "${sources[@]}"; do
    relative=${source#"$source_dir"/}
    object="$object_dir/${relative%.c}.o"
    mkdir -p "$(dirname "$object")"
    ccache cc -std=c99 -Wall -Wextra -Wno-unused-parameter -O0 -g \
      -I"$source_dir" -c "$source" -o "$object"
    objects+=("$object")
  done
  mkdir -p "$(dirname "$output")"
  cc "${objects[@]}" -o "$output" -lm
  printf '%s\n' "$output"
}

run_learner() {
  local target=${1:?choose jlox or clox}
  shift
  case "$target" in
    jlox)
      local jlox_build
      jlox_build=$(build_learner_jlox)
      exec java -cp "$jlox_build" com.craftinginterpreters.lox.Lox "$@"
      ;;
    clox)
      local clox_build
      clox_build=$(build_learner_clox)
      exec "$clox_build" "$@"
      ;;
    *) printf 'unknown interpreter: %s\n' "$target" >&2; exit 2 ;;
  esac
}

case "${1:-}" in
  build)
    shift
    build_all "${1:-all}"
    ;;
  run)
    shift
    [[ $# -gt 0 ]] || { usage >&2; exit 2; }
    run_learner "$@"
    ;;
  test)
    shift
    target=${1:-test}
    case "$target" in
      test|test_all|test_jlox|test_clox|test_java|test_c) make_code "$target" ;;
      *) printf 'unknown test target: %s\n' "$target" >&2; exit 2 ;;
    esac
    ;;
  chapters)
    make_code c_chapters java_chapters
    ;;
  verify)
    make_code test_clox test_jlox clox
    mkdir -p "$state"
    printf 'print 1 + 2;\n' > "$state/smoke.lox"
    jlox_output=$("$code/jlox" "$state/smoke.lox")
    clox_output=$("$code/clox" "$state/smoke.lox")
    [[ "$jlox_output" == '3' ]]
    [[ "$clox_output" == '3' ]]
    printf 'jlox and clox passed.\n'
    ;;
  shell)
    exec bash
    ;;
  *)
    usage >&2
    exit 2
    ;;
esac
