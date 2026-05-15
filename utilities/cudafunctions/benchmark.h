#pragma once
#include <stdint.h>

class Benchmark{

public:
    Benchmark(const uint32_t size);
    void memCopyDefault();
    void memCopyAsync();
    void managedMemory();
    void mappedMemory();

private:
    const uint32_t dataSize = 0;

};