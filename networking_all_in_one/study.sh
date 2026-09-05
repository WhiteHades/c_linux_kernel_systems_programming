#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "${BASH_SOURCE[0]}")"
umask 077
mkdir -p .state/home exercises
export BOOK_UID="${BOOK_UID:-$(id -u)}" BOOK_GID="${BOOK_GID:-$(id -g)}"
docker_cmd=(docker)
if ! docker info >/dev/null 2>&1; then
  if [[ ${BOOK_DOCKER:-} == pkexec ]]; then docker_cmd=(pkexec docker); else docker_cmd=(sudo docker); fi
fi
compose() { "${docker_cmd[@]}" compose "$@"; }
action="${1:-shell}"
shift || true
case "$action" in
  setup) compose build --progress plain ;;
  shell)
    compose up -d --wait
    compose exec "${1:-client}" /usr/local/bin/network-entrypoint bash
    ;;
  run)
    compose up -d --wait
    compose exec -T "${1:?usage: mise run run -- client|server COMMAND...}" /usr/local/bin/network-entrypoint "${@:2}"
    ;;
  verify)
    compose up -d --wait
    compose exec -T client /usr/local/bin/network-entrypoint sh -ec 'test "$(id -u)" = "$BOOK_UID"; getent hosts server; ping -c 1 server; curl -fsS http://server:8080/ >/dev/null; command -v ip dig traceroute tcpdump nc dnsmasq; echo "local dns, icmp, and http passed"'
    ;;
  stop) compose down ;;
  *) echo 'usage: setup|shell [client|server]|run client|server COMMAND|verify|stop' >&2; exit 2 ;;
esac
