#!/usr/bin/env bash
set -Eeuo pipefail

source /opt/book/versions-book-baseline.env

sdkmanager_bin="${ANDROID_SDK_ROOT:-/development/android}/cmdline-tools/latest/bin/sdkmanager"
if [[ ! -x "$sdkmanager_bin" ]]; then
  printf 'Android SDK command-line tools are missing. Use the android Compose profile.\n' >&2
  exit 1
fi

printf 'Android SDK: %s\n' "${ANDROID_SDK_ROOT:-/development/android}"
"$sdkmanager_bin" --version

for path in \
  "${ANDROID_SDK_ROOT:-/development/android}/platforms/android-34" \
  "${ANDROID_SDK_ROOT:-/development/android}/platforms/android-${ANDROID_PLATFORM}" \
  "${ANDROID_SDK_ROOT:-/development/android}/build-tools/34.0.0" \
  "${ANDROID_SDK_ROOT:-/development/android}/build-tools/${ANDROID_BUILD_TOOLS}" \
  "${ANDROID_SDK_ROOT:-/development/android}/ndk/${ANDROID_NDK}" \
  "${ANDROID_SDK_ROOT:-/development/android}/cmake/${ANDROID_CMAKE}"; do
  if [[ -e "$path" ]]; then
    printf 'ok   %s\n' "$path"
  else
    printf 'FAIL %s\n' "$path" >&2
    exit 1
  fi
done

opencv_dir="${ANDROID_SDK_ROOT:-/development/android}/OpenCV-android-sdk/sdk"
if [[ -d "$opencv_dir" ]]; then
  printf 'ok   OpenCV Android %s\n' "$OPENCV_ANDROID_VERSION"
else
  printf 'FAIL OpenCV Android SDK %s\n' "$opencv_dir" >&2
  exit 1
fi

pytorch_dir="${ANDROID_SDK_ROOT:-/development/android}/pytorch/build_android/install"
for path in \
  "$pytorch_dir/include" \
  "$pytorch_dir/lib/libc10.so" \
  "$pytorch_dir/lib/libtorch.so" \
  "$pytorch_dir/lib/libtorch_cpu.so"; do
  if [[ -e "$path" ]]; then
    printf 'ok   %s\n' "$path"
  else
    printf 'FAIL %s\n' "$path" >&2
    exit 1
  fi
done

printf 'Android environment verification passed.\n'
