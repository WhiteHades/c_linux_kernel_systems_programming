#!/usr/bin/env bash
set -euo pipefail
exec setpriv \
  --reuid="${BOOK_UID:?}" --regid="${BOOK_GID:?}" --clear-groups \
  --inh-caps=-all,+net_raw,+net_admin \
  --ambient-caps=-all,+net_raw,+net_admin \
  --bounding-set=-all,+net_raw,+net_admin \
  -- "$@"
