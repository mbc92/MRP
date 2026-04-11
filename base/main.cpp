#include <iostream>
#include "benchmark.h"


int main() {
    
    benchmark bench(100);

    bench.memCopyDefault();
    return 0;
}