#!/usr/bin/env bash
set -Eeuo pipefail

source /opt/book/versions-book-baseline.env

readonly project=/workspace/code/Chapter14/android_detection
readonly pytorch=/development/android/pytorch/build_android/install
readonly models=/workspace/models
readonly weights="$models/yolov5s.pt"
readonly torchscript="$models/yolov5s.torchscript"

[[ -x "$project/gradlew" ]] || {
  printf 'Android project is missing: %s\n' "$project" >&2
  exit 1
}

mkdir -p "$models" "$project/app/src/main/assets" "$project/app/src/main/jniLibs/arm64-v8a"

if [[ ! -f "$weights" ]]; then
  printf 'Downloading the pinned YOLOv5s v7.0 weights.\n'
  curl --fail --location --silent --show-error "$YOLOV5_WEIGHTS_URL" --output "$weights.part"
  printf '%s  %s\n' "$YOLOV5_WEIGHTS_SHA256" "$weights.part" | sha256sum --check --status -
  mv "$weights.part" "$weights"
fi

printf '%s  %s\n' "$YOLOV5_WEIGHTS_SHA256" "$weights" | sha256sum --check --status -

if [[ ! -f "$torchscript" ]]; then
  printf 'Exporting YOLOv5s for the PyTorch mobile runtime.\n'
  cd /opt/yolov5
  python export.py --weights "$weights" --include torchscript --optimize --device cpu
fi

install -m 0644 "$torchscript" "$project/app/src/main/assets/yolov5s.torchscript"
find "$pytorch/lib" -maxdepth 1 -type f -name '*.so' -exec \
  install -m 0644 {} "$project/app/src/main/jniLibs/arm64-v8a/" \;

cd "$project"
./gradlew --no-daemon assembleDebug

apk="$project/app/build/outputs/apk/debug/app-debug.apk"
[[ -f "$apk" ]] || {
  printf 'Gradle completed but the APK is missing: %s\n' "$apk" >&2
  exit 1
}
printf 'APK: %s\n' "$apk"
