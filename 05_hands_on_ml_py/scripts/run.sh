#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

target="${1:-}"
[[ -n "$target" ]] || {
  printf 'usage: mise run run -- chNN/file.py [arguments...]\n' >&2
  exit 2
}
shift

case "$target" in
  /*|../*|*/../*|*/..)
    printf 'file must be inside the book repository: %s\n' "$target" >&2
    exit 2
    ;;
esac
[[ -f "$PROJECT_DIR/code/$target" ]] || {
  printf 'file not found: code/%s\n' "$target" >&2
  exit 2
}

chapter="${target%%/*}"
chapter="$(normalize_chapter "$chapter")"
service="$(service_for_chapter "$chapter")"

ensure_state
require_docker
compose --profile "$service" build "$service"
compose --profile "$service" run --rm --no-deps "$service" \
  python "$target" "$@"
