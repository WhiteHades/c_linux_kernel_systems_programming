#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

mode=quick
dry_run=0
for argument in "$@"; do
    case "$argument" in
        --env)
            mode=env
            ;;
        --quick)
            mode=quick
            ;;
        --all)
            mode=all
            ;;
        --dry-run|--read-only)
            dry_run=1
            ;;
        --help|-h)
            printf 'usage: verify.sh [--env|--quick|--all] [--dry-run]\n'
            printf '  default: verify the environment and build Chapter 1\n'
            printf '  --all: attempt every Chapter 1-13 build; upstream assets are incomplete\n'
            exit 0
            ;;
        *)
            fatal "unknown verification option: $argument"
            ;;
    esac
done

require_project
require_host_tools
require_compose_file
require_free_space "$MIN_FREE_GIB" "verification"

service="${MLCPP_SERVICE:-book}"
if ((dry_run)); then
    print_command sudo docker compose \
        --project-directory "$PROJECT_ROOT" \
        --file "$COMPOSE_FILE" \
        --project-name "$PROJECT_NAME" \
        run --rm "$service" verify-book "$mode"
    exit 0
fi

auth_docker
docker_compose config --quiet >/dev/null
service="$(resolve_service "$service" book dev mlcpp ml-cpp core)"
run_service "$service" verify-book "$mode"
