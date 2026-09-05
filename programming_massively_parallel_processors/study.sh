#!/usr/bin/env bash
set -euo pipefail
action="${1:?expected fetch, build, or run}"
shift
case "$action" in
  fetch)
    mkdir -p code/lab-manuals exercises .state
    archive=.state/lab-materials.zip
    if [[ ! -f "$archive" ]]; then
      curl -fL --retry 2 'https://brand.elsevier.com/api/asset/eyJjbGllbnRJZCI6bnVsbCwiaWQiOjQxMjAsInRpbWVzdGFtcCI6MTczMjAxMzY0OSwidmVyc2lvbiI6MTcyOTU5NjkxOX0:elsevier:jmDqfL31yK5SSIKsTPXFOW-zveqsR3HKOgkPAJWGDRo/download' -o "$archive"
    fi
    printf '%s  %s\n' d43efe95fa95dbe8645770b3c0902f69c76b6f3729388ba766ae40f38a0fda0a "$archive" | sha256sum -c -
    unzip -nq "$archive" -d code/lab-manuals
    ;;
  build|run)
    [[ $# -gt 0 ]] || { echo "usage: mise run $action -- exercises/file.cu [nvcc flags]" >&2; exit 2; }
    mkdir -p .state/bin
    nvcc -arch=sm_75 -std=c++17 -O2 -lineinfo "$@" -o .state/bin/program
    [[ "$action" != run ]] || exec .state/bin/program
    ;;
  *) exit 2 ;;
esac
