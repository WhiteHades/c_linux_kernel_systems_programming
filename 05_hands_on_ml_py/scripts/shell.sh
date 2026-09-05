#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

chapter_arg="${1:-ch01}"
shift || true
chapter="$(normalize_chapter "$chapter_arg")"
gpu=false
if [[ "${1:-}" == "--gpu" ]]; then
  gpu=true
  shift
fi
if (($#)); then
  printf 'usage: mise run shell -- chNN [--gpu]\n' >&2
  exit 2
fi

service="$(service_for_chapter "$chapter")"
number=$((10#${chapter#ch}))
if [[ "$gpu" == true ]]; then
  if ((number < 12 || number > 17)); then
    printf 'GPU mode applies only to chapters 12 through 17.\n' >&2
    exit 2
  fi
  service=gpu
fi

ensure_state
require_docker
compose --profile "$service" build "$service"
compose --profile "$service" run --rm --no-deps \
  --workdir "/workspace/code/$chapter" "$service" shell bash
