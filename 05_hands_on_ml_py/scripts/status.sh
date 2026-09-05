#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

printf 'Book repository: %s\n' "$(git -C "$PROJECT_DIR/code" rev-parse --short=12 HEAD)"
printf 'Working tree:\n'
git -C "$PROJECT_DIR/code" status --short --branch
printf 'Free storage: %s\n' "$(df -h --output=avail "$PROJECT_DIR" | tail -1 | xargs)"

if docker info >/dev/null 2>&1; then
  compose_direct --profile '*' ps -a
elif sudo -n docker info >/dev/null 2>&1; then
  DOCKER_PREFIX=(sudo -n)
  compose --profile '*' ps -a
else
  printf 'Containers: Docker is admin-gated; run a Docker task for authentication.\n'
fi
