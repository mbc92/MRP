#pragma once
#include <stdint.h>
class benchmark{

    public:

    benchmark(const uint32_t size);
    void memCopyDefault();
    void memCopyAsync();
    void managedMemory();
    void mappedMemory();

    private:
    const uint32_t dataSize = 0;

};