#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

dry_run=0
for argument in "$@"; do
    case "$argument" in
        --dry-run|--read-only)
            dry_run=1
            ;;
        --help|-h)
            printf 'usage: android_build.sh [--dry-run]\n'
            exit 0
            ;;
        *)
            fatal "unknown Android option: $argument"
            ;;
    esac
done

require_project
require_host_tools
require_compose_file
require_free_space "$MIN_FREE_GIB" "the Android environment build"

if [[ -n "${MLCPP_PROFILES:-}" ]]; then
    MLCPP_PROFILES="${MLCPP_PROFILES},android"
else
    MLCPP_PROFILES=android
fi
export MLCPP_PROFILES

service="${MLCPP_ANDROID_SERVICE:-${MLCPP_SERVICE:-android}}"
android_command=/usr/local/bin/build-android-chapter.sh

if ((dry_run)); then
    print_command sudo docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" --profile android run --rm "$service" bash -c "$android_command"
    exit 0
fi

auth_docker
docker_compose config --quiet >/dev/null
service="$(resolve_service "$service" android android-build book-android book dev mlcpp ml-cpp core)"
printf 'android build: %s\n' "$service"
compose_with_profiles build "$service"
run_service_shell "$service" "$android_command"
printf 'android build: passed\n'
