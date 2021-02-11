#!/usr/bin/env bash

# pull the image
docker pull stereolabs/zed:3.0-runtime-cuda10.2-ubuntu18.04   # runtime release 3.0

# run the container
docker run --gpus all -it --privileged stereolabs/zed:3.0-runtime-cuda9.0-ubuntu18.04

# run zed explorer tool
docker pull stereolabs/zed:3.0-devel-gl-cuda10.2-ubuntu18.04  # pull ZED SDK devel release with OpenGL support
xhost +si:localuser:root  # allow containers to communicate with X server
docker run -it --runtime nvidia --privileged -e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix stereolabs/zed:3.0-devel-gl-cuda10.2-ubuntu18.04

