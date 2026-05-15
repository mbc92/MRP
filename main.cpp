#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

int main(int argc, char *argv[])
{
    gst_init(&argc, &argv);

    GstRTSPServer *server = gst_rtsp_server_new();
    gst_rtsp_server_set_service(server, "8554");

    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();

    gst_rtsp_media_factory_set_shared(factory, TRUE);

    gst_rtsp_media_factory_set_launch(factory,
        "( "
        "nvarguscamerasrc sensor-id=0 ! "
        "video/x-raw(memory:NVMM),width=1920,height=1080,framerate=30/1 ! "
        "nvv4l2h264enc bitrate=4000000 insert-sps-pps=1 iframeinterval=30 ! "
        "rtph264pay name=pay0 pt=96 config-interval=1 "
        ")"
    );

    gst_rtsp_mount_points_add_factory(mounts, "/webcam", factory);
    g_object_unref(mounts);

    gst_rtsp_server_attach(server, NULL);

    g_print("RTSP ready: rtsp://<jetson-ip>:8554/webcam\n");

    g_main_loop_run(g_main_loop_new(NULL, FALSE));

    return 0;
}