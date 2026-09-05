# syntax=docker/dockerfile:1.7

# The multi-architecture manifest is pinned. Compose selects linux/amd64 for
# the current Quattro workstation.
FROM ubuntu:22.04@sha256:2edbbc5dc405e9612ba3584ce95480277e3eb374407b5505fe26f17df77c7dbc AS base

ARG CMAKE_VERSION=3.27.5
ARG CMAKE_SHA256=ac28060840a4a239b898cac7641cb54d5ca2065ec329338d6eb8a43f7471629b

ENV DEBIAN_FRONTEND=noninteractive \
    LANG=C.UTF-8 \
    LC_ALL=C.UTF-8 \
    TZ=UTC \
    BOOK_PREFIX=/opt/book/libs \
    BOOK_VENV=/opt/book/venv \
    MAX_JOBS=8 \
    PIP_DISABLE_PIP_VERSION_CHECK=1 \
    PIP_ROOT_USER_ACTION=ignore \
    PYTHONDONTWRITEBYTECODE=1

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN apt-get update \
    && apt-get install --no-install-recommends --yes \
      bash \
      build-essential \
      ca-certificates \
      cmake \
      curl \
      file \
      gdb \
      git \
      gnuplot \
      libatlas-base-dev \
      libblas-dev \
      libboost-all-dev \
      libcpuinfo-dev \
      libdouble-conversion-dev \
      libevent-dev \
      libfftw3-dev \
      libfmt-dev \
      libgflags-dev \
      libgoogle-glog-dev \
      libhdf5-dev \
      liblapack-dev \
      liblapacke-dev \
      liblzma-dev \
      libncurses-dev \
      libnuma-dev \
      libomp-dev \
      libopenblas-dev \
      libopencv-dev \
      libprotobuf-dev \
      libspdlog-dev \
      libsqlite3-dev \
      libssl-dev \
      libunwind-dev \
      libx11-dev \
      make \
      ninja-build \
      openjdk-17-jdk \
      pkg-config \
      protobuf-compiler \
      python3 \
      python3-dev \
      python3-pip \
      python3-venv \
      unzip \
      wget \
      zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

RUN curl --fail --location --silent --show-error \
      "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.sh" \
      --output /tmp/cmake-install.sh \
    && printf '%s  %s\n' "$CMAKE_SHA256" /tmp/cmake-install.sh | sha256sum --check --status - \
    && chmod 0555 /tmp/cmake-install.sh \
    && mkdir -p /opt/cmake \
    && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake \
    && rm -f /tmp/cmake-install.sh

COPY requirements-book.txt /tmp/requirements-book.txt

RUN python3 -m venv --copies /opt/book/venv \
    && /opt/book/venv/bin/python -m pip install --no-cache-dir \
      pip==24.0 setuptools==69.5.1 wheel==0.43.0 \
    && /opt/book/venv/bin/python -m pip install --no-cache-dir \
      --requirement /tmp/requirements-book.txt \
    && /opt/book/venv/bin/python -m pip install --no-cache-dir \
      --index-url https://download.pytorch.org/whl/cpu \
      "torch==2.3.1" \
    && rm -f /tmp/requirements-book.txt

COPY versions-book-baseline.env /opt/book/versions-book-baseline.env

ENV PATH=/opt/cmake/bin:/opt/book/venv/bin:/opt/book/libs/bin:${PATH} \
    CMAKE_PREFIX_PATH=/opt/book/libs \
    PKG_CONFIG_PATH=/opt/book/libs/lib/pkgconfig:/opt/book/libs/share/pkgconfig \
    LD_LIBRARY_PATH=/opt/book/libs/lib

FROM base AS cpp-builder

ARG MAX_JOBS=8
ENV MAX_JOBS=${MAX_JOBS}

COPY build-cpp.sh /usr/local/src/build-cpp.sh

RUN chmod 0555 /usr/local/src/build-cpp.sh \
    && /usr/local/src/build-cpp.sh \
    && rm -f /usr/local/src/build-cpp.sh

FROM base AS core

LABEL org.opencontainers.image.title="hands-on-machine-learning-with-cpp" \
      org.opencontainers.image.description="Pinned study environment for Hands-On Machine Learning with C++" \
      org.opencontainers.image.base.name="ubuntu:22.04"

COPY --from=cpp-builder /opt/book/libs /opt/book/libs
COPY book-entrypoint.sh /usr/local/bin/book-entrypoint.sh
COPY verify-env.sh /usr/local/bin/verify-env
COPY verify-book.sh /usr/local/bin/verify-book
COPY verify-gpu.sh /usr/local/bin/verify-gpu
COPY verify-android.sh /usr/local/bin/verify-android
COPY build-android-chapter.sh /usr/local/bin/build-android-chapter.sh

RUN site_packages="$(/opt/book/venv/bin/python -c 'import site; print(site.getsitepackages()[0])')" \
    && torch_config="$site_packages/torch/share/cmake/Torch/TorchConfig.cmake" \
    && test -f "$torch_config" \
    && mkdir -p /opt/book/libs/share/cmake/Torch /development \
    && printf 'include("%s")\n' "$torch_config" > /opt/book/libs/share/cmake/Torch/TorchConfig.cmake \
    && ln -s /opt/book/libs /development/libs \
    && printf '%s\n' /opt/book/libs/lib > /etc/ld.so.conf.d/book-libs.conf \
    && ldconfig \
    && mkdir -p /workspace/code /workspace/data /workspace/models /workspace/state /workspace/home \
    && groupadd --gid 1000 book \
    && useradd --uid 1000 --gid 1000 --no-create-home --home-dir /workspace/home --shell /bin/bash book \
    && chown -R 1000:1000 /workspace \
    && chmod 0555 /usr/local/bin/book-entrypoint.sh /usr/local/bin/verify-env /usr/local/bin/verify-book /usr/local/bin/verify-gpu /usr/local/bin/verify-android /usr/local/bin/build-android-chapter.sh

ENV HOME=/workspace/home \
    XDG_CACHE_HOME=/workspace/state/cache \
    XDG_CONFIG_HOME=/workspace/state/config \
    XDG_DATA_HOME=/workspace/state/data

USER 1000:1000
WORKDIR /workspace/code
ENTRYPOINT ["/usr/local/bin/book-entrypoint.sh"]
CMD ["shell"]

# Keep the author-tested CPU environment as the default. This optional target
# swaps only PyTorch for its matching CUDA 12.1 wheel so the host NVIDIA driver
# can accelerate compatible examples without changing the core image.
FROM core AS gpu

USER root
RUN /opt/book/venv/bin/python -m pip install --no-cache-dir --force-reinstall \
      --timeout 120 \
      --retries 10 \
      --extra-index-url https://download.pytorch.org/whl/cu121 \
      "torch==2.3.1+cu121"

USER 1000:1000
WORKDIR /workspace/code

# Android is deliberately a separate profile. It adds several hundred
# megabytes of SDK/NDK/OpenCV files to the image only when Chapter 14 is used.
FROM core AS android

USER root

ARG ANDROID_CMDLINE_TOOLS_VERSION=9477386
ARG ANDROID_CMDLINE_TOOLS_SHA1=7f92d6e0783a6d73ade5396fe4cfcb58544ef14b
ARG ANDROID_PLATFORM=35
ARG ANDROID_BUILD_TOOLS=35.0.0
ARG ANDROID_NDK=26.1.10909125
ARG ANDROID_CMAKE=3.22.1
ARG OPENCV_ANDROID_VERSION=4.10.0
ARG OPENCV_ANDROID_SHA256=464d55abe64b53af3aeb73197cf4620535abd909916d06e6a8b7c32712013966

ENV ANDROID_SDK_ROOT=/development/android \
    ANDROID_HOME=/development/android \
    JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64 \
    ANDROID_NDK_HOME=/development/android/ndk/26.1.10909125

RUN mkdir -p "$ANDROID_SDK_ROOT/cmdline-tools" /tmp/android-cmdline \
    && curl --fail --location --silent --show-error \
      "https://dl.google.com/android/repository/commandlinetools-linux-${ANDROID_CMDLINE_TOOLS_VERSION}_latest.zip" \
      --output /tmp/android-cmdline.zip \
    && printf '%s  %s\n' "$ANDROID_CMDLINE_TOOLS_SHA1" /tmp/android-cmdline.zip | sha1sum --check --status - \
    && unzip -q /tmp/android-cmdline.zip -d /tmp/android-cmdline \
    && mv /tmp/android-cmdline/cmdline-tools "$ANDROID_SDK_ROOT/cmdline-tools/latest" \
    && (set +o pipefail; yes | "$ANDROID_SDK_ROOT/cmdline-tools/latest/bin/sdkmanager" --sdk_root="$ANDROID_SDK_ROOT" --licenses >/dev/null) \
    && "$ANDROID_SDK_ROOT/cmdline-tools/latest/bin/sdkmanager" --sdk_root="$ANDROID_SDK_ROOT" \
      "platform-tools" \
      "platforms;android-34" \
      "platforms;android-${ANDROID_PLATFORM}" \
      "build-tools;34.0.0" \
      "build-tools;${ANDROID_BUILD_TOOLS}" \
      "ndk;${ANDROID_NDK}" \
      "cmake;${ANDROID_CMAKE}" \
    && rm -rf /tmp/android-cmdline /tmp/android-cmdline.zip \
    && curl --fail --location --silent --show-error \
      "https://github.com/opencv/opencv/releases/download/${OPENCV_ANDROID_VERSION}/opencv-${OPENCV_ANDROID_VERSION}-android-sdk.zip" \
      --output /tmp/opencv-android.zip \
    && printf '%s  %s\n' "$OPENCV_ANDROID_SHA256" /tmp/opencv-android.zip | sha256sum --check --status - \
    && mkdir -p /tmp/opencv-android \
    && unzip -q /tmp/opencv-android.zip -d /tmp/opencv-android \
    && test -d /tmp/opencv-android/OpenCV-android-sdk \
    && mv /tmp/opencv-android/OpenCV-android-sdk "$ANDROID_SDK_ROOT/OpenCV-android-sdk" \
    && rm -rf /tmp/opencv-android /tmp/opencv-android.zip \
    && chown -R 1000:1000 "$ANDROID_SDK_ROOT"

RUN source /opt/book/versions-book-baseline.env \
    && git clone --filter=blob:none --no-checkout --no-tags "$PYTORCH_REPOSITORY" /tmp/pytorch-android \
    && git -C /tmp/pytorch-android fetch --depth 1 origin "$PYTORCH_REF" \
    && git -C /tmp/pytorch-android checkout --detach FETCH_HEAD \
    && git -C /tmp/pytorch-android submodule sync --recursive \
    && git -C /tmp/pytorch-android submodule update --init --recursive --depth 1 \
    && site_packages="$(/opt/book/venv/bin/python -c 'import site; print(site.getsitepackages()[0])')" \
    && cd /tmp/pytorch-android \
    && ANDROID_NDK="$ANDROID_NDK_HOME" \
       ANDROID_ABI=arm64-v8a \
       ANDROID_STL_SHARED=1 \
       MAX_JOBS="$MAX_JOBS" \
       ./scripts/build_android.sh \
         -DBUILD_SHARED_LIBS=ON \
         -DUSE_VULKAN=OFF \
         -DCMAKE_PREFIX_PATH="$site_packages" \
         -DPYTHON_EXECUTABLE=/opt/book/venv/bin/python \
    && mkdir -p "$ANDROID_SDK_ROOT/pytorch/build_android" \
    && mv /tmp/pytorch-android/build_android/install "$ANDROID_SDK_ROOT/pytorch/build_android/install" \
    && cd / \
    && rm -rf /tmp/pytorch-android \
    && chown -R 1000:1000 "$ANDROID_SDK_ROOT/pytorch"

COPY requirements-yolov5.txt /tmp/requirements-yolov5.txt

RUN source /opt/book/versions-book-baseline.env \
    && git clone --filter=blob:none --no-checkout --no-tags "$YOLOV5_REPOSITORY" /opt/yolov5 \
    && git -C /opt/yolov5 fetch --depth 1 origin "$YOLOV5_REF" \
    && git -C /opt/yolov5 checkout --detach FETCH_HEAD \
    && /opt/book/venv/bin/python -m pip install --no-cache-dir \
      --index-url https://download.pytorch.org/whl/cpu \
      "torchvision==0.18.1" \
    && /opt/book/venv/bin/python -m pip install --no-cache-dir \
      --constraint /tmp/requirements-yolov5.txt \
      --requirement /opt/yolov5/requirements.txt \
    && /opt/book/venv/bin/python -m pip check \
    && /opt/book/venv/bin/python -c \
      'import cv2, mlflow, numpy, pandas, pyarrow, tensorboard' \
    && rm -f /tmp/requirements-yolov5.txt \
    && rm -rf /opt/yolov5/.git

USER 1000:1000
WORKDIR /workspace/code
