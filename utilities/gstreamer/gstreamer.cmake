find_package(PkgConfig REQUIRED)

pkg_check_modules(GST REQUIRED
    gstreamer-1.0
    gstreamer-app-1.0
)

pkg_check_modules(RTSP REQUIRED gstreamer-rtsp-server-1.0)

add_library(GStreamer::GStreamer INTERFACE IMPORTED)

set_target_properties(GStreamer::GStreamer PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GST_INCLUDE_DIRS};${RTSP_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${GST_LIBRARIES};${RTSP_LIBRARIES}"
)
