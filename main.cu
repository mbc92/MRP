#include <iostream>
#include "cudafunctions/benchmark.h"

#include <stdio.h>
#include <cstdlib>
#include <cuda_runtime.h>

__global__ void vecAdd(float *x, float *y, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    printf("hello CUDA wfwff \n");
    if (i < N) {
        x[i] = x[i] + y[i];
    }
}

int main() {
    printf("hello CUDA CPU \n");
    
    int N = 1<<20;
    float *x, *y, *d_x, *d_y;
    x = (float*)malloc(N*sizeof(float));
    y = (float*)malloc(N*sizeof(float));

    cudaMalloc(&d_x, N*sizeof(float)); 
    cudaMalloc(&d_y, N*sizeof(float));

    for (int i = 0; i < N; i++) {
      x[i] = 1.0f;
      y[i] = 2.0f;
    }

    cudaMemcpy(d_x, x, N*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, N*sizeof(float), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    vecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_x, d_y, N);

    cudaDeviceSynchronize();
    cudaMemcpy(x, d_x, N*sizeof(float), cudaMemcpyDeviceToHost);

    return 0;
}