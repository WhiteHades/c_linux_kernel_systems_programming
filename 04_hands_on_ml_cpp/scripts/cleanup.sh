#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

dry_run=0
apply=0
remove_builds=0
remove_images=0
remove_state=0
for argument in "$@"; do
    case "$argument" in
        --dry-run|--read-only)
            dry_run=1
            ;;
        --apply)
            apply=1
            ;;
        --builds)
            remove_builds=1
            ;;
        --images)
            remove_images=1
            ;;
        --state)
            remove_state=1
            ;;
        --help|-h)
            printf 'usage: cleanup.sh [--dry-run] [--apply] [--builds] [--images] [--state]\n'
            printf '  --apply is required; Docker cleanup is limited to this Compose project\n'
            printf '  --builds removes generated code/**/build directories\n'
            printf '  --state removes this project''s .state contents\n'
            exit 0
            ;;
        *)
            fatal "unknown cleanup option: $argument"
            ;;
    esac
done

require_project
require_host_tools
require_compose_file

if ((remove_state)); then
    [[ "$STATE_DIR" == "$PROJECT_ROOT/.state" ]] || fatal "--state requires the default project .state directory"
fi

down_args=(down --remove-orphans --volumes)
if ((remove_images)); then
    down_args+=(--rmi all)
fi

if ((dry_run || !apply)); then
    printf 'cleanup: read-only plan\n'
    if ((apply == 0)); then
        printf 'Nothing will be removed. Pass --apply to execute this plan.\n'
    fi
    print_command sudo docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" "${down_args[@]}"
    if ((remove_builds)); then
        printf 'generated build directories that would be removed:\n'
        find "$PROJECT_ROOT/code" -type d -name build -print
    fi
    if ((remove_state)); then
        printf 'state contents that would be removed:\n'
        if [[ -d "$STATE_DIR" ]]; then
            find "$STATE_DIR" -mindepth 1 -maxdepth 1 -print
        else
            printf '(none)\n'
        fi
    fi
    exit 0
fi

auth_docker
docker_compose "${down_args[@]}"

if ((remove_builds)); then
    while IFS= read -r -d '' build_dir; do
        case "$build_dir" in
            "$PROJECT_ROOT"/code/*/build|"$PROJECT_ROOT"/code/*/*/build)
                rm -rf -- "$build_dir"
                ;;
            *)
                fatal "refusing unexpected build directory: $build_dir"
                ;;
        esac
    done < <(find "$PROJECT_ROOT/code" -type d -name build -print0)
fi

if ((remove_state)) && [[ -d "$STATE_DIR" ]]; then
    find "$STATE_DIR" -mindepth 1 -maxdepth 1 -exec rm -rf -- {} +
fi

printf 'cleanup: completed for Compose project %s\n' "$PROJECT_NAME"
