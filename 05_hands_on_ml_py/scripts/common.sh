#!/usr/bin/env bash
set -euo pipefail

PROJECT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
PROJECT_NAME=05_hands_on_ml_py
export LOCAL_UID="$(id -u)"
export LOCAL_GID="$(id -g)"

DOCKER_PREFIX=()
COMPOSE_ARGS=(
  compose
  --project-directory "$PROJECT_DIR"
  --file "$PROJECT_DIR/compose.yaml"
  --project-name "$PROJECT_NAME"
)

compose_direct() {
  docker "${COMPOSE_ARGS[@]}" "$@"
}

compose() {
  "${DOCKER_PREFIX[@]}" docker "${COMPOSE_ARGS[@]}" "$@"
}

require_docker() {
  if docker info >/dev/null 2>&1; then
    DOCKER_PREFIX=()
    return
  fi
  if command -v sudo >/dev/null 2>&1; then
    printf 'Docker is protected by Omarchy. Authenticate for this task.\n' >&2
    sudo -v
    DOCKER_PREFIX=(sudo)
    "${DOCKER_PREFIX[@]}" docker info >/dev/null
    return
  fi
  printf 'Docker is unavailable to this user.\n' >&2
  exit 1
}

ensure_state() {
  umask 077
  mkdir -p \
    "$PROJECT_DIR/.state/runtime/home" \
    "$PROJECT_DIR/.state/runtime/jupyter" \
    "$PROJECT_DIR/.state/runtime/jupyter-data" \
    "$PROJECT_DIR/.state/runtime/jupyter-runtime" \
    "$PROJECT_DIR/.state/runtime/matplotlib" \
    "$PROJECT_DIR/.state/runtime/pip-cache" \
    "$PROJECT_DIR/data" \
    "$PROJECT_DIR/models"
}

normalize_chapter() {
  local value="${1:-}"
  if [[ "$value" =~ ^ch([0-9]|0[1-9]|1[0-9])$ ]]; then
    printf 'ch%02d\n' "$((10#${BASH_REMATCH[1]}))"
    return
  fi
  if [[ "$value" =~ ^([0-9]|0[1-9]|1[0-9])$ ]]; then
    printf 'ch%02d\n' "$((10#${BASH_REMATCH[1]}))"
    return
  fi
  printf 'chapter must be ch01 through ch19\n' >&2
  return 2
}

service_for_chapter() {
  local chapter="$1"
  local number=$((10#${chapter#ch}))
  if ((number <= 11)); then
    printf 'core\n'
  elif ((number <= 17)); then
    printf 'torch\n'
  elif ((number == 18)); then
    printf 'gnn\n'
  else
    printf 'rl\n'
  fi
}

jupyter_token() {
  local token_file="$PROJECT_DIR/.state/jupyter_token"
  if [[ ! -s "$token_file" ]]; then
    umask 077
    openssl rand -hex 24 >"$token_file"
  fi
  chmod 600 "$token_file"
  tr -d '\n' <"$token_file"
}
