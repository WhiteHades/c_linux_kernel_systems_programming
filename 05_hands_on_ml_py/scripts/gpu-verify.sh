#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

ensure_state
require_docker
compose --profile gpu build gpu
compose --profile gpu run --rm --no-deps gpu verify gpu
