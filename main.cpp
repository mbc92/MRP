#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <gstreamer.h>

int main(int argc, char *argv[])
{
    Gstreamer stream(8554);
    stream.StartRTSPStream();
    stream.RunMainLoop();

    return 0;
}