FROM ubuntu:20.04

# Set up non-interactive installation environment
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies and tools (e.g., build-essential, CMake, etc.)
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    python3 \
    file \
    gdb-multiarch \
    xz-utils \
    tar \
    locales \
    wget \
    curl \
    gnupg2 \
    lsb-release \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-ubuntu1804.pin && \
    mv cuda-ubuntu1804.pin /etc/apt/preferences.d/cuda-repository-pin-600

RUN wget https://developer.download.nvidia.com/compute/cuda/10.2/Prod/local_installers/cuda-repo-ubuntu1804-10-2-local-10.2.89-440.33.01_1.0-1_amd64.deb && \
    dpkg -i cuda-repo-ubuntu1804-10-2-local-10.2.89-440.33.01_1.0-1_amd64.deb

RUN apt-key add /var/cuda-repo-10-2-local-10.2.89-440.33.01/7fa2af80.pub && \
    apt-get update && \
    apt-get install -y cuda && \
    rm -rf /var/lib/apt/lists/*

# Copy Yocto SDK installer
COPY sdk/oecore-x86_64-armv8a-toolchain-nodistro.0.sh /tmp/sdk.sh

# Install Yocto SDK
RUN chmod +x /tmp/sdk.sh && \
    /tmp/sdk.sh -d /opt/yocto-sdk -y && \
    rm /tmp/sdk.sh

# Auto-load SDK environment (this ensures Yocto toolchain is available in every new terminal)
RUN echo "source /opt/yocto-sdk/environment-setup-armv8a-oe-linux" >> /root/.bashrc

# Ensure environment variables for Yocto SDK are loaded on each container start
ENV PATH=/opt/yocto-sdk/sysroots/x86_64-oesdk-linux/usr/bin:$PATH

# Clean up any remaining cache from package installations
RUN rm -rf /var/lib/apt/lists/*

# Set default entrypoint to bash
CMD ["/bin/bash"]