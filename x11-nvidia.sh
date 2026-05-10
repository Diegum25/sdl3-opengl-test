#!/bin/bash

xhost +local:docker # sudo pacman -S xorg-host

docker run --rm \
    --net=host \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    --gpus all \
    -e NVIDIA_DRIVER_CAPABILITIES=all \
    dockersdl:latest

xhost -local:docker