#include "benchmark.h"
#include "kernels/benchmark.cuh"
#include <stdio.h>
#include <cstdlib>

Benchmark::Benchmark(const uint32_t size)
:dataSize(size)
{};

void Benchmark::memCopyDefault()
{
    ExecuteMemCopyDefault();
}

