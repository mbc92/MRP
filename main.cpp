#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    GstRTSPServer *server = gst_rtsp_server_new();
    gst_rtsp_server_set_service(server, "8554");

    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();

    gst_rtsp_media_factory_set_shared(factory, TRUE);
    gst_rtsp_media_factory_set_latency(factory, 30);

    gst_rtsp_media_factory_set_launch(factory,
        "( "
        "v4l2src device=/dev/video0 do-timestamp=true is-live=true ! "
        "image/jpeg,width=1920,height=1080,framerate=30/1 ! "
    
        /* Split COMPRESSED stream */
        "tee name=t "
    
        /* RTSP branch (unchanged, still MJPEG) */
        "t. ! queue leaky=downstream max-size-buffers=1 ! "
        "rtpjpegpay name=pay0 pt=26 config-interval=1 "
    
        /* NVMM branch (decode separately) */
        "t. ! queue ! "
        "jpegdec ! "
        "nvvidconv ! video/x-raw(memory:NVMM),format=NV12 ! "
        "fakesink sync=false "
        ")"
    );

    gst_rtsp_mount_points_add_factory(mounts, "/webcam", factory);
    g_object_unref(mounts);

    gst_rtsp_server_attach(server, NULL);

    g_print("LOW LATENCY RTSP: rtsp://192.168.178.66:8554/webcam\n");

    g_main_loop_run(g_main_loop_new(NULL, FALSE));

    return 0;
}