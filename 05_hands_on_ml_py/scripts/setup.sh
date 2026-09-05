#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

CODE_DIR="$PROJECT_DIR/code"
CODE_REPOSITORY="https://github.com/rasbt/machine-learning-book.git"
CODE_REVISION="63bee951ca45420ac33ccf803ceb337afc3c0a91"

fatal_setup() {
  printf 'error: %s\n' "$*" >&2
  exit 1
}

code_is_checkout() {
  local top
  [[ -d "$CODE_DIR" ]] || return 1
  top="$(git -C "$CODE_DIR" rev-parse --show-toplevel 2>/dev/null || true)"
  [[ "$top" == "$CODE_DIR" ]]
}

ensure_code_checkout() {
  command -v git >/dev/null 2>&1 || fatal_setup 'required command not found: git'
  code_is_checkout && return

  if [[ -e "$CODE_DIR" ]]; then
    [[ -d "$CODE_DIR" ]] || fatal_setup "code exists but is not a directory: $CODE_DIR"
    local first_entry
    first_entry="$(find "$CODE_DIR" -mindepth 1 -maxdepth 1 -print -quit)"
    [[ -z "$first_entry" ]] || fatal_setup "code exists but is not a git checkout: $CODE_DIR"
  fi

  git clone --no-checkout "$CODE_REPOSITORY" "$CODE_DIR"
  git -C "$CODE_DIR" checkout --detach "$CODE_REVISION"
}

ensure_code_checkout
ensure_state

free_gib="$(df -BG --output=avail "$PROJECT_DIR" | tail -1 | tr -dc '0-9')"
if ((free_gib < 150)); then
  printf 'Full setup requires at least 150 GiB free; found %s GiB.\n' "$free_gib" >&2
  exit 1
fi

require_docker
compose --profile core --profile torch --profile gnn --profile rl \
  build core torch gnn rl

for profile in core torch gnn rl; do
  compose --profile "$profile" run --rm --no-deps "$profile" verify "$profile"
done

printf '\nReady. Open code/ in Neovim and start with Chapter 1.\n'
