#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

dry_run=0
gpu=0
for argument in "$@"; do
    case "$argument" in
        --dry-run|--read-only)
            dry_run=1
            ;;
        --gpu)
            gpu=1
            ;;
        --help|-h)
            printf 'usage: shell.sh [--gpu] [--dry-run]\n'
            exit 0
            ;;
        *)
            fatal "unknown shell option: $argument"
            ;;
    esac
done

require_project
require_host_tools
require_compose_file

if ((gpu)); then
    if [[ -n "${MLCPP_PROFILES:-}" ]]; then
        MLCPP_PROFILES="${MLCPP_PROFILES},gpu"
    else
        MLCPP_PROFILES=gpu
    fi
    export MLCPP_PROFILES
fi

if ((gpu)); then
    service="${MLCPP_GPU_SERVICE:-${MLCPP_SERVICE:-gpu}}"
else
    service="${MLCPP_SERVICE:-book}"
fi

if ((dry_run)); then
    if ((gpu)); then
        print_command sudo docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" --profile gpu run --rm --gpus all "$service" bash
    else
        print_command sudo docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" run --rm "$service" bash
    fi
    exit 0
fi

auth_docker
docker_compose config --quiet >/dev/null
if ((gpu)); then
    service="$(resolve_service "$service" gpu cuda book dev mlcpp ml-cpp core)"
    run_gpu_service_shell "$service" 'exec bash'
else
    service="$(resolve_service "$service" book dev mlcpp ml-cpp core)"
    run_service_shell "$service" 'exec bash'
fi
