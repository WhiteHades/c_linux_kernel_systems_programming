#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

storage_only=0
for argument in "$@"; do
    case "$argument" in
        --storage)
            storage_only=1
            ;;
        --help|-h)
            printf 'usage: status.sh [--storage]\n'
            exit 0
            ;;
        *)
            fatal "unknown status option: $argument"
            ;;
    esac
done

require_project
require_command df
require_command awk
require_command du
require_command numfmt

storage_report
((storage_only)) && exit 0

printf 'code checkout:\n'
git_state

if [[ -f "$COMPOSE_FILE" ]]; then
    printf 'compose file: %s\n' "$COMPOSE_FILE"
    if docker_cmd_noprompt info >/dev/null 2>&1; then
        printf 'containers:\n'
        if ! docker_compose_noprompt ps --all; then
            warn "Compose status could not be read"
        fi
        printf 'project images:\n'
        if ! docker_cmd_noprompt image ls --filter "label=com.docker.compose.project=$PROJECT_NAME"; then
            warn "project image status could not be read"
        fi
    else
        warn "sudo-gated Docker status skipped; run 'sudo -v' to inspect it"
    fi
else
    printf 'compose file: not created yet\n'
fi

if has_command nvidia-smi; then
    printf 'host GPU:\n'
    nvidia-smi --query-gpu=name,memory.total,driver_version --format=csv,noheader 2>/dev/null || warn "host GPU status unavailable"
fi
