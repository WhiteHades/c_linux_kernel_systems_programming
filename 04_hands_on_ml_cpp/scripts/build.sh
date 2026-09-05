#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

usage() {
    printf 'usage: build.sh CHAPTER [--dry-run]\n'
    printf '  CHAPTER is 1..14, ch01..ch14, or 01..14\n'
}

dry_run=0
chapter_input=""
for argument in "$@"; do
    case "$argument" in
        --dry-run|--read-only)
            dry_run=1
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        *)
            if [[ -z "$chapter_input" ]]; then
                chapter_input="$argument"
            else
                fatal "more than one chapter was provided: $chapter_input and $argument"
            fi
            ;;
    esac
done

[[ -n "$chapter_input" ]] || {
    usage >&2
    exit 2
}

case "$chapter_input" in
    ch0[1-9]|ch1[0-4])
        chapter_number="${chapter_input#ch}"
        ;;
    0[1-9]|1[0-4])
        chapter_number="$chapter_input"
        ;;
    [1-9]|1[0-4])
        chapter_number="$chapter_input"
        ;;
    *)
        fatal "invalid chapter: $chapter_input"
        ;;
esac

chapter_number="$((10#$chapter_number))"
chapter_script="build_ch${chapter_number}.sh"

if ((chapter_number == 14)); then
    if ((dry_run)); then
        exec "$SCRIPT_DIR/android_build.sh" --dry-run
    fi
    exec "$SCRIPT_DIR/android_build.sh"
fi

require_project
require_host_tools
require_compose_file
require_free_space "$MIN_FREE_GIB" "building Chapter $chapter_number"

if ((dry_run)); then
    service="${MLCPP_SERVICE:-book}"
    command_text="$(container_code_path_script "$chapter_script")"
    print_command sudo docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" run --rm "$service" bash -c "$command_text"
    exit 0
fi

auth_docker
docker_compose config --quiet >/dev/null
service="$(resolve_service "${MLCPP_SERVICE:-book}" book dev mlcpp ml-cpp core)"
run_service_shell "$service" "$(container_code_path_script "$chapter_script")"
