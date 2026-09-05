#!/usr/bin/env bash
set -Eeuo pipefail

# Build the C++ dependencies used by the book. This script runs only in the
# image builder stage. Runtime containers never have a compiler or git source
# tree outside the image's read-only dependency prefix.

readonly PREFIX=/opt/book/libs
readonly SOURCE_ROOT=/tmp/book-sources
readonly BUILD_ROOT=/tmp/book-builds
readonly LOCK_FILE="$PREFIX/share/book/dependency-commits.txt"

jobs="${MAX_JOBS:-8}"
if ! [[ "$jobs" =~ ^[0-9]+$ ]] || (( jobs < 1 )); then
  jobs=1
elif (( jobs > 8 )); then
  jobs=8
fi

mkdir -p "$PREFIX" "$SOURCE_ROOT" "$BUILD_ROOT" "$(dirname "$LOCK_FILE")"
: >"$LOCK_FILE"

source /opt/book/versions-book-baseline.env

log() {
  printf '\n==> %s\n' "$*"
}

source_name() {
  local repository="$1"
  repository="${repository##*/}"
  printf '%s' "${repository%.git}"
}

clone_at() {
  local name="$1"
  local repository="$2"
  local ref="$3"
  local destination="$SOURCE_ROOT/$name"

  if [[ -d "$destination/.git" ]]; then
    git -C "$destination" fetch --depth 1 origin "$ref"
  else
    rm -rf "$destination"
    git clone --filter=blob:none --no-checkout --no-tags "$repository" "$destination"
    git -C "$destination" fetch --depth 1 origin "$ref"
  fi

  git -C "$destination" checkout --detach FETCH_HEAD

  if [[ -f "$destination/.gitmodules" ]]; then
    sed -i 's#git://#https://#g' "$destination/.gitmodules"
    git -C "$destination" submodule sync --recursive
    git -C "$destination" -c protocol.file.allow=never submodule update --init --recursive
  fi

  printf '%s\t%s\t%s\n' "$name" "$ref" "$(git -C "$destination" rev-parse HEAD)" >>"$LOCK_FILE"
}

cmake_install() {
  local name="$1"
  local repository="$2"
  local ref="$3"
  shift 3
  local source="$SOURCE_ROOT/$name"
  local build="$BUILD_ROOT/$name"

  log "Building $name ($ref)"
  clone_at "$name" "$repository" "$ref"
  rm -rf "$build"
  cmake -S "$source" -B "$build" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="$PREFIX" \
    -DCMAKE_INSTALL_LIBDIR=lib \
    -DCMAKE_INSTALL_RPATH="$PREFIX/lib" \
    -DCMAKE_PREFIX_PATH="$PREFIX" \
    "$@"
  cmake --build "$build" --parallel "$jobs"
  cmake --install "$build"
  rm -rf "$build"
}

checkout_source() {
  local name="$1"
  local repository="$2"
  local ref="$3"

  log "Checking out $name ($ref)"
  clone_at "$name" "$repository" "$ref"
}

install_onnxruntime() {
  local archive=/tmp/onnxruntime.tgz
  local source=/tmp/onnxruntime

  log "Installing onnxruntime ($ONNXRUNTIME_VERSION)"
  curl --fail --location --silent --show-error "$ONNXRUNTIME_URL" --output "$archive"
  printf '%s  %s\n' "$ONNXRUNTIME_SHA256" "$archive" | sha256sum --check --status -
  rm -rf "$source"
  mkdir -p "$source" "$PREFIX/share/licenses/onnxruntime"
  tar --extract --gzip --file "$archive" --directory "$source" --strip-components=1
  [[ "$(<"$source/VERSION_NUMBER")" == "$ONNXRUNTIME_VERSION" ]]
  [[ "$(<"$source/GIT_COMMIT_ID")" == "$ONNXRUNTIME_COMMIT" ]]
  cp -a "$source/include/." "$PREFIX/include/"
  cp -a "$source/lib/." "$PREFIX/lib/"
  cp "$source/LICENSE" "$source/Privacy.md" "$source/ThirdPartyNotices.txt" \
    "$PREFIX/share/licenses/onnxruntime/"
  printf '%s\t%s\t%s\n' onnxruntime "$ONNXRUNTIME_VERSION" "$ONNXRUNTIME_COMMIT" >>"$LOCK_FILE"
  rm -rf "$source" "$archive"
}

# The order follows the book's dependency order. ArrayFire must precede
# Flashlight, and ONNX Runtime must precede any future LibTorch source build.
cmake_install blaze "$BLAZE_REPOSITORY" "$BLAZE_REF"
cmake_install span-lite "$SPAN_LITE_REPOSITORY" "$SPAN_LITE_REF" \
  -DSPAN_LITE_OPT_BUILD_TESTS=OFF \
  -DSPAN_LITE_OPT_BUILD_EXAMPLES=OFF \
  -DSPAN_LITE_EXPORT_PACKAGE=OFF
cmake_install arrayfire "$ARRAYFIRE_REPOSITORY" "$ARRAYFIRE_REF" \
  -DBUILD_TESTS=OFF \
  -DBUILD_TESTING=OFF \
  -DAF_BUILD_EXAMPLES=OFF \
  -DAF_BUILD_CPU=ON \
  -DAF_BUILD_CUDA=OFF \
  -DAF_BUILD_OPENCL=OFF \
  -DAF_BUILD_UNIFIED=OFF
cmake_install flashlight "$FLASHLIGHT_REPOSITORY" "$FLASHLIGHT_REF" \
  -DFL_BUILD_TESTS=OFF \
  -DFL_BUILD_EXAMPLES=OFF \
  -DFL_LIBRARIES_USE_MKL=OFF \
  -DFL_USE_CPU=ON \
  -DFL_USE_ONEDNN=OFF \
  -DArrayFire_DIR="$PREFIX/share/ArrayFire/cmake" \
  -DFL_ARRAYFIRE_USE_CPU=ON \
  -DFL_BUILD_DISTRIBUTED=OFF
cmake_install dlib "$DLIB_REPOSITORY" "$DLIB_REF" \
  -DDLIB_USE_CUDA=OFF
cmake_install armadillo-code "$ARMADILLO_REPOSITORY" "$ARMADILLO_REF" \
  -DDETECT_HDF5=ON
cmake_install xtl "$XTL_REPOSITORY" "$XTL_REF"
cmake_install xtensor "$XTENSOR_REPOSITORY" "$XTENSOR_REF"
cmake_install xtensor-blas "$XTENSOR_BLAS_REPOSITORY" "$XTENSOR_BLAS_REF"
cmake_install nlohmann-json "$NLOHMANN_JSON_REPOSITORY" "$NLOHMANN_JSON_REF" \
  -DJSON_BuildTests=OFF
cmake_install mlpack "$MLPACK_REPOSITORY" "$MLPACK_REF" \
  -DBUILD_PYTHON_BINDINGS=OFF \
  -DBUILD_CLI_EXECUTABLES=OFF \
  -DBUILD_TESTS=OFF \
  -DDOWNLOAD_DEPENDENCIES=ON
cmake_install eigen "$EIGEN_REPOSITORY" "$EIGEN_REF"
cmake_install HighFive "$HIGHFIVE_REPOSITORY" "$HIGHFIVE_REF" \
  -DHIGHFIVE_UNIT_TESTS=OFF \
  -DHIGHFIVE_EXAMPLES=OFF \
  -DHIGHFIVE_BUILD_DOCS=OFF
cmake_install cpp-httplib "$CPP_HTTPLIB_REPOSITORY" "$CPP_HTTPLIB_REF" \
  -DHTTPLIB_BUILD_TESTS=OFF
checkout_source plotcpp "$PLOTCPP_REPOSITORY" "$PLOTCPP_REF"
checkout_source fast-cpp-csv-parser "$FAST_CPP_CSV_REPOSITORY" "$FAST_CPP_CSV_REF"
cmake_install tapkee "$TAPKEE_REPOSITORY" "$TAPKEE_REF" \
  -DBUILD_TESTS=OFF
install_onnxruntime

# The two header-only checkouts are referenced directly by the upstream
# chapter build scripts. Keep only those source trees and strip their git
# metadata from the runtime image.
mkdir -p "$PREFIX/sources"
cp -a "$SOURCE_ROOT/plotcpp" "$PREFIX/sources/plotcpp"
cp -a "$SOURCE_ROOT/fast-cpp-csv-parser" "$PREFIX/sources/fast-cpp-csv-parser"
rm -rf "$PREFIX/sources/plotcpp/.git" "$PREFIX/sources/fast-cpp-csv-parser/.git"

printf '\nDependency commits:\n'
cat "$LOCK_FILE"
