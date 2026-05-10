#!/bin/bash

docker run --rm \
    -e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
    -v $XDG_RUNTIME_DIR:$XDG_RUNTIME_DIR \
    --device /dev/dri \
    dockersdl:latest