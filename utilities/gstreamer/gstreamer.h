#pragma once

#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <memory>
#include <functional>

// Wrapper class for GStreamer functionality
class Gstreamer
{
public:
    Gstreamer(const uint16_t port);
    ~Gstreamer();

    void StartRTSPStream();
    void RunMainLoop();

private:
    const uint16_t _port{0u};
    std::unique_ptr<GstElement> _pipeline;

    std::unique_ptr<GstRTSPServer> _server;
    std::unique_ptr<GstRTSPMountPoints> _mounts;
    std::unique_ptr<GstRTSPMediaFactory> _factory;
};