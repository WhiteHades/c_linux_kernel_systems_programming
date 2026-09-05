#!/usr/bin/env bash
set -euo pipefail
source "$(dirname -- "$0")/common.sh"

printf 'Filesystem\n'
df -h "$PROJECT_DIR"
printf '\nProject usage\n'
for path in code .state/runtime data models; do
  if [[ -e "$PROJECT_DIR/$path" ]]; then
    du -sh "$PROJECT_DIR/$path"
  fi
done
printf '\nHeavy-task floor: keep at least 150 GiB free before full image builds.\n'

if docker info >/dev/null 2>&1; then
  printf '\nDocker usage\n'
  docker system df
elif sudo -n docker info >/dev/null 2>&1; then
  printf '\nDocker usage\n'
  sudo -n docker system df
else
  printf '\nDocker usage is hidden by the Omarchy admin boundary.\n'
fi
