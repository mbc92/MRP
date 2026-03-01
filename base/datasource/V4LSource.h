#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <memory>
#include <functional>
#include "DataSourceBase.h"

class V4LSource : public DataSource<V4LSource>
{
public:
explicit V4LSource(
    std::string v4lPath, 
    const uint32_t videoWidth, 
    const uint32_t videoHeight)
    : devicePath(std::move(v4lPath)),
      width(videoWidth),
      height(videoHeight)
    {
        fd = open(devicePath.c_str(), O_RDWR);
        if (fd < 0)
            throw std::runtime_error("Failed to open device");
    }

    ~V4LSource()
    {
        std::cout << "Destroying V4LSource" << std::endl;
        if (fd >= 0)
            close(fd);
    }

    bool configureImpl()
    {
        configureFormat(width, height);
        requestAndMapBuffer();
        startStreaming();
        streaming = true;
        return true;
    }

    void readImpl(std::vector<uint8_t>& buffer)
    {
        if (!streaming) throw std::runtime_error("Camera not started");

        v4l2_buffer buf{};
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;

        if (ioctl(fd, VIDIOC_DQBUF, &buf) < 0) throw std::runtime_error("DQBUF failed");

        buffer.assign(mappedBuffer.get(), mappedBuffer.get() + buf.bytesused);

        ioctl(fd, VIDIOC_QBUF, &buf);
    }

    void closeImpl()
    {
        std::cout << "Closing USB camera\n";
    }

private:
    int fd{-1};
    std::unique_ptr<uint8_t, std::function<void(uint8_t*)>> mappedBuffer;
    size_t bufferLength{0};
    bool streaming{false};
    const std::string devicePath;
    const uint32_t width{0};
    const uint32_t height{0};

    void configureFormat(const uint32_t width, const uint32_t height)
    {
        v4l2_format fmt{};
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = width;
        fmt.fmt.pix.height = height;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        fmt.fmt.pix.field = V4L2_FIELD_NONE;

        if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0)
            throw std::runtime_error("VIDIOC_S_FMT failed");
    }


    void requestAndMapBuffer()
    {
        // Request buffer
        v4l2_requestbuffers req{};
        req.count = 1;
        req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        req.memory = V4L2_MEMORY_MMAP;
        if (ioctl(fd, VIDIOC_REQBUFS, &req) < 0)
            throw std::runtime_error("REQBUFS failed");

        v4l2_buffer buf{};
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = 0;

        if (ioctl(fd, VIDIOC_QUERYBUF, &buf) < 0)
            throw std::runtime_error("QUERYBUF failed");

        void* raw = mmap(nullptr, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        if (raw == MAP_FAILED) 
            throw std::runtime_error("mmap failed");

        // Wrap in unique_ptr with lambda deleter
        mappedBuffer = std::unique_ptr<uint8_t, std::function<void(uint8_t*)>>(
            static_cast<uint8_t*>(raw),
            [len = buf.length](uint8_t* p) {
                if (p) munmap(p, len);
            }
        );

        // Queue buffer
        if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)
            throw std::runtime_error("QBUF failed");
    }

    void startStreaming()
    {
        v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (ioctl(fd, VIDIOC_STREAMON, &type) < 0)
            throw std::runtime_error("STREAMON failed");
    }
};