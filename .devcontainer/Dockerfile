FROM soramaregistry.azurecr.io/jetson-nano-xilinx-sdk:latest AS listener-nano-sdk
FROM soramaregistry.azurecr.io/jetson-xavier-nx-xilinx-sdk:latest AS listener-xavier-sdk
 
FROM soramaregistry.azurecr.io/qtdevcontainerbaseimage:latest
 
# Cross compile toolchain for Listener nano
COPY --from=listener-nano-sdk /opt/sdk-jetson-nano-xilinx /opt/sdk-jetson-nano-xilinx
# Cross compile toolchain for Listener xavier
COPY --from=listener-xavier-sdk /opt/sdk-jetson-xavier-nx-xilinx /opt/sdk-jetson-xavier-nx-xilinx
 
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get update \
    && apt-get -y install --no-install-recommends \
        libprotobuf-dev \
        protobuf-compiler \
        libcairo2-dev \
        libjson-glib-dev \
        libsoup2.4-dev \
        sshpass \
        libxkbfile1
