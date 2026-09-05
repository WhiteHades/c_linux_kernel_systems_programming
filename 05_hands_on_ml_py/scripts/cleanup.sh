#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

mode="${1:---plan}"
case "$mode" in
  --plan)
    printf 'Project-only cleanup plan:\n'
    printf '  containers and networks: docker compose down --remove-orphans\n'
    printf '  project images:          docker compose down --remove-orphans --rmi all\n'
    printf 'Book code, datasets, models, and runtime state are never removed.\n'
    ;;
  --containers)
    require_docker
    compose --profile '*' down --remove-orphans
    ;;
  --images)
    require_docker
    compose --profile '*' down --remove-orphans --rmi all
    ;;
  *)
    printf 'usage: %s [--plan|--containers|--images]\n' "$0" >&2
    exit 2
    ;;
esac
