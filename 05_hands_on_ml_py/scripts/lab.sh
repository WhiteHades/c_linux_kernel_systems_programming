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
  printf 'usage: mise run lab -- chNN [--gpu]\n' >&2
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
token="$(jupyter_token)"
export JUPYTER_TOKEN="$token"
export JUPYTER_PORT="${JUPYTER_PORT:-8888}"
require_docker
compose --profile "$service" build "$service"

printf 'Opening %s with the %s environment.\n' "$chapter" "$service"
printf 'Local URL: http://127.0.0.1:%s/lab/tree/%s?token=%s\n' \
  "$JUPYTER_PORT" "$chapter" "$token"
printf 'Press Ctrl-C to stop the lab.\n'
compose --profile "$service" run --rm --service-ports --no-deps \
  -e JUPYTER_TOKEN -e JUPYTER_PORT "$service" jupyter "$chapter"
