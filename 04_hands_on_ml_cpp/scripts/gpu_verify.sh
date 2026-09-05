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
            printf 'usage: gpu_verify.sh [--dry-run]\n'
            exit 0
            ;;
        *)
            fatal "unknown GPU verification option: $argument"
            ;;
    esac
done

require_project
require_host_tools
require_compose_file
require_free_space "$MIN_FREE_GIB" "GPU verification"
has_command nvidia-smi || fatal "nvidia-smi is not available on the host"

if [[ -n "${MLCPP_PROFILES:-}" ]]; then
    MLCPP_PROFILES="${MLCPP_PROFILES},gpu"
else
    MLCPP_PROFILES=gpu
fi
export MLCPP_PROFILES

service="${MLCPP_GPU_SERVICE:-${MLCPP_SERVICE:-gpu}}"
verification_command='set -eu
command -v nvidia-smi
nvidia-smi --query-gpu=name,memory.total --format=csv,noheader
command -v python
python -c '\''import torch; assert torch.cuda.is_available(), "PyTorch CUDA is unavailable"; print(torch.cuda.get_device_name(0))'\''
if command -v nvcc >/dev/null 2>&1; then
    nvcc --version | tail -n 1
fi'

if ((dry_run)); then
    print_command sudo docker compose --project-directory "$PROJECT_ROOT" --file "$COMPOSE_FILE" --project-name "$PROJECT_NAME" --profile gpu run --rm --gpus all "$service" bash -c "$verification_command"
    exit 0
fi

auth_docker
docker_compose config --quiet >/dev/null
service="$(resolve_service "$service" gpu cuda book dev mlcpp ml-cpp core)"
printf 'gpu verify: %s\n' "$service"
compose_with_profiles build "$service"
run_gpu_service_shell "$service" "$verification_command"
printf 'gpu verify: passed\n'
