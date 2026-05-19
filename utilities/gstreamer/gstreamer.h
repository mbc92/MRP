#pragma once

#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <memory>

// Wrapper class for GStreamer functionality
class Gstreamer
{
public:
    Gstreamer();
    ~Gstreamer();

private:

    std::unique_ptr<GstRTSPServer> _server;
    std::unique_ptr<GstRTSPMountPoints> _mounts;
    std::unique_ptr<GstRTSPMediaFactory> _factory;
};