#!/usr/bin/env bash
set -euo pipefail

command_name="${1:-shell}"
shift || true

project_make_dir() {
  local target="$1"
  if [[ -f "$target/Makefile" || -f "$target/makefile" ]]; then
    printf '%s\n' "$target"
    return
  fi
  [[ -d "$target" ]] || return 0
  find "$target" -mindepth 1 -maxdepth 3 -type f \
    \( -name Makefile -o -name makefile \) -printf '%h\n' \
    | sort -u | head -n1
}

case "$command_name" in
  verify)
    command -v arm-none-eabi-gcc >/dev/null
    command -v arm-none-eabi-objcopy >/dev/null
    command -v arm-none-eabi-size >/dev/null
    command -v openocd >/dev/null
    test -f /workspace/code/Chapter5/4_Makefiles/Makefile
    make -C /workspace/code/Chapter5/4_Makefiles clean >/dev/null 2>&1 || true
    make -C /workspace/code/Chapter5/4_Makefiles -j"${JOBS:-$(nproc)}"
    arm-none-eabi-size /workspace/code/Chapter5/4_Makefiles/4_makefile_project.elf
    echo "embedded C toolchain ready"
    ;;
  build)
    target="${1:-/workspace/exercises}"
    shift || true
    make_dir="$(project_make_dir "$target")"
    [[ -n "$make_dir" ]] || {
      echo "Copy one author project into exercises/, then pass its path to build." >&2
      exit 2
    }
    make -C "$make_dir" "$@"
    ;;
  run)
    target="${1:-/workspace/exercises}"
    shift || true
    elf="$(find "$target" -type f -name '*.elf' -print -quit 2>/dev/null || true)"
    if [[ -z "$elf" ]]; then
      make_dir="$(project_make_dir "$target")"
      [[ -n "$make_dir" ]] || {
        echo "Copy one author project into exercises/, then pass its path to run." >&2
        exit 2
      }
      make -C "$make_dir"
      elf="$(find "$target" -type f -name '*.elf' -print -quit 2>/dev/null || true)"
    fi
    test -n "$elf"
    arm-none-eabi-size "$elf"
    echo "firmware built: $elf"
    echo "Connect the NUCLEO-F411RE and use the author's OpenOCD procedure to flash it."
    ;;
  shell)
    exec bash "$@"
    ;;
  *)
    echo "usage: study.sh verify|build [dir] [make args...]|run [dir]|shell" >&2
    exit 2
    ;;
esac
