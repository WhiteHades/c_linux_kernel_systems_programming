#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

failures=0

check_command() {
  local command="$1"
  if command -v "$command" >/dev/null 2>&1; then
    printf '%-22s %s\n' "$command" "$(command -v "$command")"
  else
    printf '%-22s missing\n' "$command"
    failures=$((failures + 1))
  fi
}

printf 'Host\n'
printf '%-22s %s\n' omarchy "$(omarchy-version 2>/dev/null || printf 'not detected')"
printf '%-22s %s\n' mise "$(mise --version 2>/dev/null || printf 'missing')"
for command in docker openssl jq nvim; do
  check_command "$command"
done

printf '\nProject\n'
if [[ -f "$PROJECT_DIR/machine_learning_with_pytorch_and_scikit_learn.txt" ]]; then
  printf '%-22s present and private\n' book-text
else
  printf '%-22s missing\n' book-text
  failures=$((failures + 1))
fi
if [[ -d "$PROJECT_DIR/code/.git" ]]; then
  printf '%-22s %s\n' official-checkout "$(git -C "$PROJECT_DIR/code" rev-parse --short=12 HEAD)"
else
  printf '%-22s missing\n' official-checkout
  failures=$((failures + 1))
fi

free_gib="$(df -BG --output=avail "$PROJECT_DIR" | tail -1 | tr -dc '0-9')"
printf '%-22s %s GiB free\n' storage "$free_gib"
if ((free_gib < 150)); then
  printf '%-22s need at least 150 GiB before a full build\n' storage-gate
  failures=$((failures + 1))
else
  printf '%-22s ready\n' storage-gate
fi

if compose_direct --profile '*' config --quiet; then
  printf '%-22s valid\n' compose
else
  printf '%-22s invalid\n' compose
  failures=$((failures + 1))
fi

config_json="$(compose_direct --profile '*' config --format json)"
if jq -e '
  [.services[] |
    (.privileged // false),
    ((.network_mode // "") == "host"),
    (.volumes[]?.source == "/var/run/docker.sock")
  ] | any | not
' >/dev/null <<<"$config_json"; then
  printf '%-22s no privileged, host-network, or socket access\n' isolation
else
  printf '%-22s unsafe container setting detected\n' isolation
  failures=$((failures + 1))
fi

if jq -e --arg home "$HOME" '
  [.services[].volumes[]?.source |
    select(. == $home or startswith($home + "/.ssh") or
      startswith($home + "/.gnupg") or startswith($home + "/.config/calibre"))
  ] | length == 0
' >/dev/null <<<"$config_json"; then
  printf '%-22s no home, key, or Calibre mount\n' private-mounts
else
  printf '%-22s sensitive host mount detected\n' private-mounts
  failures=$((failures + 1))
fi

if docker info >/dev/null 2>&1; then
  printf '%-22s ready\n' docker-daemon
elif systemctl is-active --quiet docker; then
  printf '%-22s active; Omarchy admin authentication required\n' docker-daemon
else
  printf '%-22s inactive\n' docker-daemon
  failures=$((failures + 1))
fi

if command -v nvidia-smi >/dev/null 2>&1; then
  gpu="$(nvidia-smi --query-gpu=name,memory.total --format=csv,noheader 2>/dev/null | head -1 || true)"
  printf '%-22s %s\n' gpu "${gpu:-driver present; unavailable now}"
else
  printf '%-22s not detected; CPU profiles remain supported\n' gpu
fi

if ((failures)); then
  printf '\nDoctor found %d blocking issue(s).\n' "$failures" >&2
  exit 1
fi
printf '\nDoctor: ready.\n'
