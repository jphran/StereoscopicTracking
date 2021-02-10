#!/usr/bin/env bash

# allow contianer to comm with X server
xhost +si:localuser:root

# run docker container iteractive term as root
# connect volumes for display (.X11-unix)
# add DISPLAY env var to container
docker run --gpus all -it --runtime nvidia --privileged -e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix stereolabs/zed:3.3-tools-devel-jetson-jp4.4

