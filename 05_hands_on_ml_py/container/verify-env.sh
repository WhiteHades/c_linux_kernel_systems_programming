#!/usr/bin/env bash
set -euo pipefail

profile="${1:-${BOOK_PROFILE:-core}}"

python - "$profile" <<'PY'
import importlib
import importlib.metadata
import os
import pathlib
import subprocess
import sys

profile = sys.argv[1]
expected = {
    "numpy": "1.21.2",
    "pandas": "1.3.2",
    "scipy": "1.7.0",
    "scikit-learn": "1.0",
    "matplotlib": "3.4.3",
    "jupyterlab": "3.4.4",
}
if profile in {"torch", "gnn", "rl", "gpu"}:
    expected.update({
        "torch": "1.9.0",
        "torchvision": "0.10.0",
        "torchtext": "0.10.0",
        "pytorch-lightning": "1.5.0",
    })
if profile == "gnn":
    expected.update({
        "networkx": "2.6.2",
        "torch-geometric": "2.0.2",
        "torch-scatter": "2.0.9",
        "torch-sparse": "0.6.12",
    })
if profile == "rl":
    expected["gym"] = "0.20.0"

errors = []
for package, wanted in expected.items():
    try:
        got = importlib.metadata.version(package)
    except importlib.metadata.PackageNotFoundError:
        errors.append(f"{package}: missing")
        continue
    if got.split("+")[0] != wanted:
        errors.append(f"{package}: expected {wanted}, got {got}")

imports = ["numpy", "pandas", "scipy", "sklearn", "matplotlib", "jupyterlab"]
if profile in {"torch", "gnn", "rl", "gpu"}:
    imports += ["torch", "torchvision", "torchtext", "pytorch_lightning"]
if profile == "gnn":
    imports += ["networkx", "torch_geometric", "torch_scatter", "torch_sparse"]
if profile == "rl":
    imports += ["gym"]
for module in imports:
    try:
        importlib.import_module(module)
    except Exception as exc:
        errors.append(f"import {module}: {type(exc).__name__}: {exc}")

if sys.version_info[:2] != (3, 9):
    errors.append(f"Python: expected 3.9, got {sys.version.split()[0]}")
code_path = pathlib.Path("/workspace/code")
if not (code_path / ".git").is_dir():
    errors.append("official repository mount is missing")
elif not code_path.is_dir():
    errors.append("working repository is unavailable")
elif not os.access(code_path, os.W_OK):
    errors.append("working repository is not writable")

if profile == "gpu":
    import torch
    if not torch.cuda.is_available():
        errors.append("PyTorch cannot use CUDA")

if errors:
    print("environment verification failed:", file=sys.stderr)
    for error in errors:
        print(f"- {error}", file=sys.stderr)
    raise SystemExit(1)

commit = subprocess.check_output(
    ["git", "-C", "/workspace/code", "rev-parse", "HEAD"], text=True
).strip()
print(f"profile={profile}")
print(f"python={sys.version.split()[0]}")
print(f"official_commit={commit}")
print("environment=ok")
PY
