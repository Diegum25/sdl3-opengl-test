# Temp BUILDING.md
## Clone as submodule
## Get submodules (SDL3 & cglm)

```sh
git submodule update --init --recursive --depth 1
```
## Setup CMakeLists.txt
## Configure build folder and build
```sh
cmake -S . -B build
cmake --build build
```
## Configure windows build version
```sh
cmake -S . -B windows -DCMAKE_TOOLCHAIN_FILE=windows-toolchain.cmake
```
## ~~Run~~

```sh
./build/rmi
```

