#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

CODE_DIR="$PROJECT_ROOT/code"
CODE_REPOSITORY="https://github.com/PacktPublishing/Hands-on-Machine-learning-with-C-Second-Edition.git"
CODE_REVISION="f9f3e95a2ef7f51355613cf3454ae02bb710b088"

code_is_checkout() {
    local top
    [[ -d "$CODE_DIR" ]] || return 1
    top="$(git -C "$CODE_DIR" rev-parse --show-toplevel 2>/dev/null || true)"
    [[ "$top" == "$CODE_DIR" ]]
}

ensure_code_checkout() {
    require_command git
    if code_is_checkout; then
        if ((dry_run)); then
            printf 'setup: existing author checkout unchanged: %s\n' "$CODE_DIR"
        fi
        return
    fi

    if [[ -e "$CODE_DIR" ]]; then
        [[ -d "$CODE_DIR" ]] || fatal "code exists but is not a directory: $CODE_DIR"
        local first_entry
        first_entry="$(find "$CODE_DIR" -mindepth 1 -maxdepth 1 -print -quit)"
        [[ -z "$first_entry" ]] || fatal "code exists but is not a git checkout: $CODE_DIR"
    fi

    if ((dry_run)); then
        printf 'setup: author checkout is missing; planned fetch\n'
        print_command git clone --no-checkout "$CODE_REPOSITORY" "$CODE_DIR"
        print_command git -C "$CODE_DIR" checkout --detach "$CODE_REVISION"
        return
    fi

    git clone --no-checkout "$CODE_REPOSITORY" "$CODE_DIR"
    git -C "$CODE_DIR" checkout --detach "$CODE_REVISION"
}

dry_run=0
build_all=0
for argument in "$@"; do
    case "$argument" in
        --dry-run|--read-only)
            dry_run=1
            ;;
        --all)
            build_all=1
            ;;
        --help|-h)
            printf 'usage: setup.sh [--dry-run] [--all]\n'
            printf '  builds the core service; --all also builds active Compose profiles\n'
            exit 0
            ;;
        *)
            fatal "unknown setup option: $argument"
            ;;
    esac
done

ensure_code_checkout
if (( ! dry_run )); then
    require_project
fi
require_host_tools
require_compose_file
require_free_space "$MIN_FREE_GIB" "the environment build"

service="${MLCPP_SERVICE:-book}"
if ((build_all)); then
    if [[ -n "${MLCPP_PROFILES:-}" ]]; then
        MLCPP_PROFILES="${MLCPP_PROFILES},gpu,android"
    else
        MLCPP_PROFILES=gpu,android
    fi
    export MLCPP_PROFILES
fi
if ((dry_run)); then
    printf 'setup: read-only plan\n'
    storage_report
    if ((build_all)); then
        print_command sudo docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" --profile gpu --profile android build --pull
    else
        print_command sudo docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" build --pull "$service"
    fi
    exit 0
fi

auth_docker
docker_compose config --quiet >/dev/null
state_init
printf 'setup: building the contained environment\n'
if ((build_all)); then
    compose_with_profiles build --pull
else
    service="$(resolve_service "$service" book dev mlcpp ml-cpp core)"
    compose_with_profiles build --pull "$service"
fi
printf 'setup: image build complete\n'
