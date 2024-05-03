//
// Created by dbj on 24-5-3.
//

#include "UDMCudaContext.cuh"

#include "cuda_runtime.h"

__host__ void cu_calloc_dev(void *ptr_d, int aligned_size, uint64_t nelem, uint64_t size) {
    uint64_t total_length = (nelem / aligned_size + 1) * aligned_size * size;
    cudaError err = cudaMalloc(&ptr_d, total_length);
};