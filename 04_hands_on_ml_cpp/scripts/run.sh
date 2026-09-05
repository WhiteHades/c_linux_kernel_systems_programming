#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

target="${1:-}"
[[ -n "$target" ]] || {
    printf 'usage: mise run run -- PATH/TO/PROGRAM [arguments...]\n' >&2
    exit 2
}
shift

case "$target" in
    /*|../*|*/../*|*/..)
        fatal "program must be inside code/: $target"
        ;;
esac
[[ -f "$PROJECT_ROOT/code/$target" ]] || fatal "program not found: code/$target"
[[ -x "$PROJECT_ROOT/code/$target" ]] || fatal "program is not executable: code/$target"

require_project
require_host_tools
require_compose_file
auth_docker
docker_compose config --quiet >/dev/null
run_service book "/workspace/code/$target" "$@"
