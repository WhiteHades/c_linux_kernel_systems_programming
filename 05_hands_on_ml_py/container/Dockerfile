# syntax=docker/dockerfile:1.7

ARG PYTHON_IMAGE=python:3.9.25-slim-bookworm@sha256:a02e9c5406c416c504d6c9a1a306ff4080c3173f1008d192f953bd20382a2d5c

FROM ${PYTHON_IMAGE} AS core

ARG USER_ID=1000
ARG GROUP_ID=1000

ENV DEBIAN_FRONTEND=noninteractive \
    HOME=/workspace/state/home \
    MPLCONFIGDIR=/workspace/state/matplotlib \
    PIP_CACHE_DIR=/workspace/state/pip-cache \
    PYTHONUNBUFFERED=1 \
    PYTHONDONTWRITEBYTECODE=1

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        curl \
        ffmpeg \
        git \
        graphviz \
        libgl1 \
        libglib2.0-0 \
        libgomp1 \
        libsm6 \
        libxext6 \
        libxrender1 \
        tini \
        xauth \
        xvfb \
    && rm -rf /var/lib/apt/lists/*

COPY requirements-core.txt /tmp/requirements-core.txt
RUN python -m pip install --no-cache-dir \
        pip==23.3.2 setuptools==59.5.0 wheel==0.45.1 \
    && python -m pip install --no-cache-dir -r /tmp/requirements-core.txt \
    && python -m pip check

RUN groupadd --gid "$GROUP_ID" book \
    && useradd --uid "$USER_ID" --gid "$GROUP_ID" --create-home --home-dir /home/book book \
    && install -d -o "$USER_ID" -g "$GROUP_ID" \
        /opt/book/bin \
        /workspace/state/home \
        /workspace/state/matplotlib \
        /workspace/state/pip-cache \
        /workspace/study

COPY --chmod=755 entrypoint.sh verify-env.sh /opt/book/bin/

USER book
WORKDIR /workspace/study
ENV BOOK_PROFILE=core
ENTRYPOINT ["/usr/bin/tini", "--", "/opt/book/bin/entrypoint.sh"]
CMD ["shell"]

FROM core AS torch

USER root
RUN python -m pip install --no-cache-dir \
        torch==1.9.0+cpu \
        torchvision==0.10.0+cpu \
        -f https://download.pytorch.org/whl/torch_stable.html
COPY requirements-torch.txt /tmp/requirements-torch.txt
RUN python -m pip install --no-cache-dir -r /tmp/requirements-torch.txt \
    && python -m pip check
USER book
ENV BOOK_PROFILE=torch

FROM torch AS gnn

USER root
RUN python -m pip install --no-cache-dir \
        torch-scatter==2.0.9 \
        torch-sparse==0.6.12 \
        -f https://data.pyg.org/whl/torch-1.9.0+cpu.html
COPY requirements-gnn.txt /tmp/requirements-gnn.txt
RUN python -m pip install --no-cache-dir -r /tmp/requirements-gnn.txt \
    && python -m pip check
USER book
ENV BOOK_PROFILE=gnn

FROM torch AS rl

USER root
COPY requirements-rl.txt /tmp/requirements-rl.txt
RUN python -m pip install --no-cache-dir wheel==0.38.4 \
    && python -m pip install --no-cache-dir -r /tmp/requirements-rl.txt \
    && python -m pip check
USER book
ENV BOOK_PROFILE=rl

FROM torch AS gpu

USER root
RUN python -m pip install --no-cache-dir --force-reinstall --no-deps \
        torch==1.9.0+cu111 \
        torchvision==0.10.0+cu111 \
        -f https://download.pytorch.org/whl/torch_stable.html \
    && python -m pip check
USER book
ENV BOOK_PROFILE=gpu
