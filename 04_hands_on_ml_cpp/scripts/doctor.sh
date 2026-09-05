#!/usr/bin/env bash
set -euo pipefail

# This command is read-only. It never installs host packages or changes Docker.
source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

require_project
require_host_tools
require_command df
require_command awk
require_command numfmt

status=0

printf 'Omarchy book environment doctor\n'
printf 'host: %s\n' "$(uname -srmo)"
printf 'project: %s\n' "$PROJECT_ROOT"

if has_command mise; then
    printf 'mise: %s\n' "$(mise --version 2>/dev/null || printf 'available')"
else
    warn "mise is not on PATH; invoke the scripts through the project task interface"
    status=1
fi

printf 'omarchy: %s\n' "$(command -v omarchy)"
printf 'docker: %s\n' "$(docker --version 2>/dev/null || printf 'available')"

available_gib="$(free_gib)"
printf 'free storage: %s GiB\n' "$available_gib"
if ((available_gib < MIN_FREE_GIB)); then
    warn "free storage is below the ${MIN_FREE_GIB} GiB heavy-task floor"
    status=1
else
    printf 'storage: ready for heavy tasks\n'
fi

if [[ ! -f "$COMPOSE_FILE" ]]; then
    warn "Compose file is missing: $COMPOSE_FILE"
    status=1
else
    if docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" --profile '*' config --quiet >/dev/null 2>&1; then
        printf 'compose: valid\n'
        config="$(docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" --profile '*' config)"

        # These checks protect the boundary promised by this project. A project
        # checkout mount is expected; credentials, Docker's socket, host
        # networking, and privileged mode are not.
        home_dir="$(realpath -- "$HOME")"
        for forbidden in \
            'privileged: true' \
            'network_mode: host' \
            'network_mode: "host"' \
            'docker.sock' \
            'source: /root' \
            '.ssh' \
            '.gnupg'; do
            if grep -Fq -- "$forbidden" <<< "$config"; then
                warn "Compose boundary check found forbidden setting: $forbidden"
                status=1
            fi
        done
        if sed 's/^[[:space:]]*//' <<< "$config" | grep -Fxq -- "source: $home_dir"; then
            warn "Compose boundary check found a full home-directory mount"
            status=1
        fi
    else
        warn "Compose configuration is invalid"
        status=1
    fi
fi

if docker_cmd_noprompt info >/dev/null 2>&1; then
    printf 'docker daemon: reachable with cached administrator authorization\n'
elif systemctl is-active --quiet docker 2>/dev/null; then
    printf 'docker daemon: active; setup will request administrator authorization\n'
else
    warn "Docker daemon is not active"
    status=1
fi

if has_command nvidia-smi; then
    if nvidia-smi --query-gpu=name,memory.total --format=csv,noheader 2>/dev/null; then
        printf 'gpu: available on host\n'
    else
        warn "nvidia-smi is present but the host GPU check failed"
    fi
else
    warn "nvidia-smi is not installed; GPU tasks will not be available"
fi

if [[ -d "$PROJECT_ROOT/code/.git" ]]; then
    printf 'book checkout: %s\n' "$(git -C "$PROJECT_ROOT/code" rev-parse --short HEAD)"
else
    warn "book checkout is missing"
    status=1
fi

if ((status == 0)); then
    printf 'doctor: ready\n'
else
    printf 'doctor: action needed\n'
fi
exit "$status"
