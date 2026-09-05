FROM eclipse-temurin:26-jdk@sha256:6ed484c3607a9ad524689b0ece7e6a7c0b929f408d05ba4651c475a2cdb20bc8 AS jdk

FROM gcc:16@sha256:213a0e383dc1429862a8f12624dfe8fb43339bc808a79f4e578529e4903b3054

COPY --from=jdk /opt/java/openjdk /opt/java/openjdk

ENV JAVA_HOME=/opt/java/openjdk
ENV PATH=${JAVA_HOME}/bin:/opt/dart/dart-sdk/bin:${PATH}

RUN apt-get update \
    && apt-get install --no-install-recommends --yes ca-certificates ccache curl make unzip \
    && rm -rf /var/lib/apt/lists/*

ARG DART_VERSION=2.19.6
ARG DART_SHA256=0fdff25e6acba3d6094155a7e341634f8de3477e86c2fda4ad47232c1adf704f
RUN curl --fail --location --retry 3 \
      "https://storage.googleapis.com/dart-archive/channels/stable/release/${DART_VERSION}/sdk/dartsdk-linux-x64-release.zip" \
      --output /tmp/dart-sdk.zip \
    && echo "${DART_SHA256}  /tmp/dart-sdk.zip" | sha256sum --check --status \
    && mkdir -p /opt/dart \
    && unzip -q /tmp/dart-sdk.zip -d /opt/dart \
    && rm /tmp/dart-sdk.zip

ENV PUB_CACHE=/opt/dart-pub-cache
COPY code/tool /opt/crafting-tool/tool
RUN cd /opt/crafting-tool/tool && dart pub get

ENV LANG=C.UTF-8 LC_ALL=C.UTF-8

WORKDIR /workspace
