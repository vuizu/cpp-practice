#include <cstdio>
#include <cuda_runtime_api.h>

__global__ void name_gpu() {
    printf("hello world\n");
}

int main() {

    name_gpu<<<2, 4>>>();
    cudaDeviceSynchronize();
}
