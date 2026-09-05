#!/usr/bin/env bash
set -Eeuo pipefail

source /opt/book/versions-book-baseline.env

failures=0
check_command() {
  local command_name="$1"
  if command -v "$command_name" >/dev/null 2>&1; then
    printf 'ok   command %-12s %s\n' "$command_name" "$(command -v "$command_name")"
  else
    printf 'FAIL command %-12s missing\n' "$command_name"
    failures=$((failures + 1))
  fi
}

printf 'Hands-On Machine Learning with C++ environment\n'
printf 'user:       %s\n' "$(id -u):$(id -g)"
printf 'prefix:     %s\n' "${BOOK_PREFIX:-/opt/book/libs}"
printf 'jobs limit: %s\n' "${MAX_JOBS:-8}"
printf 'base:       %s\n' "$BASE_IMAGE"

for command_name in cmake ninja gcc g++ git python; do
  check_command "$command_name"
done

printf '\nTool versions\n'
cmake --version | head -n 1
ninja --version
gcc --version | head -n 1
python --version

printf '\nPython packages\n'
python - <<'PY'
import importlib
import sys

packages = {
    "yaml": "PyYAML",
    "typing_extensions": "typing_extensions",
    "optuna": "optuna",
    "torch": "torch",
    "transformers": "transformers",
    "mlflow": "mlflow",
}
for module_name, display_name in packages.items():
    module = importlib.import_module(module_name)
    print(f"ok   {display_name:16s} {getattr(module, '__version__', 'stdlib')}")
print(f"ok   Python           {sys.version.split()[0]}")
PY

printf '\nC++ headers\n'
for header in \
  arrayfire.h \
  blaze/Blaze.h \
  dlib/matrix.h \
  Eigen/Dense \
  armadillo \
  xtensor/xarray.hpp \
  nlohmann/json.hpp \
  highfive/H5File.hpp \
  httplib.h \
  flashlight/fl/flashlight.h \
  mlpack/core.hpp \
  tapkee/tapkee.hpp \
  onnxruntime_cxx_api.h; do
  if find "${BOOK_PREFIX:-/opt/book/libs}/include" -type f -path "*/$header" -print -quit | grep -q .; then
    printf 'ok   %s\n' "$header"
  else
    printf 'FAIL %s\n' "$header"
    failures=$((failures + 1))
  fi
done

for source_header in \
  sources/plotcpp/plot.h \
  sources/fast-cpp-csv-parser/csv.h; do
  if [[ -f "${BOOK_PREFIX:-/opt/book/libs}/$source_header" ]]; then
    printf 'ok   %s\n' "$source_header"
  else
    printf 'FAIL %s\n' "$source_header"
    failures=$((failures + 1))
  fi
done

torch_cmake="${BOOK_VENV:-/opt/book/venv}/lib/python3.10/site-packages/torch/share/cmake/Torch/TorchConfig.cmake"
if [[ -f "$torch_cmake" ]]; then
  printf 'ok   Torch CMake package %s\n' "$torch_cmake"
else
  printf 'FAIL Torch CMake package %s\n' "$torch_cmake"
  failures=$((failures + 1))
fi

if (( failures )); then
  printf '\nEnvironment verification failed: %d check(s).\n' "$failures" >&2
  exit 1
fi
printf '\nEnvironment verification passed.\n'
