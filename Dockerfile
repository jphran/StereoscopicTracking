# native on xavier nx is zed 3.2, python 3.6, pyzed 3.2, ipjetpack 4.4, cuda 10.2
FROM stereolabs/zed:3.3-devel-jetson-jp4.4
LABEL maintainer="Justin Francis <j.francis@sarcos.com>"
LABEL version="0.1"

USER root

WORKDIR /home/
exit
RUN apt-get update \
    && apt-get autoremove -y \
    && apt-get install -y --no-install-recommends \
        git \
        vim \
        build-essential \
        cmake \
        glew-utils \
#        nmap \
#        net-tools \
    && git clone https://github.com/stereolabs/zed-examples.git \
#    && rm -rf /var/lib/apt/lists/* \
#    && mkdir -p /usr/local/zed/tools

WORKDIR /

CMD ["/bin/bash"]