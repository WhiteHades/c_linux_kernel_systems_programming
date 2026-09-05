#!/usr/bin/env bash
set -euo pipefail

action="${1:?usage: book-container.sh setup|run IMAGE [COMMAND...]}"
image="${2:?image required}"
shift 2
project="$(pwd -P)"
[[ -f "$project/Dockerfile" ]] || { echo "Run this task from its book folder." >&2; exit 2; }

docker_cmd=(docker)
if ! docker info >/dev/null 2>&1; then
  if [[ "${BOOK_DOCKER:-}" == pkexec ]]; then
    docker_cmd=(pkexec docker)
  else
    docker_cmd=(sudo docker)
  fi
fi

case "$action" in
  setup)
    "${docker_cmd[@]}" build --progress=plain -t "$image" .
    ;;
  run)
    "${docker_cmd[@]}" image inspect "$image" >/dev/null 2>&1 || {
      echo "The book image is missing. Run: mise run setup" >&2
      exit 1
    }
    umask 077
    mkdir -p code exercises .state/home
    args=(run --rm --init --read-only --cap-drop=ALL
      --security-opt=no-new-privileges --pids-limit=2048
      --memory=16g --memory-swap=16g
      --shm-size=2g
      --user "${BOOK_UID:-$(id -u)}:${BOOK_GID:-$(id -g)}"
      --tmpfs /tmp:rw,nosuid,nodev,size=2g
      --workdir /workspace
      --env HOME=/workspace/.state/home
      --env XDG_CACHE_HOME=/workspace/.state/cache
      --env PYTHONUNBUFFERED=1
      --mount "type=bind,src=$project/code,dst=/workspace/code"
      --mount "type=bind,src=$project/exercises,dst=/workspace/exercises"
      --mount "type=bind,src=$project/.state,dst=/workspace/.state")
    [[ ! -f study.sh ]] || args+=(--mount "type=bind,src=$project/study.sh,dst=/opt/study.sh,readonly")
    [[ "${BOOK_GPU:-0}" != 1 ]] || args+=(--gpus all)
    if [[ "${BOOK_KVM:-0}" == 1 ]]; then
      [[ -e /dev/kvm ]] || { echo "/dev/kvm is unavailable." >&2; exit 1; }
      args+=(--device /dev/kvm --group-add "$(stat -c %g /dev/kvm)")
    fi
    if [[ -n "${BOOK_PORT:-}" ]]; then
      [[ "$BOOK_PORT" =~ ^[0-9]+$ ]] && ((BOOK_PORT > 1023 && BOOK_PORT < 65536)) || {
        echo "BOOK_PORT must be a port from 1024 to 65535." >&2; exit 2;
      }
      args+=(-p "127.0.0.1:$BOOK_PORT:$BOOK_PORT")
    fi
    [[ "${BOOK_NETWORK:-}" != none ]] || args+=(--network none)
    [[ ! -t 0 || ! -t 1 ]] || args+=(-t)
    "${docker_cmd[@]}" "${args[@]}" -i "$image" "${@:-bash}"
    ;;
  *)
    echo "usage: book-container.sh setup|run IMAGE [COMMAND...]" >&2
    exit 2
    ;;
esac
