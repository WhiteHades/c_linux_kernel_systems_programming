#!/usr/bin/env bash
set -Eeuo pipefail

command_name="${1:-shell}"
shift || true

case "$command_name" in
  shell)
    exec /bin/bash "$@"
    ;;
  verify-env)
    exec /usr/local/bin/verify-env "$@"
    ;;
  verify-gpu)
    exec /usr/local/bin/verify-gpu "$@"
    ;;
  verify-android)
    exec /usr/local/bin/verify-android "$@"
    ;;
  *)
    exec "$command_name" "$@"
    ;;
esac
