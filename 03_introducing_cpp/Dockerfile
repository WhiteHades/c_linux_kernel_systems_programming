FROM gcc:16@sha256:213a0e383dc1429862a8f12624dfe8fb43339bc808a79f4e578529e4903b3054

RUN apt-get update \
    && apt-get install --no-install-recommends --yes ca-certificates ccache gdb make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
