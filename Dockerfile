# heavy ahh image bro what
FROM gcc:latest AS build

RUN apt-get update -y; apt-get upgrade -y; apt-get install -y build-essential git make pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev libthai-dev

WORKDIR /app

# we are on the root of the project btw
COPY . . 

RUN cd tests/

RUN cmake -S . -B build/

CMD cmake --build build/