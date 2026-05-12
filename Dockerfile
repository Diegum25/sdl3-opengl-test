FROM gcc:latest as builder

WORKDIR /sdltest

RUN apt-get update

RUN apt-get install -y build-essential git make \
    pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
    libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
    libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
    libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
    libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev libthai-dev \
    libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev \
    libgl1-mesa-dri

COPY ./src ./src
COPY ./stb ./stb
COPY ./SDL ./SDL
COPY ./cglm ./cglm
COPY ./glad ./glad
COPY ./include ./include
COPY ./CMakeLists.txt ./CMakeLists.txt
COPY ./testing ./testing

RUN cmake -S . -B build

RUN cmake --build build --parallel

CMD ./build/hello

# stage  2

FROM ubuntu:rolling

WORKDIR /sdltest

RUN apt-get update

RUN apt-get install -y \
    libasound2t64 libpulse0 libaudio2 libjack0 libsndio7.0 libpipewire-0.3-0 \
    libx11-6 libxext6 libxrandr2 libxcursor1 libxfixes3 libxi6 libxss1 libxtst6 \
    libxkbcommon0 libdrm2 libgbm1 libgl1 libgles2 libegl1 libgl1-mesa-dri \
    libwayland-client0 libwayland-egl1 libdecor-0-0 \
    libdbus-1-3 libibus-1.0-5 libudev1 libthai0 libfribidi0 liburing2

COPY --from=builder /sdltest/build/. .
COPY --from=builder /sdltest/testing/. ./testing

ENV LD_LIBRARY_PATH=/sdltest

CMD ./hello