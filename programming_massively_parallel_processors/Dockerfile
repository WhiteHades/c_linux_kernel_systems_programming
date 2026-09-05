FROM nvidia/cuda:13.3.1-devel-ubuntu24.04@sha256:4ff859525f99de5782aa73607ce24219b07dddd48d12b97c1c301d7e1cfb0a87
RUN sed -i 's|http://|https://|g' /etc/apt/sources.list.d/ubuntu.sources \
    && apt-get update && apt-get install -y --no-install-recommends make libopenmpi-dev openmpi-bin \
    && rm -rf /var/lib/apt/lists/*
COPY verify.cu /opt/verify.cu
RUN nvcc -arch=sm_75 -std=c++17 /opt/verify.cu -o /opt/verify-cuda
WORKDIR /workspace
