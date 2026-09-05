#!/usr/bin/env bash
set -euo pipefail

source "$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)/common.sh"

[[ $# -eq 0 || ( $# -eq 1 && ( "$1" == "--help" || "$1" == "-h" ) ) ]] || fatal "storage.sh takes no options"
if [[ $# -eq 1 ]]; then
    printf 'usage: storage.sh\n'
    exit 0
fi

require_project
require_command df
require_command awk
require_command du
require_command numfmt
storage_report
