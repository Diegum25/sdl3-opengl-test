#!/bin/bash

# ignore the
# error: XDG_RUNTIME_DIR is invalid or not set in the environment.
# error. if you fix it it will open a wayland window.
# i also dont know if it actually works on a real x session but i dont gaf

xhost +local:docker # sudo pacman -S xorg-host

docker run --rm \
    --net=host \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    --device /dev/dri \
    dockersdl:latest

xhost -local:docker