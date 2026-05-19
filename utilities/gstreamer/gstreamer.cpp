#include "gstreamer.h"

// GStreamer implementation
// Add your GStreamer functionality here

Gstreamer::Gstreamer()
    :_server(std::make_unique<GstRTSPServer>()),
     _mounts(gst_rtsp_server_get_mount_points(_server.get())),
     _factory(gst_rtsp_media_factory_new())
{
    
}

Gstreamer::~Gstreamer()
{
    // Destructor implementation
}

