#!/usr/bin/env bash
set -Eeuo pipefail

if ! command -v nvidia-smi >/dev/null 2>&1; then
  printf 'nvidia-smi is unavailable. Start this service with the NVIDIA container runtime.\n' >&2
  exit 1
fi

nvidia-smi --query-gpu=name,driver_version,memory.total --format=csv,noheader

python - <<'PY'
import torch

print(f"torch: {torch.__version__}")
print(f"torch.cuda.is_available(): {torch.cuda.is_available()}")
if not torch.cuda.is_available():
    print("The book baseline intentionally installs the CPU PyTorch wheel.")
    print("GPU visibility passed; a CUDA PyTorch candidate is a separate compatibility update.")
PY
