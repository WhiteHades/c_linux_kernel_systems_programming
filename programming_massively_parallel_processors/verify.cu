#include <cuda_runtime.h>
#include <cstdio>

__global__ void probe(int *result) { *result = 37; }

int main() {
    int count = 0;
    cudaError_t status = cudaGetDeviceCount(&count);
    if (status != cudaSuccess || count < 1) {
        std::fprintf(stderr, "CUDA device unavailable: %s\n", cudaGetErrorString(status));
        return 1;
    }
    int *device = nullptr;
    int result = 0;
    if (cudaMalloc(&device, sizeof(int)) != cudaSuccess) return 1;
    probe<<<1, 1>>>(device);
    status = cudaGetLastError();
    if (status == cudaSuccess) status = cudaDeviceSynchronize();
    if (status == cudaSuccess) status = cudaMemcpy(&result, device, sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(device);
    if (status != cudaSuccess || result != 37) return 1;
    std::puts("CUDA compilation, kernel execution, and device copy passed.");
}
