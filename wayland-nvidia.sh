#!/bin/bash

# have to run this -> sudo nvidia-ctk runtime configure --runtime=docker
docker run --rm \
    -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
    -v $XDG_RUNTIME_DIR:$XDG_RUNTIME_DIR \
    --gpus all \
    -e NVIDIA_DRIVER_CAPABILITIES=all \
    dockersdl:latest