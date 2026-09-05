#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

mode="${1:-all}"
ensure_state
require_docker

case "$mode" in
  quick)
    profiles=(core)
    ;;
  all)
    profiles=(core torch gnn rl)
    ;;
  core|torch|gnn|rl)
    profiles=("$mode")
    ;;
  *)
    printf 'usage: mise run verify -- [quick|all|core|torch|gnn|rl]\n' >&2
    exit 2
    ;;
esac

for profile in "${profiles[@]}"; do
  compose --profile "$profile" build "$profile"
  compose --profile "$profile" run --rm --no-deps "$profile" verify "$profile"
done
