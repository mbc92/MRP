#include "gstreamer.h"
#include <string>
// GStreamer implementation
// Add your GStreamer functionality here

Gstreamer::Gstreamer(const uint16_t port)
    :_port(port),
     _server(gst_rtsp_server_new()),
     _factory(gst_rtsp_media_factory_new()),
     _pipeline(nullptr)
{
}

Gstreamer::~Gstreamer()
{
    if (_server) g_object_unref(_server.get());
    if (_factory) g_object_unref(_factory.get());
    if (_mounts) g_object_unref(_mounts.get());
}

void Gstreamer::StartRTSPStream()
{
    gst_init(NULL, NULL);

    _mounts = std::make_unique<GstRTSPMountPoints>(*gst_rtsp_server_get_mount_points(_server.get()));

    gst_rtsp_server_set_service(_server.get(), std::to_string(_port).c_str());
    gst_rtsp_media_factory_set_shared(_factory.get(), TRUE);

    gst_rtsp_media_factory_set_launch(_factory.get(),
        "( nvarguscamerasrc sensor-id=0 ! "
        "video/x-raw(memory:NVMM),width=1920,height=1080,framerate=30/1 ! "
        "tee name=t ! "
        "queue ! nvv4l2h264enc ! rtph264pay bitrate=4000000 insert-sps-pps=1 iframeinterval=30 name=pay0 pt=96 "
        "t. ! queue ! appsink name=sink sync=false )");

    gst_rtsp_mount_points_add_factory(_mounts.get(), "/webcam", _factory.get());
    g_object_unref(_mounts.get());

    gst_rtsp_server_attach(_server.get(), NULL);

    g_print("RTSP ready: rtsp://<jetson-ip>:%d/webcam\n", _port);
}

void Gstreamer::RunMainLoop()
{
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);
}

