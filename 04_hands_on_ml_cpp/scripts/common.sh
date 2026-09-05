#!/usr/bin/env bash

# Shared, deliberately small helpers for the mise tasks in this project.
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)"
PROJECT_ROOT="$(cd -- "$SCRIPT_DIR/.." && pwd -P)"
STATE_DIR="${MLCPP_STATE_DIR:-$PROJECT_ROOT/.state}"
COMPOSE_FILE="${MLCPP_COMPOSE_FILE:-$PROJECT_ROOT/compose.yaml}"
MIN_FREE_GIB="${MLCPP_MIN_FREE_GIB:-150}"

# Keep all Compose objects under a project name that is stable for this folder.
if [[ -n "${COMPOSE_PROJECT_NAME:-}" ]]; then
    PROJECT_NAME="$COMPOSE_PROJECT_NAME"
else
    PROJECT_NAME="$(basename -- "$PROJECT_ROOT" | tr '[:upper:]' '[:lower:]' | sed 's/[^a-z0-9_-]/-/g')"
fi

info() {
    printf 'info: %s\n' "$*"
}

warn() {
    printf 'warning: %s\n' "$*" >&2
}

fatal() {
    printf 'error: %s\n' "$*" >&2
    exit 1
}

has_command() {
    command -v "$1" >/dev/null 2>&1
}

require_command() {
    local command_name="$1"
    has_command "$command_name" || fatal "required command not found: $command_name"
}

require_project() {
    [[ -d "$PROJECT_ROOT" ]] || fatal "project directory is missing: $PROJECT_ROOT"
    [[ -d "$PROJECT_ROOT/code" ]] || fatal "the Packt checkout is missing: $PROJECT_ROOT/code"
}

require_compose_file() {
    [[ -f "$COMPOSE_FILE" ]] || fatal "Compose file is missing: $COMPOSE_FILE"
}

require_host_tools() {
    local command_name
    for command_name in omarchy sudo docker; do
        require_command "$command_name"
    done
}

docker_cmd() {
    # Docker is intentionally sudo-gated on Omarchy. Do not silently fall back
    # to an unprivileged Docker socket or ask the user to join docker.sock.
    sudo docker "$@"
}

docker_cmd_noprompt() {
    sudo -n docker "$@"
}

docker_compose() {
    docker_cmd compose \
        --project-directory "$PROJECT_ROOT" \
        --file "$COMPOSE_FILE" \
        --project-name "$PROJECT_NAME" \
        "$@"
}

docker_compose_noprompt() {
    docker_cmd_noprompt compose \
        --project-directory "$PROJECT_ROOT" \
        --file "$COMPOSE_FILE" \
        --project-name "$PROJECT_NAME" \
        "$@"
}

compose_with_profiles() {
    local -a profile_args=()
    local profile
    if [[ -n "${MLCPP_PROFILES:-}" ]]; then
        # Accept either a comma-separated or whitespace-separated value.
        local profile_list="${MLCPP_PROFILES//,/ }"
        read -r -a profile_args <<< "$profile_list"
        local -a normalized=()
        for profile in "${profile_args[@]}"; do
            [[ -n "$profile" ]] && normalized+=(--profile "$profile")
        done
        docker_compose "${normalized[@]}" "$@"
        return
    fi
    docker_compose "$@"
}

compose_with_profiles_noprompt() {
    local -a profile_args=()
    local profile
    if [[ -n "${MLCPP_PROFILES:-}" ]]; then
        local profile_list="${MLCPP_PROFILES//,/ }"
        read -r -a profile_args <<< "$profile_list"
        local -a normalized=()
        for profile in "${profile_args[@]}"; do
            [[ -n "$profile" ]] && normalized+=(--profile "$profile")
        done
        docker_compose_noprompt "${normalized[@]}" "$@"
        return
    fi
    docker_compose_noprompt "$@"
}

compose_services() {
    compose_with_profiles config --services
}

compose_services_noprompt() {
    compose_with_profiles_noprompt config --services
}

service_exists() {
    local requested="$1"
    local service
    while IFS= read -r service; do
        [[ "$service" == "$requested" ]] && return 0
    done < <(compose_services)
    return 1
}

resolve_service() {
    local requested="${1:-}"
    shift || true
    local candidate
    local -a services=()
    mapfile -t services < <(compose_services)
    ((${#services[@]} > 0)) || fatal "Compose defines no services"

    if [[ -n "$requested" ]]; then
        for candidate in "${services[@]}"; do
            [[ "$candidate" == "$requested" ]] && {
                printf '%s\n' "$candidate"
                return 0
            }
        done
        fatal "Compose service does not exist: $requested"
    fi

    for requested in "$@"; do
        for candidate in "${services[@]}"; do
            [[ "$candidate" == "$requested" ]] && {
                printf '%s\n' "$candidate"
                return 0
            }
        done
    done

    if ((${#services[@]} == 1)); then
        printf '%s\n' "${services[0]}"
        return 0
    fi

    fatal "set MLCPP_SERVICE; available services: ${services[*]}"
}

resolve_service_noprompt() {
    local requested="${1:-}"
    shift || true
    local candidate
    local -a services=()
    mapfile -t services < <(compose_services_noprompt)
    ((${#services[@]} > 0)) || fatal "Compose defines no services"

    if [[ -n "$requested" ]]; then
        for candidate in "${services[@]}"; do
            [[ "$candidate" == "$requested" ]] && {
                printf '%s\n' "$candidate"
                return 0
            }
        done
        fatal "Compose service does not exist: $requested"
    fi

    for requested in "$@"; do
        for candidate in "${services[@]}"; do
            [[ "$candidate" == "$requested" ]] && {
                printf '%s\n' "$candidate"
                return 0
            }
        done
    done

    if ((${#services[@]} == 1)); then
        printf '%s\n' "${services[0]}"
        return 0
    fi

    fatal "set MLCPP_SERVICE; available services: ${services[*]}"
}

auth_docker() {
    # Authenticate only when a task is about to perform a Docker operation.
    sudo -v || fatal "sudo authentication is required for Docker"
    docker_cmd info >/dev/null || fatal "sudo-gated Docker is not available"
}

run_service() {
    local service="$1"
    shift
    compose_with_profiles run --rm "$service" "$@"
}

run_service_shell() {
    local service="$1"
    local command_text="$2"
    run_service "$service" bash -c "$command_text"
}

run_gpu_service_shell() {
    local service="$1"
    local command_text="$2"
    compose_with_profiles run --rm --gpus all "$service" bash -c "$command_text"
}

free_bytes() {
    df -Pk -- "$PROJECT_ROOT" | awk 'NR == 2 { print $4 * 1024 }'
}

free_gib() {
    local bytes
    bytes="$(free_bytes)"
    printf '%s\n' "$((bytes / 1024 / 1024 / 1024))"
}

project_bytes() {
    du -sx -B1 -- "$PROJECT_ROOT" | awk '{ print $1 }'
}

format_bytes() {
    numfmt --to=iec -- "$1"
}

storage_report() {
    local available_bytes available_gib project_size
    available_bytes="$(free_bytes)"
    available_gib="$((available_bytes / 1024 / 1024 / 1024))"
    project_size="$(project_bytes)"
    printf 'project: %s\n' "$PROJECT_ROOT"
    printf 'free: %s (%s GiB)\n' "$(format_bytes "$available_bytes")" "$available_gib"
    printf 'project size: %s\n' "$(format_bytes "$project_size")"
    printf 'heavy-task floor: %s GiB\n' "$MIN_FREE_GIB"
    if ((available_gib >= MIN_FREE_GIB)); then
        printf 'storage status: ready\n'
    else
        printf 'storage status: below heavy-task floor\n'
    fi
}

require_free_space() {
    local required_gib="${1:-$MIN_FREE_GIB}"
    local purpose="${2:-this task}"
    [[ "$required_gib" =~ ^[0-9]+$ ]] || fatal "invalid storage threshold: $required_gib"
    local available_gib
    available_gib="$(free_gib)"
    ((available_gib >= required_gib)) || fatal "$purpose needs at least ${required_gib} GiB free; only ${available_gib} GiB is available"
}

state_init() {
    mkdir -p -- \
        "$STATE_DIR/home" \
        "$STATE_DIR/runtime" \
        "$PROJECT_ROOT/data" \
        "$PROJECT_ROOT/models"
}

print_command() {
    local part
    printf '[dry-run]'
    for part in "$@"; do
        printf ' %q' "$part"
    done
    printf '\n'
}

git_state() {
    if [[ -d "$PROJECT_ROOT/code/.git" ]]; then
        git -C "$PROJECT_ROOT/code" status --short --branch
    else
        printf 'code checkout: missing\n'
    fi
}

container_code_path_script() {
    local chapter_script="$1"
    cat <<EOF
set -eu
for root in /workspace/code /samples /development/code; do
    if [ -f "\$root/build_scripts/$chapter_script" ]; then
        cd "\$root/build_scripts"
        temporary_script="\$(mktemp)"
        trap 'rm -f "\$temporary_script"' EXIT
        sed -E \
            -e 's/^[[:space:]]*mkdir[[:space:]]+build[[:space:]]*$/mkdir -p build/' \
            -e 's#^[[:space:]]*LIBS_DIR=.*\$#LIBS_DIR="\${BOOK_PREFIX:-/opt/book/libs}"#' \
            "$chapter_script" > "\$temporary_script"
        exec bash -e "\$temporary_script"
    fi
done
echo "book checkout not found in /workspace/code, /samples, or /development/code" >&2
exit 2
EOF
}

container_path_script() {
    local script_name="$1"
    cat <<EOF
set -eu
for root in /workspace/code /samples /development/code; do
    if [ -f "\$root/$script_name" ]; then
        cd "\$root"
        exec bash "$script_name"
    fi
done
echo "book checkout not found in /workspace/code, /samples, or /development/code" >&2
exit 2
EOF
}
