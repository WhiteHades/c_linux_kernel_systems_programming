#!/usr/bin/env bash
set -euo pipefail

start_display() {
  if [[ -z "${DISPLAY:-}" ]]; then
    export DISPLAY=:99
    Xvfb "$DISPLAY" -screen 0 1280x720x24 -nolisten tcp >/tmp/xvfb.log 2>&1 &
  fi
}

case "${1:-}" in
  jupyter)
    chapter="${2:-ch01}"
    [[ "$chapter" =~ ^ch(0[1-9]|1[0-9])$ ]] || {
      printf 'invalid chapter: %s\n' "$chapter" >&2
      exit 2
    }
    [[ -n "${JUPYTER_TOKEN:-}" ]] || {
      printf 'JUPYTER_TOKEN is required\n' >&2
      exit 2
    }
    if [[ "${BOOK_PROFILE:-}" == "rl" ]]; then
      start_display
    fi
    exec jupyter lab \
      --ip=0.0.0.0 \
      --port="${JUPYTER_PORT:-8888}" \
      --no-browser \
      --ServerApp.root_dir=/workspace/code \
      --ServerApp.default_url="/lab/tree/${chapter}" \
      --ServerApp.token="$JUPYTER_TOKEN" \
      --ServerApp.password=''
    ;;
  shell)
    if [[ "${BOOK_PROFILE:-}" == "rl" ]]; then
      start_display
    fi
    shift
    exec "${@:-bash}"
    ;;
  verify)
    shift
    exec /opt/book/bin/verify-env.sh "$@"
    ;;
  *)
    exec "$@"
    ;;
esac
