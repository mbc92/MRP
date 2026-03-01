#include <iostream>
#include "V4LSource.h"
#include "MockSource.h"
#include "FileSource.h"
#include "DataSourceBase.h"


int main() {
    const uint32_t videoWidth = 640;
    const uint32_t videoHeight = 480;
    const std::string cameraPath{"/dev/video0"};
    std::vector<uint8_t> cameraBuffer;

    V4LSource camera(cameraPath, videoWidth, videoHeight);

    camera.configure();

    std::cout << "Starting MRP compute" << std::endl;

    while(1)
    {
        camera.read(cameraBuffer);
    }

    return 0;
}